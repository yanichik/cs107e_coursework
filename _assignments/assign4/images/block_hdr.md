---
title: 'Heap allocator diagrams'
layout: page
---

### Block payload and header

We refer to the heap space allocated for a client's request as a _block_.
When the client requests space, the heap must choose a block of
sufficient size to service the request. The client's data is what is
called the _payload_ of the block. In addition to setting aside space for 
the payload, a heap allocator typically needs to manage some metadata 
for each block that tracks its size and status. One convenient way
to store the metadata is reserving the memory preceding the block
payload to store a block header. This technique is quite efficient
in that simple pointer arithmetic can be used to move from the payload to 
the header and back, no lookup required.

Consider this struct definition for a block header:

    struct header {
        size_t payload_size;
        int status;       // 0 if free, 1 if in use
    };

`sizeof(struct header)` will require 8 bytes.
Assume the entire heap is of size 0x40 bytes and starts at address 0x9000. 
To configure the entire heap as one block, the block payload would start
at 0x9008 and the preceding 8 bytes would be its header struct. The size of 
the block payload is 0x38 bytes, the status is 0 (freed). The heap looks like this:

Address|Contents|&nbsp;
-------|--------|-----------
[0x903c] | xx xx xx xx | 
[0x9038] | xx xx xx xx | 
[0x9034] | xx xx xx xx | 
[0x9030] | xx xx xx xx | 
[0x902c] | xx xx xx xx | 
[0x9028] | xx xx xx xx | 
[0x9024] | xx xx xx xx | 
[0x9020] | xx xx xx xx | 
[0x901c] | xx xx xx xx | 
[0x9018] | xx xx xx xx | 
[0x9014] | xx xx xx xx | 
[0x9010] | xx xx xx xx | 
[0x900c] | xx xx xx xx | 
[0x9008] | xx xx xx xx | payload starts here
[0x9004] | 00 00 00 00 | hdr.status
[0x9000] | 00 00 00 38 | hdr.payload_size


<style type='text/css'>
table 
{ font-family: Consolas;
  font-size: 9pt;
  border-collapse: collapse;
  border: none;
}
td:nth-child(2) {
   border-left: 1px solid black; 
   border-right: 1px solid black; 
}
tr td  {
   padding: 1px 10px 1px 10px !important;
}
</style>


Now consider splitting that one free block into two blocks: 
an in-use block with a payload size of 0x10 and a remainder free block. 
The header for the first block is still at 0x9000, but its header is
updated to show the payload_size is now 0x10 and status is in-use. 
The remainder block has its header at address 0x9018. Its payload
size is 0x20 and its status is freed.

After the split, the heap now looks like this:

Address|Contents|&nbsp;
-------|--------|-----------
[0x903c] | xx xx xx xx | 
[0x9038] | xx xx xx xx | 
[0x9034] | xx xx xx xx | 
[0x9030] | xx xx xx xx | 
[0x902c] | xx xx xx xx | 
[0x9028] | xx xx xx xx | 
[0x9024] | xx xx xx xx | 
[0x9020] | xx xx xx xx | payload starts here
[0x901c] | 00 00 00 00 | hdr.status
[0x9018] | 00 00 00 20 | hdr.payload_size
[0x9014] | xx xx xx xx | 
[0x9010] | xx xx xx xx | 
[0x900c] | xx xx xx xx | 
[0x9008] | xx xx xx xx | payload starts here
[0x9004] | 00 00 00 01 | hdr.status
[0x9000] | 00 00 00 10 | hdr.payload_size


Given a heap that is laid out with block headers like this, do you see how to advance from one header to the subsequent header?  What about if given the address of the payload (such as the argument to a `free()` call), how can you access the header associated with that payload?

Make sure you understand pointer arithmetic and the distinction in scaling applied when adding to an `int *` versus a `char *` versus a `struct hdr *` versus n `unsigned int`!


