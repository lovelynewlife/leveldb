# KeyStructure
## MemTable
```text
MemTable Entry:
    MemTable Key:
        kLength varint32
        Internal Key:
            userkey char[kLength]
            tag uint64
    vLength varint32
    value char[vLength]
```
tag = keyType + sequence number

MemTable is a skip list which is ordered by:
* increasing user key (according to user-supplied comparator)
* decreasing sequence number
* decreasing type (though sequence number should be enough to disambiguate)
    