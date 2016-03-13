#include <thread>
#include <futex.h>


Futex::Futex()
{
    ownerId_.store(Hasher(std::this_thread::get_id()));
    hash0_ = Hasher(std::this_thread::get_id());
}

bool Futex::lock(int hash)
{
    uint8_t desired = hash0_;
    while(!ownerId_.compare_exchange_strong(desired, hash, std::memory_order_acquire))
    {
        desired = hash0_;
        std::this_thread::yield();  //Опыт показывает, что вызывать yield каждый раз выгоднее, чем каждый 2-ой, 5-й или 10-й
                                    //(Как под gcc, так и под clang)
    }
    return true;
}
bool Futex::unlock(int hash)
{
    uint8_t desired = hash;
    if(!ownerId_.compare_exchange_strong(desired, hash0_))
        return false;
    return true;
}
