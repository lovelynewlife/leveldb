# Compaction Rules
## Level 0

When the log file grows above a certain size (4MB by default):
Create a brand new memtable and log file and direct future updates here.

In the background:

1. Write the contents of the previous memtable to an sstable.
2. Discard the memtable.
3. Delete the old log file and the old memtable.
4. Add the new sstable to the young (level-0) level.

## Compactions

When the size of level L exceeds its limit, we compact it in a background
thread. The compaction picks a file from level L and all overlapping files from
the next level L+1. Note that if a level-L file overlaps only part of a
level-(L+1) file, the entire file at level-(L+1) is used as an input to the
compaction and will be discarded after the compaction. 

Aside: because level-0 is special (files in it may overlap each other), we treat compactions from
level-0 to level-1 specially: a level-0 compaction may pick more than one
level-0 file in case some of these files overlap each other.

A compaction merges the contents of the picked files to produce a sequence of
level-(L+1) files.

**Rules:**
* Switch to producing a new level-(L+1) file after the
current output file has reached the target file size (2MB).
* Switch to a new output file when the key range of the current output file has grown enough 
to overlap more than ten level-(L+2) files.  

This last rule ensures that a later compaction of a level-(L+1) file will not pick up too much data from
level-(L+2).

The old files are discarded and the new files are added to the serving state.

Compactions for a particular level rotate through the key space. In more detail,
for each level L, we remember the ending key of the last compaction at level L.
The next compaction for level L will pick the first file that starts after this
key (wrapping around to the beginning of the key space if there is no such
file).

* Compactions drop overwritten values. 
* Drop deletion markers if there are no higher numbered levels that contain a file whose range overlaps the
current key.