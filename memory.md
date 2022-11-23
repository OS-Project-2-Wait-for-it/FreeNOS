# Inspect the FreeNOS Memory  
  
Requirements:  
  ~ inspect how FreeNOS manages process memory  
  ~ report what kind of memory management system FreeNOS is using, with numbers, characteristics, duration, dynamics, etc.  
  ~ Observation should be specific, detailed, and supported with specific code reference to the vanilla FreeNOS (directory/file/line number of code quoted)  
  ~ The report should be written using ".md" format, showing off your MD file formatting skills  

Notes:  
heap allocator  
lib/libarch/memory.h, contains address virt, address, phys, size, access  
libipc, implements user-space IPC using shared memory  
Dynamic and Shared memory  
Shared and Private Memory mappings support in MemoryServer  
Simplified virtual FileSystems by using synchroneous I/O and Shared memory mappings  
core manager  
