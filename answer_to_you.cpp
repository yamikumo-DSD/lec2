#include <iostream>
#include <type_traits>
#include <vector>
#include <exception>
#include <algorithm>
#include <string>
#include <boost/lexical_cast.hpp>

namespace Answer
{
	namespace _1
	{
		namespace Impl
		{
			template<typename Container>
			auto mean_of(Container&& _data)
			{
				if (_data.size() == 0) { throw std::logic_error("Empty container"); }
				using value_type = std::enable_if_t
				<
					std::is_arithmetic
					<
						std::remove_reference_t<Container>::value_type
					>::value,
					std::remove_reference_t<Container>::value_type
				>;
				value_type result{};
				for (const auto& val : _data) { result += val; }
				return static_cast<value_type>(result / _data.size());
			}

		}

		void exec(void)
		{
			using ValueType = int;
			std::vector<int> data;
			while (true)
			{
				std::string input;
				std::getline(std::cin, input);
				if (input.empty()) { break; }
				try
				{
					data.push_back(boost::lexical_cast<ValueType>(input));
				}
				catch (const boost::bad_lexical_cast& _blc)
				{
					data.push_back(static_cast<ValueType>(0));
				}
			}
			std::cout << Impl::mean_of(data) << std::endl;
		}
	}

	namespace _2
	{
		namespace Impl
		{
			template<typename String>
			void to_upper(String& _origin)
			{
				using std::cbegin;
				using std::cend;
				using std::begin;
				std::transform(cbegin(_origin), cend(_origin), begin(_origin), [](const auto& c) {return std::toupper(c, std::locale()); });
			}
		}
		void exec(void)
		{
			std::vector<std::string> data;
			while (true)
			{
				std::string input;
				std::getline(std::cin, input);
				if (input.empty()) { break; }
				data.push_back(input);
			}

			for (auto& line : data) { Impl::to_upper(line); }

			for (const auto& line : data) { std::cout << line << std::endl; }
		}
	}
}

#include <cstdlib>

int main(void)
{
	Answer::_1::exec();
	Answer::_2::exec();
	std::system("pause");
}
