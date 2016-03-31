#ifndef C_LOCK_FREE_STACK_H
#define C_LOCK_FREE_STACK_H

#include <assert.h>
#include <atomic>
#include <vector>
#include <iostream>

#ifdef TEST_LOCK_FREE_STACK
#include <Logger.h>
#include <sstream>

template <typename T>
struct atomwrapper
{
  std::atomic<T> _a;

  atomwrapper()
    :_a()
  {}

  atomwrapper(const std::atomic<T> &a)
    :_a(a.load())
  {}

  atomwrapper(const atomwrapper &other)
    :_a(other._a.load())
  {}

  atomwrapper &operator=(const atomwrapper &other)
  {
    _a.store(other._a.load());
  }
};
#endif

template <typename ValueType>
class LockFreeStack
{
    public:
        enum MallocType
        {
            DEFAULT, CUSTOM     //Test Purposes only
        };

        LockFreeStack(MallocType type = MallocType::DEFAULT, unsigned int size = 0);
        ~LockFreeStack();
        bool Pop(ValueType& data);
        void Push(ValueType data);
    private:
        struct Node
        {
            Node(Node* next, ValueType data):next(next), data(data) {}
            Node* next;
            ValueType data;
        };
        class IAllocator
        {
            public:
                virtual ~IAllocator(){};
                virtual Node* Malloc(Node* next, ValueType data) = 0;
                virtual void Free(Node* node) = 0;
                virtual void Initialize(unsigned int size) = 0;
        };

#ifdef TEST_LOCK_FREE_STACK
        class CustomMalloc:public IAllocator
        {
            public:
                CustomMalloc() {}
                ~CustomMalloc();
                Node* Malloc(Node* next, ValueType data);
                void Free(Node* node);
                void Initialize(unsigned int size);
            private:
                std::vector< atomwrapper<bool> > allocIds_;
                Node* alloc_;

        };
#endif
        class DefaultMalloc:public IAllocator
        {
            public:
                DefaultMalloc() {}
                ~DefaultMalloc(){}
                Node* Malloc(Node* next, ValueType data) { return new Node(next, data);}
                void Free(Node* node){delete node;}
                void Initialize(unsigned int size){};

        };
        std::atomic<Node*> head_;
        IAllocator* allocator;
};



template <typename ValueType>
LockFreeStack<ValueType>::LockFreeStack(MallocType type, unsigned int size)
{
#ifndef TEST_LOCK_FREE_STACK
    assert(type == MallocType::DEFAULT);
#endif
    assert((type == MallocType::DEFAULT) || size > 0);
    switch(type)
    {
        case MallocType::DEFAULT:
            allocator = new DefaultMalloc();
            break;
        case MallocType::CUSTOM:
            allocator = new CustomMalloc();
            allocator->Initialize(size);
            break;
        default:
            break;
    }

    head_.store(nullptr);
}

template <typename ValueType>
LockFreeStack<ValueType>::~LockFreeStack()
{
    auto pointer = head_.load();
    while(pointer != nullptr)
    {
        auto oldHead = pointer;
        pointer = pointer->next;
        allocator->Free(pointer);
        pointer = oldHead;
    }
    delete allocator;
}

template <typename ValueType>
bool LockFreeStack<ValueType>::Pop(ValueType& data)
{
    auto a = head_.load();
    do{
           if(a == nullptr)
               return false;
    }while(!head_.compare_exchange_strong(a, a->next));
    if(a == nullptr)
        return false;
    data = a->data;
    allocator->Free(a);;
    return true;
}

template <typename ValueType>
void LockFreeStack<ValueType>::Push(ValueType data)
{
    Node* node = allocator->Malloc(head_.load(), data);
    while(!head_.compare_exchange_strong(node->next, node));
}

#ifdef TEST_LOCK_FREE_STACK
template <typename ValueType>
LockFreeStack<ValueType>::CustomMalloc::~CustomMalloc()
{
    free(alloc_);
}
template <typename ValueType>
void LockFreeStack<ValueType>::CustomMalloc::Initialize(unsigned int size)
{
    for(int i = 0; i < size; ++i)
    {
        std::atomic<bool> atom(false);
        allocIds_.push_back(atom);
    }
    if((alloc_ = (Node*)malloc(sizeof(Node)*size)) < 0)
    {
        std::cerr << "Failed to alloc stack\n" << std::endl;
        exit(1);
    }
}
template <typename ValueType>
typename LockFreeStack<ValueType>::Node*LockFreeStack<ValueType>::CustomMalloc::Malloc(Node* next, ValueType data)
{
    int i = 0;
    while(true)
    {
        bool expected = false;
#ifdef LOG
        std::stringstream s;
        s << "Trying to allocate " << i << " " << alloc_ + i << std::endl;
        Logger::logger() << s;
#endif
        if(allocIds_[i]._a.compare_exchange_strong(expected, true))
        {
            Node* node = alloc_ + i;
            node->next = next;
            node->data = data;
#ifdef LOG
            s.str(std::string());
            s << "Allocated " << i << " " << alloc_ + i << std::endl;
            Logger::logger() << s;
#endif
            return node;
        }
        i = (i + 1) % allocIds_.size();
    }
}
template <typename ValueType>
void LockFreeStack<ValueType>::CustomMalloc::Free(Node* node)
{
    int i;
    for(i = 0; i < allocIds_.size(); ++i)
    {
        long b = long(node);
        long a = long(alloc_);
#ifdef LOG
        std::stringstream s;
        s << i << " " << (b-a) << std::endl;
        Logger::logger() << s;
#endif
        if(node == alloc_ + i)
        {
            bool expected = true;
            if(!allocIds_[i]._a.compare_exchange_strong(expected, false))
            {
                std::cerr << "Already freed at " << i << std::endl;
                exit(1);
            }
#ifdef LOG
            s.str(std::string());
            s << "Freed " << i << " " << alloc_ + i << std::endl;
            Logger::logger() << s;
#endif
            return;
        }
    }
    std::cerr << "Can't find pointer: " << node << std::endl;
    exit(1);
}
#endif

#endif

