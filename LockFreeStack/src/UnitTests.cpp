#include "LockFreeStack.hpp"
#include <thread>
#include <functional>
#include <vector>
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LOCK_FREE_STACK_UNIT_TEST
#include <boost/test/unit_test.hpp>

#define SIZE 10e3

template <typename T>
void Produce(std::vector<T>& storage, LockFreeStack<T>& stack)
{
    for(auto it = storage.begin(); it != storage.end(); ++it)
        stack.Push(*it);
}
template <typename T>
void Consume(unsigned int items, std::vector<T>& consume, LockFreeStack<T>& stack)
{
    for(unsigned int i = 0; i < items; ++i)
    {
        T item;
        while(!stack.Pop(item));

        consume.push_back(item);
    }
}
std::vector<int> GenerateStorage(int from, int to)
{
    assert(from <= to);
    std::vector<int> storage;
    for(int i = from; i < to; ++i)
        storage.push_back(i);
    return storage;
}

BOOST_AUTO_TEST_CASE(LockFreeTest_default)
{
    LockFreeStack<int> stack;
    auto storage1 = GenerateStorage(0, 10*SIZE);
    auto storage2 = GenerateStorage(10*SIZE, 20*SIZE);
    std::vector<int> consume1, consume2, consume;
    auto push1 = new std::thread(Produce<int>, std::ref(storage1), std::ref(stack));
    auto cons1 = new std::thread(Consume<int>, 8*SIZE, std::ref(consume1), std::ref(stack));
    auto push2 = new std::thread(Produce<int>, std::ref(storage2), std::ref(stack));
    auto cons2 = new std::thread(Consume<int>, 8*SIZE, std::ref(consume2), std::ref(stack));
    push1->join();
    delete push1;
    push2->join();
    delete push2;
    cons1->join();
    delete cons1;
    cons2->join();
    delete cons2;
    std::vector<bool> verify(20*SIZE, false);
    for(auto it = consume1.begin(); it != consume1.end(); ++it)
    {
        if(verify[*it])
        {
            std::cout << "Fail on verify - already true - consume1:" << *it << std::endl;
        }
        BOOST_CHECK(!verify[*it]);
        verify[*it] = true;
    }
    for(auto it = consume2.begin(); it != consume2.end(); ++it)
    {
        if(verify[*it])
        {
            std::cout << "Fail on verify - already true - consume2:" << *it << std::endl;
        }
        BOOST_CHECK(!verify[*it]);
        verify[*it] = true;
    }
    auto cons = new std::thread(Consume<int>, 4*SIZE, std::ref(consume), std::ref(stack));
    cons->join();
    delete cons;
    for(auto it = consume.begin(); it != consume.end(); ++it)
    {
        if(verify[*it])
        {
            std::cout << "Fail on verify - already true - consume:" << *it << std::endl;
        }
        BOOST_CHECK(!verify[*it]);
        verify[*it] = true;
    }
    for(int i = 0; i < verify.size(); ++i)
    {
        if(!verify[i])
        {
            std::cout << "Lost element:" << i << std::endl;
        }
        BOOST_CHECK(verify[i]);
    }
}
BOOST_AUTO_TEST_CASE(LockFreeTest_custom)
{
    LockFreeStack<int> stack(LockFreeStack<int>::MallocType::CUSTOM, 100*SIZE);
    auto storage1 = GenerateStorage(0, 10*SIZE);
    auto storage2 = GenerateStorage(10*SIZE, 20*SIZE);
    std::vector<int> consume1, consume2, consume;
    auto push1 = new std::thread(Produce<int>, std::ref(storage1), std::ref(stack));
    auto cons1 = new std::thread(Consume<int>, 8*SIZE, std::ref(consume1), std::ref(stack));
    auto push2 = new std::thread(Produce<int>, std::ref(storage2), std::ref(stack));
    auto cons2 = new std::thread(Consume<int>, 8*SIZE, std::ref(consume2), std::ref(stack));
    push1->join();
    delete push1;
    push2->join();
    delete push2;
    cons1->join();
    delete cons1;
    cons2->join();
    delete cons2;
    std::vector<bool> verify(20*SIZE, false);
    for(auto it = consume1.begin(); it != consume1.end(); ++it)
    {
        if(verify[*it])
        {
            std::cout << "Fail on verify - already true - consume1:" << *it << std::endl;
        }
        BOOST_CHECK(!verify[*it]);
        verify[*it] = true;
    }
    for(auto it = consume2.begin(); it != consume2.end(); ++it)
    {
        if(verify[*it])
        {
            std::cout << "Fail on verify - already true - consume2:" << *it << std::endl;
        }
        BOOST_CHECK(!verify[*it]);
        verify[*it] = true;
    }
    auto cons = new std::thread(Consume<int>, 4*SIZE, std::ref(consume), std::ref(stack));
    cons->join();
    delete cons;
    for(auto it = consume.begin(); it != consume.end(); ++it)
    {
        if(verify[*it])
        {
            std::cout << "Fail on verify - already true - consume:" << *it << std::endl;
        }
        BOOST_CHECK(!verify[*it]);
        verify[*it] = true;
    }
    for(int i = 0; i < verify.size(); ++i)
    {
        if(!verify[i])
        {
            std::cout << "Lost element:" << i << std::endl;
        }
        BOOST_CHECK(verify[i]);
    }
}
