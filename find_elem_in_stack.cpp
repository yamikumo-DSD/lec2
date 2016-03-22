#include <iostream>
#include <stack>

template<typename T>
struct stack_traits
{
    using value_type = typename T::value_type;
    //stack should have pop interface
    static void pop(T& _stack){_stack.pop();}
    //stack should have push interface
    template<typename U>
    static void push(T& _stack, U&& _new_value){_stack.emplace(std::forward<U>(_new_value));}
    //stack should have top interface
    static value_type top(const T& _stack){return _stack.top();}
    //stack should have size interface
    static std::size_t size(const T& _stack){return _stack.size();}
};

struct stack_category{};

template<typename T>
struct category_of;

template<typename ValType>
struct category_of<std::stack<ValType>>{using type = stack_category;};

template<typename T, typename Comp>
auto my_find_if_impl(T _stack, Comp&& _comp, stack_category)
{
    using traits = stack_traits<T>;
    using value_type = typename traits::value_type;
    if(traits::size(_stack) < 1){throw std::logic_error("You cannot apply find_if algorithm to empty container.");}
    value_type buffer{traits::top(_stack)};
    while(traits::size(_stack) > 1)
    {
        traits::pop(_stack);
        if(!_comp(buffer, traits::top(_stack)))
        {
            buffer = traits::top(_stack);
        }
    }
    return buffer;
}

template<typename T, typename Comp>
auto my_find_if(T _container, Comp&& _comp)
{
    return my_find_if_impl(_container, std::forward<Comp>(_comp), typename category_of<T>::type());
}

int main(void)
{
    std::stack<int> data;
    data.push(100); data.push(20); data.push(40); data.push(0);
    std::cout << my_find_if(data, [](auto _first, auto _second){return _first < _second;});
}
