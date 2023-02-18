#include "Allocator.h"

#ifndef POOL_SIZE
#define POOL_SIZE 128
#endif

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 8
#endif

uint8_t Allocator::pool[POOL_SIZE] = {0};

Allocator::Allocator() : numberBlocks(POOL_SIZE / BLOCK_SIZE){}

void Allocator::init()
{
    std::lock_guard lg{mtx};

    createPointers();
}

uint32_t Allocator::getPoolSize() const noexcept
{
    return POOL_SIZE;
}

uint32_t Allocator::getBlockSize() const noexcept
{
    return BLOCK_SIZE;
}

void Allocator::createPointers()
{
    for (uint32_t i = 0; i < numberBlocks; ++i)
        pointers.insert({(&pool[0] + BLOCK_SIZE * i), state::FREE});
}

Allocator::block_ptr Allocator::getBlock()
{
    std::lock_guard lg{mtx};
    
    const block_ptr ch_ptr = findFreeBlock();

    if (ch_ptr)
        pointers[ch_ptr] = state::USED;

    return ch_ptr;
}

void Allocator::releaseBlock(block_ptr pBlock)
{
    std::lock_guard lg{mtx};
    
    if (!pointers.count(pBlock))
        throw "invalid pointer";

    if (pointers[pBlock] == state::FREE)
        throw "pointer already released";

    pointers[pBlock] = state::FREE;
}

void Allocator::releasePool()
{
    std::lock_guard lg{mtx};
    
    for (auto &[ptr, st]: pointers)
        st = state::FREE;
}

Allocator::block_ptr Allocator::findFreeBlock() const
{
    const auto it = std::find_if(pointers.begin(), pointers.end(), 
    [](const std::pair<block_ptr, state>& ptrs){return ptrs.second == state::FREE;});
    
    return it != pointers.end() ? it->first : nullptr;
}