# Database-Indexing

## B+ Trees

### To Run:
- g++ btree.cpp
- ./a.out <file>

### Insert
We traverse to the appropriate leaf node and insert the value in that node. If the size of the
node is greater than N, then we split the node into N1 and N2 and pass on the first value of
the N2 to the parent. Then we recursively insert in the parent until we reach the root.
Finally, if the root needs to be split, then we add a new root.

### Find
We traverse to the leaf node by making use of c++ upper_bound() function which gives the
pointer we want to search in. Once we reach the lead node, binary_search() tells us if the
required value if present or not.

### Count
We traverse to the appropriate leaf node and count the occurences of that particular value.

### Range
We traverse to the leaf containing a value just greater than or equal to x and using the leaf
pointers move to adjacent leaves till we encounter a value greater than or equal to y.

## Linear Hashing

### To Run:
- g++ linhash.cpp
- ./a.out <file>

We compute h(K), where K is the key of the record, and we use the i bits at the end of bit
sequence h(K) as the bucket number, m. If m < n, we first search for the record in bucket m,
and if m >= n, in bucket m — 2^(i-1). If the record is not found, we proceed to insert in the
same bucket number calculated before. If there is no room in the bucket, then we create
an overflow block, add it to the chain for that bucket,and put the record there. Each time
we insert, we compare the current number of records r with the threshold ratio of r/t (t
being total number of records that can be held), and if the ratio is too high, we add the next
bucket to the table. If the binary representation of the number of the bucket we add is
1a2•••ai, then we split the bucket numbered 0a2•••ai, putting records into one or the other
bucket, depending on their last i bits. The last important detail is what happens when n
exceeds 2^i. Then, i is incremented by 1. The data blocks in each bucket is 1KB of data
(excluding pointer to overflow), and the threshold is set at 0.75 (75%).
