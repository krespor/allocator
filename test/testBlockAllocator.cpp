#include <Allocator.h>

#include <iostream>
#include <cassert>

int main()
{
    Allocator allocator;
    allocator.init();

    std::cout << allocator.getPoolSize() << std::endl;
    std::cout << allocator.getPoolSize() << std::endl;

    

    return 0;
}