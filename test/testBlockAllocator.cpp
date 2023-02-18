#include <Allocator.h>

#include <iostream>
#include <cassert>

Allocator allocator;
const uint32_t poolSize = allocator.getPoolSize();
const uint32_t blockSize = allocator.getBlockSize();

bool test_1()
{
    Allocator::block_ptr p1 = allocator.getBlock();
    allocator.releasePool();
    Allocator::block_ptr p2 = allocator.getBlock();

    return p1 == p2;
}

bool test_2()
{
    Allocator::block_ptr p1 = allocator.getBlock();
    allocator.releaseBlock(p1);
    Allocator::block_ptr p2 = allocator.getBlock();

    return p1 == p2;
}

bool test_3()
{
    Allocator::block_ptr p1 = allocator.getBlock();
    Allocator::block_ptr p2 = allocator.getBlock();

    return (uint8_t*)p2 + blockSize == (uint8_t*)p1;
}

bool test_4()
{
    Allocator::block_ptr p1 = allocator.getBlock();
    try
    {
        allocator.releaseBlock((uint8_t*)p1+1);
        return false;
    }
    catch(const char* e)
    {
        return e == "invalid pointer";
    }
}

bool test_5()
{
    Allocator::block_ptr p1 = allocator.getBlock();
    try
    {
        allocator.releaseBlock(p1);
        allocator.releaseBlock(p1);
        return false;
    }
    catch(const char* e)
    {
        return e == "pointer already released";
    }
}

bool test_6()
{
    const uint8_t value {123};
    Allocator::block_ptr p1 = allocator.getBlock();

    *reinterpret_cast<uint8_t*>(p1) = value;
    allocator.releaseBlock(p1);


    Allocator::block_ptr p1_ = allocator.getBlock();
    const uint8_t value_ = *reinterpret_cast<uint8_t*>(p1_);

    return value == value_;
}

int main()
{
    allocator.init();

    std::cout << "pool size = " << poolSize << std::endl;
    std::cout << "block size = " << blockSize << std::endl;

    assert(test_1());
    allocator.releasePool();
    std::cout << "test 1/6: successful" << std::endl;

    assert(test_2());
    allocator.releasePool();
    std::cout << "test 2/6: successful" << std::endl;

    assert(test_3());
    allocator.releasePool();
    std::cout << "test 3/6: successful" << std::endl;

    assert(test_4());
    allocator.releasePool();
    std::cout << "test 4/6: successful" << std::endl;

    assert(test_5());
    allocator.releasePool();
    std::cout << "test 5/6: successful" << std::endl;
    
    assert(test_6());
    allocator.releasePool();
    std::cout << "test 6/6: successful" << std::endl;
    return 0;
}