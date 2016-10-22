//bindclass.h

#pragma once

#include "common.h"

namespace LuaUtilities
{
	template<typename CXXClass>
	class RegisterCXXClass
	{
	private:
		lua_State* L;
		const char* name;

		template<typename... Args, typename F>
		static auto call(lua_State* _state, F _functor, int _first_arg_index)
		{
			auto args{ detail::to_cvalues<Args...>(_state, _first_arg_index) };
			return detail::call_with_expanded_tuple
			(
				[f = _functor](Args... _args)
				{
					return f(_args...);
				}, args
			);
		}

		template<typename T, typename R, typename... Args>
		static auto bind(R(T::*_memfunc_ptr)(Args...), T* _obj)
		{
			return [memf = _memfunc_ptr, obj = _obj](Args... _args)
			{
				return (obj->*memf)(_args...);
			};
		}
	public:
		RegisterCXXClass(lua_State* _state, const char* _class_name) :L(_state), name(_class_name)
		{
			lua_newtable(L); // Class body
			lua_newtable(L); // Metatable
			lua_newtable(L); // Method list
		}

		//Helper to get self pointer.
		//Doesn't work if self is poped before call of this method.
		//You should use this method to cash the self pointer before all in the glue functions.
		static CXXClass* self(lua_State* _state)
		{
			return static_cast<CXXClass*>(lua_touserdata(_state, -1));
		}

		//Return 1 value.
		template<typename R, typename... Args>
		void add_memfunc(R(CXXClass::*_memfunc)(Args...), const char* _name)
		{
			using MemFunc = decltype(_memfunc);
			detail::construct_userdata(L, _memfunc);
			lua_pushcclosure
			(
				L,
				[](lua_State* _state)->int
				{
					auto memfunc_ptr{detail::upvalue_cast<MemFunc*>(_state, 1)};
					auto result{call<Args...>(_state, bind(*memfunc_ptr, self(_state)), 2)};
					detail::push_cvalue(_state, result);
					return 1;
				},
				1
			);
			lua_setfield(L, -2, _name);
		}
		//Return 0 value.
		template<typename... Args>
		void add_memfunc(void(CXXClass::*_memfunc)(Args...), const char* _name)
		{
			using MemFunc = decltype(_memfunc);
			detail::construct_userdata(L, _memfunc);
			lua_pushcclosure
			(
				L,
				[](lua_State* _state)->int
				{
					auto memfunc_ptr{detail::upvalue_cast<MemFunc*>(_state, 1)};
					call<Args...>(_state, bind(*memfunc_ptr, self(_state)), 2);
					return 0;
				},
				1
			);
			lua_setfield(L, -2, _name);
		}

		//After all member functions are registered, 
		//register new adaptor(allocator/constructor) and finalize the class.
		template<typename... Args>
		void finalize(void*(*_new)(Args...))
		{
			lua_setfield(L, -2, "__index");
			lua_pushlightuserdata(L, _new);

			lua_pushcclosure
			(
				L,
				[](lua_State* _state)->int
				{
					//Upvalue 1: metatable
					//Upvalue 2: new adaptor

					//Allocate and construct new object.
					auto new_{static_cast<void*(*)(Args...)>(lua_touserdata(_state, lua_upvalueindex(2)))};
					auto initializer{detail::to_cvalues<Args...>(_state, 1)};
					auto new_obj{detail::call_with_expanded_tuple(new_, initializer)};

					//Clear all arguments.
					lua_settop(_state, 0);

					lua_pushlightuserdata(_state, new_obj);

					//Set the metatable.
					lua_pushvalue(_state, lua_upvalueindex(1));
					lua_setmetatable(_state, -2);

					//Return new object of type userdata.
					return 1;
				},
				2
			);
			lua_setfield(L, -2, "new");

			//Finally, register the class to the global field.
			lua_setglobal(L, name);
		}
	};

}
