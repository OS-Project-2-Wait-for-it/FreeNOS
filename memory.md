# Inspect the FreeNOS Memory

Contributions: Shane Dirksen
  
### Requirements:  
  ~ inspect how FreeNOS manages process memory  
  ~ report what kind of memory management system FreeNOS is using, with numbers, characteristics, duration, dynamics, etc.  
  ~ Observation should be specific, detailed, and supported with specific code reference to the vanilla FreeNOS (directory/file/line number of code quoted)  
  ~ The report should be written using ".md" format, showing off your MD file formatting skills  

### Summary:  

The Allocator class defines the abstract memory allocation. It forms a hierarchy of parent-children relationships. If a child does not have enough memory, it can request more from the parent. Classes that inherit from the Allocator include: BitAllocator, BubbleAllocator, PageAllocator, PoolAllocator, and Split Allocator. These files are located in `lib/liballoc/`  

The Pool Allocator manages same-sized obkects and allocates memory from pools, with each pool being a power of two. Pools are pre-allocated with a bitmap that represents free blocks. The Pool struct allocates same sized objects from a contiguous block of memory. It contains pointers called "next" and "prev" that points to the next/previous pool of a specified size.  

The Bit Allocator contains BitArray, which scans the array for open bits. All memory is divided into equally sized parts called chunks. '1' signals that the chunk is used and '0' is free. The creator(s) of the OS note that this is inefficient, because a caller could be unlucky and need to scan the entire array for a free bit; the Linux kernel uses a more efficient method called a "buddy allocator," which combines bit arrays and linked lists.  

The Bubble Allocator continually grows allocated memory and cannot free the memory.  
The Page Allocator allocates virtual memory using the memory server. An incomplete issue is that the release() function at line 73 does not release memory back to the system, which may result in fragmented virtual memory that would cause issues for higher-level allocators.  

The Split Allocator separates kernel mapped memory at virtual and physical addresses.  The allocate() function allocates one physical memory page.

### Notes:  
heap allocator  
`lib/libarch/memory.h`, contains address virt, address, phys, size, access  
libipc, implements user-space IPC using shared memory	  
Dynamic and Shared memory  
Shared and Private Memory mappings support in MemoryServer  
Simplified virtual FileSystems by using synchroneous I/O and Shared memory mappings  
core manager  
  
`kernel/processshares.h` -> contains struct MemoryShare, coreID, share tag, physical memory address range  

`lib/liballoc/alloctor.h` -> Memory Allocator  

