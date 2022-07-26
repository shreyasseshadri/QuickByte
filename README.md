# QuickByte

## About the Project

A Key Value store, where the underlying storage exits either in-memory or on-disk. This project is aimed at implementing a Key Value store inspired by the **3rd chapter of Designing Data-Intensive Applications, by Martin Kleppmann**. The aim was to follow the progression of designs that he describes in the chapter, and implement them.

## Simple Segments with Hash Map

He starts off with a simple linked list of segments (which are a logical entity of storage) that store data onto their respective files, while having an indexer inside each segment.

This design has some problems.

- The indexer being within the segment will not have the knowledge of keys outside its segment. In the worst case the storage engine will have to traverse the entire list of segments and query their indexers to retrieve the value, if it all it exists 
- Even though the keys are distributed, its not controlled, and hence for every query we would have to query the indexer of the latest segment to find if the key exists, which may bleed back towards the previous segments, hence duplicating the query load across potentially multiple segments
- Indexer being in-memory which has a limited space. Along with which it would restrict the number of keys that a single segment can hold
- Compaction process is very computationally intensive


## Memtable and SSTable

An extension of the previous design is to have an in-memory data structure that stores keys, called the *memtable*. Since at some point we are bound to run out of memory, after which we write out this sorted list of keys to disk, creating the *SSTable* (Sorted String Table).

We can then use our  design of segments to store the previous keys on the disk.

An advantage of having an indexer within the segment becomes apparent here, as we only need to write this sorted list of keys into the segment, after which keys can be retrieved quickly with segment having an inbuilt indexer.


This approach still retains the problems of segments and indexer 

Some advantages of this design over the previous:
- Since the contents of each segment is sorted, the compaction process become much simpler.
- Even though the memory for the indexer is a bottle neck, we can try to cut down the memory used by using a sparse index, since the entries in the segment are sorted


## Summary of what is done

- There are two main components involved, Segments and a memtable, both of which have their basic APIs implemented
- A linked list is being used to keep track of segments and to preserve memory (as opposed to using an array)
- A hash map is being used as an indexer
- A BST is being used for the memtable. A lot of effort went into desigining the BST with as few amount of simultaneous latches as possible, to allow multiple threads to mutate the BST simultaneously without blocking rest of the tree. <br> **Currently the test suite spawns 10,000 threads which issue upserts, retrieves, and delete calls on the BST, taking an average time of about 257ms (averaged over 100 times)**

## Details about implementation
- [Storage](/storage/README.md)
- [Segment](/segment/README.md)
- [Indexer](/indexers/README.md)

## High Level design

<p align="center">
  <img src="https://user-images.githubusercontent.com/28723932/180716372-cdaa0e8a-cd7e-43be-8024-e549e20e3a65.png" />
</p>

### Future work
- The Segments have to be made thread safe
- The compaction process is to be implemented
- Once BST reaches a certain memory threshold, an inorder traversal write operation must be performed into segments
- Over the network file access

## Instructions to run

### Server

To compile the sever
```
make server
```
To run
```
./server/server.out
```

### Client

Client uses GNU's `readline` library

```
sudo apt-get install libreadline6 libreadline6-dev
```

To compile the client
```
make compile-cli
```
To run,
```
./cli/cli.out
```


### Testing

#### Testing the Query Processor
```
make test-query-engine
./test.out
```

#### Testing the in-memory storage engine
```
make test
./test.out
```

## CLI 
![Screenshot from 2022-07-22 23-55-44](https://user-images.githubusercontent.com/28723932/180642192-d5007558-8322-46c5-85ba-644cce869df1.png)


## Team
* [shreyasseshadri](https://github.com/shreyasseshadri) - Developer
* [srinskit](https://github.com/srinskit) - Program Manager
