# Indexers

An indexer's job is to quickly retrieve data during queries. The layers above the indexer are agnostic to the implementation details of the indexer, and hence any type of indexer can be used.


Any indexer implementation must extend the `Indexer` interface, after which it must implement 3 APIs

- **index( key, value, offset, size )** : <br>
    This API will be called by the Segment at the time of upsert. The indexer will be given the key, value, the offset at which the value is stored and the size of the value.
    
    Normally the `value` will not be used by most indexers, but it was kept to give a better transparency to the indexer incase some indexer implementations use value
- **retrieve( key ) -> (offset,size)** : <br> 
    This API is called at the time of query. The Segment gives the key to be retrieved and the indexer returns the offset of the file at which the value is stored, and the size of the value. If the key is not found offset must be returned as `-1`
- **remove( key )** : <br>
    This API is called at the time of delete. The indexer is given the key to delete, and the indexer can either remove the key from memory or use a tombstone to signify deleted value

