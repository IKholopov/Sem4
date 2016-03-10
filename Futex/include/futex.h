#ifndef FUTEXT_H
#define FUTEX_H

#include <thread>
#include <atomic>

class Futex{
    public:
        Futex();
        bool lock(int hash);
        bool unlock(int hash);
        std::hash<std::thread::id> Hasher;
    private:
        std::atomic<uint8_t> ownerId_;
        int hash0_;
        Futex(const Futex& futex) = delete;
};

#endif
