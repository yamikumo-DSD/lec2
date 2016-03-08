//multi_threading.cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <cstdlib>
#include <array>
#include <vector>
#include <chrono>

#define THREADING_VER

int main(void)
{
     using Mutex = std::mutex;
     using LockGuard = std::lock_guard<Mutex>;

     const auto start = std::chrono::system_clock::now();

     std::vector<long> data_base;

#ifdef THREADING_VER
     constexpr auto TASK_NUM{10};
     Mutex mux;

     auto work
     {
               [&data_base, &mux](void) 
               {
                    for (long i = 0; i != 10'000'000; ++i) 
                    {
                         LockGuard lock{mux};
                         data_base.emplace_back(i);
                    }
               }
     };

     std::array<std::future<void>, TASK_NUM> task_list;

     for (auto& task : task_list)
     {
          task = std::async(std::launch::async, work);
     }//all task aren't deferred.

     for (auto& task : task_list) { task.wait(); }
#else
     for (int j = 0; j != TASK_NUM; ++j)
     {
          for (long i = 0; i != 10'000'000; ++i) { data_base.emplace_back(i); }
     }
#endif

     std::cout << data_base.size() << std::endl;

     std::cout <<
          std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count()
          << std::endl;

     std::system("pause");
     return 0;
}
