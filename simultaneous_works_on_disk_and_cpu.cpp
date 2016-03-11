//myMain.cpp

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <future>
#include <chrono>

#define MULTITHREAD_VER

int main(void)
{
	using namespace std::chrono;

	auto start_t{high_resolution_clock::now()};

#ifdef MULTITHREAD_VER
	auto write
	{
		std::async
		(
			std::launch::async,
			[](void)
			{
				std::ofstream ofs{"output", std::ios_base::trunc};
				for (long i = 0; i != 1'000'000L; ++i) { ofs << i; }
			}
		)
	}; //this task won't be deferred.

	for (volatile long i = 0; i != 100'000'000L; ++i); //Do other heavy works. 

	try { write.get(); } //Wait until the writing procedure ends.
	catch (const std::exception& _e) { std::cerr << _e.what() << std::endl; }
#else
	try
	{
		std::ofstream ofs{"output", std::ios_base::trunc};
		for (long i = 0; i != 1'000'000L; ++i) { ofs << i; }

		for (volatile long i = 0; i != 100'000'000L; ++i); //Do other heavy works. 
	}
	catch (const std::exception& _e) { std::cerr << _e.what() << std::endl;}
#endif

	std::cout << duration_cast<microseconds>(high_resolution_clock::now() - start_t).count() << std::endl;

	std::system("pause");
}