#include <thread>
#include <functional>


const int N = 500000000;

char ping[1024];

int main()
{
  auto thr1 = new std::thread([&](){
      for(int i = 0; i < N; ++i)
	ping[0] = i;
    });
  auto thr2 = new std::thread([&](){
      for(int i = 0; i < N; ++i)
	ping[1024] = i;
    });
  thr1->join();
  thr2->join();
  delete thr1;
  delete thr2;
  return 0;
}
