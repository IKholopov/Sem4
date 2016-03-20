#ifndef C_SYNC_CONTAINER
#define C_SYNC_CONTAINER

#include <queue>
#include <stack>
#include <mutex>
#include <condition_variable>

template <class CONTAINER>
class CSyncContainer
{
    typedef typename CONTAINER::value_type value_type;
    public:
        CSyncContainer();

        void push(value_type item);
        value_type popOrSleep();
        bool popNoSleep(value_type& item);
        size_t size();
    private:
        CONTAINER container_;
        std::mutex containerLock_;
        std::condition_variable notEmptyFlag_;
};



template <class CONTAINER>
CSyncContainer<CONTAINER>::CSyncContainer()
{

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
typename CSyncContainer<CONTAINER>::value_type CSyncContainer<CONTAINER>::popOrSleep()
{
    std::unique_lock<std::mutex> lock(containerLock_);
    while(container_.empty())
        notEmptyFlag_.wait(lock);
    auto element = container_.back();
    container_.pop_back();
    return element;
}

template <class CONTAINER>
bool CSyncContainer<CONTAINER>::popNoSleep(value_type& item)
{
    std::unique_lock<std::mutex> lock(containerLock_);
    if(container_.size() == 0)
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

template<typename T>
class CSyncContainer<std::queue<T>>
{
    public:
        T popOrSleep()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            while(container_.empty())
                notEmptyFlag_.wait(lock);
            auto element = container_.front();
            container_.pop();
            return element;
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
    private:
        std::queue<T>    container_;
        std::mutex containerLock_;
        std::condition_variable notEmptyFlag_;
};
template<typename T>
class CSyncContainer<std::stack<T>>
{
    public:
        T popOrSleep()
        {
            std::unique_lock<std::mutex> lock(containerLock_);
            while(container_.empty())
                notEmptyFlag_.wait(lock);
            auto element = container_.top();
            container_.pop();
            return element;
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
    private:
        std::stack<T>    container_;
        std::mutex containerLock_;
        std::condition_variable notEmptyFlag_;
};

#endif
