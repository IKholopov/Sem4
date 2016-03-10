#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
#include <limits>
#include <futex.h>
#include <mutex>
#include <pthread.h>
#include <chrono>

long long MAX_SUM = 500000000;
long long  global = 0;
Futex futex;
std::mutex mutex;
pthread_mutex_t pmutex = PTHREAD_MUTEX_INITIALIZER;
int incrementFutex(long long& localSum)
{
    int myHash = futex.Hasher(std::this_thread::get_id());
    while(true)
    {
        futex.lock(myHash);
        if(global >= MAX_SUM)
        {
            futex.unlock(myHash);
            break;
        }
        ++global;
        ++localSum;
        futex.unlock(myHash);
    }
    return 0;
}
int incrementMutex(long long& localSum)
{
    while(true)
    {
        mutex.lock();
        if(global >= MAX_SUM)
        {
            mutex.unlock();
            break;
        }
        ++global;
        ++localSum;
        mutex.unlock();
    }
    return 0;
}
int incrementPMutex(long long& localSum)
{
    while(true)
    {
        pthread_mutex_lock(&pmutex);
        if(global >= MAX_SUM)
        {
            pthread_mutex_unlock(&pmutex);
            break;
        }
        ++global;
        ++localSum;
        pthread_mutex_unlock(&pmutex);
    }
    return 0;
}
void run(int increment(long long& localSum), size_t numberOfThreads)
{
    global = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<long long> local(numberOfThreads, 0);
    std::vector<std::thread*> threads(numberOfThreads);
    start = std::chrono::system_clock::now();
    for(int i = 0; i < numberOfThreads; ++i)
        threads[i]= new std::thread(increment, std::ref(local[i]));
    for(int i = 0; i < numberOfThreads; ++i)
        threads[i]->join();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end-start;
    long long sum = 0;
    for(int i = 0; i < numberOfThreads; ++i)
    {
        sum += local[i];
        std::cout << i << ": " << local[i] << std::endl;
    }
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << std::endl;
}

int runTests(size_t nThreads)
{
    std::cout << "Futex:" << std::endl;
    run(&incrementFutex, nThreads);
    std::cout << "Pthread Mutex:" << std::endl;
    run(&incrementPMutex, nThreads);
    std::cout << "std::mutex:" << std::endl;
    run(&incrementMutex, nThreads);
    std::cout << std::endl;
}

int main()
{
    std::cout << "std::thread::hardware_concurrency() / 2:" << std::endl << std::endl;
    runTests(std::thread::hardware_concurrency() / 2);
    runTests(std::thread::hardware_concurrency() * 2);
    return 0;
}
