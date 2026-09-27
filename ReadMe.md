# mmalloc

Just a basic malloc implementation in hopes of learning **C** better.

TODO: 
- Combining free blocks of data into big ones
- Handle 4096 bytes allocation
- Fix the free block search
- If necessary split big blocks into smaller ones, cause we loose data when reusing block that is much smaller then previous owner.
