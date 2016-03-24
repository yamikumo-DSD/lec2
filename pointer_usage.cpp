
namespace IntroduceThisAndArrow
{
	struct Widget //If you don't know that struct is class, please remember.
	{
		int data;
		explicit Widget(int _data = 0) :data(_data) {}
		Widget(const Widget& _widget) :data(_widget.data) {}
		//One of the most common use of 'this' is overloading of assign operator.
		Widget& operator=(const Widget& _widget) 
		{
			data = _widget.data; 
			return *this; //returning *this as reference of Widget! 
		}
	};
}

#include <memory>
#include <iostream>

int main(void)
{
	using namespace IntroduceThisAndArrow;

	Widget* widget_ptr = new Widget(123); //old style pointer.

	//use of arrow operator. 
	//You can also write
	//(*widget_ptr).data
	std::cout << widget_ptr->data << std::endl; 

	Widget copy_of_widget;
	copy_of_widget = *widget_ptr; //use operator= overloaded. 
	std::cout << copy_of_widget.data << std::endl;

	delete widget_ptr; //No need to say... don't forget to delete.
	std::cin.get();

#if 0
	//You can also apply arrow operator to more up-to-date style of pointer-like classes in standard libraries such as std::unique_ptr<T>
	//Only available with C++14 or later version of compiler.
	auto dynamic_widget{std::make_unique<Widget>(12345)};
	std::cout << dynamic_widget->data << std::endl;
	//Automatically deleted when the code reached closing-parenthesis.
#endif
}