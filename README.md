# KoolKey
A Kool Key Value store

## Initial Plan

- [X] Make an executable that given a key value pair must append it to a file
- [X] Write an indexer that contains the byte offset in the file as we append keys
- [X] Provide querying API that first indexes the key and then writes, and then retrieves
- [ ] Setup CI and git hooks to run test case file on every commit
- [ ] Provide persistant storage to the indexer


> NOTE: CLI support can be provided once project has reached some major milestone. For now we test using test case files directly calling the APIs

## Team
* [shreyasseshadri](https://github.com/shreyasseshadri) - Developer
* [srinskit](https://github.com/srinskit) - Program Manager