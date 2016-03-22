#ifndef C_SYNC_CONTAINER
#define C_SYNC_CONTAINER

#include <queue>
#include <stack>
#include <mutex>
#include <atomic>
#include <condition_variable>

template <class CONTAINER>
class CSyncContainer
{
    typedef typename CONTAINER::value_type value_type;
    public:
        CSyncContainer();

        void push(value_type item);
        bool popOrSleep(value_type& item);
        bool popNoSleep(value_type& item);
        size_t size();
        void terminate();
        void restart();

    private:
        CONTAINER container_;
        std::mutex containerLock_;
        std::condition_variable notEmptyFlag_;
        std::atomic<bool> terminated_;
};



template <class CONTAINER>
CSyncContainer<CONTAINER>::CSyncContainer()
{
    terminated_.store(false);
}
template <class CONTAINER>
void CSyncContainer<CONTAINER>::push(value_type item)
{
    std::unique_lock<std::mutex> lock(containerLock_);
    container_.push_back(item);
    lock.unlock();
    notEmptyFlag_.notify_one();
}

template <class CONTAINER>
bool CSyncContainer<CONTAINER>::popOrSleep(value_type& item)
{
    std::unique_lock<std::mutex> lock(containerLock_);
    while(container_.empty() && !terminated_)
        notEmptyFlag_.wait(lock);
    if(container_.empty())
        return false;
    item = container_.back();
    container_.pop_back();
    return true;
}

template <class CONTAINER>
bool CSyncContainer<CONTAINER>::popNoSleep(value_type& item)
{
    std::unique_lock<std::mutex> lock(containerLock_);
    if(container_.empty())
        return false;
    item = container_.back();
    container_.pop_back();
    return true;
}
template <class CONTAINER>
size_t CSyncContainer<CONTAINER>::size()
{
    std::unique_lock<std::mutex> lock(containerLock_);
    return container_.size();
}
template <class CONTAINER>
void CSyncContainer<CONTAINER>::terminate()
{
    std::unique_lock<std::mutex> lock(containerLock_);
    terminated_.store(true);
    lock.unlock();
    notEmptyFlag_.notify_all();
}
template <class CONTAINER>
void CSyncContainer<CONTAINER>::restart()
{
    std::unique_lock<std::mutex> lock(containerLock_);
    terminated_.store(false);
}

template<typename T>
class CSyncContainer<std::queue<T>>
{
    public:
        CSyncContainer<std::queue<T>>()
        {
            terminated_.store(false);
        }

        bool popOrSleep(T& item)
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            while(container_.empty() && !terminated_)
                notEmptyFlag_.wait(lock);
            if(container_.empty())
                return false;
            item = container_.front();
            container_.pop();
            return true;
        }
        bool popNoSleep(T& item)
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            if(container_.size() == 0)
                return false;
            item = container_.front();
            container_.pop();
            return true;
        }
        void push(T item)
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            container_.push(item);
            lock.unlock();
            notEmptyFlag_.notify_one();
        }
        size_t size()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            return container_.size();
        }
        void terminate()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            terminated_.store(true);
            lock.unlock();
            notEmptyFlag_.notify_all();
        }
        void restart()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            terminated_.store(false);
        }
    private:
        std::queue<T>    container_;
        std::mutex containerLock_;
        std::condition_variable notEmptyFlag_;
        std::atomic<bool> terminated_;
};
template<typename T>
class CSyncContainer<std::stack<T>>
{
    public:
        CSyncContainer<std::stack<T>>()
        {
            terminated_.store(false);
        }
        bool popOrSleep(T& item)
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            while(container_.empty() && !terminated_)
                notEmptyFlag_.wait(lock);
            if(container_.empty())
                return false;
            item = container_.top();
            container_.pop();
            return true;
        }
        bool popNoSleep(T& item)
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            if(container_.size() == 0)
                return false;
            item = container_.top();
            container_.pop();
            return true;
        }
        void push(T item)
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            container_.push(item);
            lock.unlock();
            notEmptyFlag_.notify_one();
        }
        size_t size()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            return container_.size();
        }
        void terminate()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            terminated_.store(true);
            lock.unlock();
            notEmptyFlag_.notify_all();
        }
        void restart()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            terminated_.store(false);
        }

    private:
        std::stack<T>    container_;
        std::mutex containerLock_;
        std::condition_variable notEmptyFlag_;
        std::atomic<bool> terminated_;
};

#endif
