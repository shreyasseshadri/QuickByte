# Segments

A segment is a logical storage unit for the Key Value store. The storage engine maintains all the data stored in the form of Segment(s).

Each segment is attached a file to which it reads and writes data.

`Segment` objects are managed by the `Storage` engine, which calls the APIs of the segment

The `SEGMENT_LIMIT` is the number of bytes that a segment can store.

`segmentSizeLeft` is an attribute exposed by the Segment, for the the storage engine to take decisions, when the segment size is full.

The APIs for segments are 
- **write_to_segment( key, value )** : <br>
    Writes the key and value after the current offset at the file and give back the information for its indexer to index  
- **read_from_segment( key ) -> (is_present,value)** : <br>
    Query the indexer to see the key is stored in its segment, if not return `is_present` as `false`. If present, retrieve the value from its file and return
- **delete_if_exists( key ) -> is_removed** : <br>
    Delete the data if key exists by calling the indexer delete API. It does not actually remove the value from the file, as that will be taken care of in the compaction process.  



