#include <thread>
#include <functional>

struct TwoChars
{
  char a;
  char b;
};

const int N = 10000000;
const int M = 100;
TwoChars ch;

int main()
{
  auto thr1 = new std::thread([&](){
      //      for(int i = 0; i < N; ++i)
      for(int i = 0; i < M; ++i)
      for(int i = 0; i < N; ++i)
	ch.a = i;
    });
  auto thr2 = new std::thread([&](){
      for(int i = 0; i < M; ++i)
	//for(int i = 0; i < N; ++i)
      for(int i = 0; i < N; ++i)
	ch.b = i;
    });
  thr1->join();
  thr2->join();
  delete thr1;
  delete thr2;
  return 0;
}
