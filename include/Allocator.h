#include <cstdint>
#include <unordered_map>
#include <cstring>
#include <algorithm>
#include <mutex>

class Allocator
{
    enum class state: bool {USED=true, FREE=false};
    
public:
    typedef void* block_ptr;

    Allocator();

    void init();

    uint32_t getPoolSize() const noexcept;
    uint32_t getBlockSize() const noexcept;

    block_ptr getBlock();
    void releaseBlock(block_ptr pBlock);
    void releasePool();

    
private:
    const uint32_t numberBlocks;
    
    static uint8_t pool[];
    std::unordered_map<block_ptr, state> pointers;

    std::mutex mtx;

    void createPointers();
    block_ptr findFreeBlock() const;
};