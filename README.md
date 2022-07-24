# QuickByte

A Key Value store, where the underlying storage exits either in-memory or on-disk. 
Initially starting off as an implementation of a basic DB using an append only file, now has evolved into a key-value store, having a BST that can be operated on by large number of threads.

Although both in-memory and on-disk options are supported, a lot more work has gone in to making the on-disk BST as efficient as possible, as a result there are lots of scope for improvement on the outer layers of the key-value store such as the Query Processor and the Server.

## High Level design

```mermaid
  flowchart TD
  A[Client] ---> C[Server]
  B[Client] ---> C
  C --> D[Query Processor Engine]
  D --> E[Storage Engine]
  E --> F{Storage Type}
  
 
  F --In Memory--> L[BST on memory]
  F --On Disk--> G1
  
  subgraph G1[Linked List of Segments]
  direction LR
  A1[Segments] --> B1[Segments]
  end
  
  subgraph G2[Each Segment]
  direction LR
  C1[Indexer] --> D1{File Storage}
  D1 --Local Storage--> E1[Append Only File Storage]
  D1 --Over the network --> E1
  end
  
  G1 -->  G2
```
## Instructions to run

### Client

Client uses GNU's `readline` library

```
sudo apt-get install libreadline6 libreadline6-dev
```

To compile the client
```
make cli
```
To run,
```
./cli/cli.out
```

### Server

To compile the sever
```
make server
```
To run
```
./server/server.out
```

### Testing

#### Testing the Query Processor
```
make test-query-engine
./test.out
```
Currently tested 10,000 threads upserting, deleting and writing into the bst concurrently 
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
