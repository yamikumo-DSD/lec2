#include <type_traits>

template
<
	typename InputItr,
	 std::enable_if_t<std::is_arithmetic<typename std::decay_t<InputItr>::value_type>::value>* 
	 = nullptr
 >
constexpr inline auto sum(InputItr first, InputItr last) noexcept
{
	using ValType = std::decay_t<decltype(*first)>;
	auto result{static_cast<ValType>(0)};
	while(first != last){result += *(first++);}
	return result;
}

#include <iterator>

template
<
	typename InputItr,
	std::enable_if_t<std::is_arithmetic<typename std::decay_t<InputItr>::value_type>::value>* 
	= nullptr
>
constexpr inline auto mean(InputItr first, InputItr last) noexcept
{
	return sum(first, last) / std::distance(first, last);
}

#include <iostream>
#include <vector>

int main()
{
	//This test program calculates mean of data.
	std::vector<double> data{1, 2, 3, 4, 5};
	std::cout << mean(data.begin(), data.end()) << std::endl;
}
