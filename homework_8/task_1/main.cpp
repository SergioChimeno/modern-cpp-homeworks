#include <iostream>
 
constexpr uint32_t KiBToAllocate = 8200;
constexpr uint32_t bytesInOneKiB = 1024;
constexpr uint32_t bytesPerAllocation = 100*bytesInOneKiB;
constexpr uint32_t numberOfAllocations = (KiBToAllocate*bytesInOneKiB)/bytesPerAllocation;

void allocate(uint32_t allocationIt);
uint64_t sum(uint8_t array[], uint32_t size);

int main(int argc, char const *argv[])
{
    // Allocate 8192 KiB in stack. 8 MiB
    // 100 KiB = 100*1024 bytes = 100*1024
    // 1 char = 1 byte.

    for(uint32_t allocationN =1;allocationN<=numberOfAllocations;allocationN++)
    {
        uint8_t array[allocationN*bytesPerAllocation];
        sum(array,allocationN*bytesPerAllocation);
        std::cout << allocationN*bytesPerAllocation/bytesInOneKiB << "[KiB] Allocated in the stack" << std::endl;
    }

    // Other possible solution(using multiple stack frames)
    //allocate(0);
    
    return 0;
}

uint64_t sum(uint8_t array[], uint32_t size)
{
    uint64_t totalSum = 0;
    for(uint32_t i=0;i<size;i++)
    {
        totalSum+=array[i];
    }
    return totalSum;
}

void allocate(uint32_t allocationIt)
{
    if(allocationIt<numberOfAllocations)
    {
        char array[bytesPerAllocation-4];
        std::cout << (allocationIt+1)*bytesPerAllocation/bytesInOneKiB << "[KiB] Allocated in the stack" << std::endl;
        allocate(allocationIt+1);
    }
}


