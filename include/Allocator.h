#include <cstdint>
#include <unordered_map>
#include <cstring>
#include <algorithm>

class Allocator
{
    enum class state: bool {USED=true, FREE=false};
    
public:
    typedef void* block_ptr;

    Allocator();
    ~Allocator();

    void init();

    uint32_t getPoolSize();
    uint32_t getBlockSize();

    block_ptr getBlock();
    void releaseBlock(block_ptr pBlock);
    void releasePool();

private:
    const uint32_t numberBlocks;
    uint8_t* pool {nullptr};
    std::unordered_map<block_ptr, state> pointers;

    void createPointers();
    block_ptr findFreeBlock();
};