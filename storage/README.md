# Storage

The `Storage` is the main class that exposes the top most APIs for the storage engine which are `upsert`, `delete`, `retrieve`.

Currently two implementations exist for Storage and a specific type of instance can be requested from the factory method of Storage, by passing in the type of engine required from the enum `StorageType`.

## In memory Storage

Data is stored on memory, this is essentially a **memtable**. A BST has been used for its implementation.

The BST implementation is under [`/utils/bst`](/utils/bst/).


An array or a hash index is avoided as they use a lot more space than BST, which allocates memory dynamically as and when required. It is much faster to search than a dynamically allocated Linked List, and it is cleanly divisble in terms of search space of keys, which helps in latching only at the necessary places.

A lot of effort has gone into making the BST data structure as optimized for mutation as possible, avoiding lots of simultaneous latches. 

## On Disk Storage

A specific type of indexer instance can be used for segments from the constructor of the on disk storage, by passing in the type of enginer required from the enum `IndexerType`

This specific implementation is incharge of managing a linked list of segments.

- An insert is inserted at the latest current segment.
- In case of a retrieve, the current segment is asked to retrieve the key, if not present we check the previous segment and so on.
- In case of delete, there are two ways
    - Use a tombstone on the latest segment the key is found, that way we do not have to delete the duplicate in even previous segments. But this would force the indexer having to use tombstone, making the segment and storage dependent on indexer implementation
    - Delete the entry in all of the segments. This is the current implementation