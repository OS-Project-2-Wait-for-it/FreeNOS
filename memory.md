# Inspect the FreeNOS Memory

Contributions: Shane Dirksen
  
### Requirements:  
  - Inspect how FreeNOS manages process memory  
  - Report what kind of memory management system FreeNOS is using, with numbers, characteristics, duration, dynamics, etc.  
  - Observation should be specific, detailed, and supported with specific code reference to the vanilla FreeNOS (directory/file/line number of code quoted)  
  - The report should be written using ".md" format, showing off your MD file formatting skills  

### Summary:  

The Allocator class defines the abstract memory allocation. It forms a hierarchy of parent-children relationships. If a child does not have enough memory, it can request more from the parent. Classes that inherit from the Allocator include: BitAllocator, BubbleAllocator, PageAllocator, PoolAllocator, and Split Allocator. These files are located in `lib/liballoc/`  

![image](https://user-images.githubusercontent.com/87223787/204167767-68d50752-e3fa-4b18-ab0f-3d21188d9809.png)

The Pool Allocator manages same-sized objects and allocates memory from pools, with each pool being a power of two. Pools are pre-allocated with a bitmap that represents free blocks. The Pool struct allocates same sized objects from a contiguous block of memory. It contains pointers called "next" and "prev" that points to the next/previous pool of a specified size.  

The Bit Allocator contains BitArray, which scans the array for open bits. All memory is divided into equally sized parts called chunks. '1' signals that the chunk is used and '0' is free. The creator(s) of the OS note that this is inefficient because a caller could be unlucky and need to scan the entire array for a free bit; the Linux kernel uses a more efficient method called a "buddy allocator," which combines bit arrays and linked lists.  

The Bubble Allocator continually grows allocated memory and cannot free the memory.  
The Page Allocator allocates virtual memory using the memory server. An incomplete issue is that the release() function at line 73 does not release memory back to the system, which may result in fragmented virtual memory that would cause issues for higher-level allocators.  

The Split Allocator separates kernel mapped memory at virtual and physical addresses.  The allocate() function allocates one physical memory page.  

`kernel/kernel.cpp` line 108 contains initializeHeap() function, which sets up the kernel heap for dynamic memory allocation. It uses new() and delete() operators and it is called before any object is created using new()  

`lib/libarch/MemoryMap.h` contains the virtual memory map layout and is the parent to the ARMMap and IntelMap classes, which define the memory maps for ARM and Intel architectures Currently limited to 1GB of supported system memory. The memory is delineated into several memory regions, which are available on the system. The regions are labeled by predefined virtual memory ranges and the virtual memory address range of each depends on the architecture implementation.  

Within `kernel/intel`, looking at the Intel implementation, the `IntelKernel.cpp` contains a function called memContext, that refreshes and uses the SplitAllocator. It also calls the `MemoryBlock` to fill the Task State Segment (TSS). MemoryBlock is located in `lib/libstd` and sets, copies, and compares memory blocks.  

Within `kernel`, the file ProcessManager.cpp has a function create() for creating processes, that has a MemoryMap argument. Here there are variables such as KernelData, UserData, UserHeap, and UserStack. Here new memory range values for the memory region are defined. The namespace Memory has flags for readable, writeable, executable, user, uncached, InnerCached, OuterCached, and device; it also contains the struct Range that has the virtual address, the physical address, the size, and access flag at line 40-48. 

![Animation](https://user-images.githubusercontent.com/87223787/204168264-678e6d3a-c9f3-47d1-93a6-4a137b1b221b.gif)


### Notes:  
heap allocator  
`lib/libarch/memory.h`, contains address virt, address, phys, size, access  
libipc, implements user-space IPC using shared memory	  
Dynamic and Shared memory  
Shared and Private Memory mappings support in MemoryServer  
Simplified virtual FileSystems by using synchronous I/O and Shared memory mappings  
core manager  
  
`kernel/processshares.h` -> contains struct MemoryShare, coreID, share tag, physical memory address range  

`lib/liballoc/alloctor.h` -> Memory Allocator  

