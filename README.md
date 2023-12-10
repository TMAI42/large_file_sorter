# Large file sorter  

## Overview
Program that sorts double precision numbers stored in a text file of size 1GB (one number per line). 

Input example:
```text 
8.33891e+307
1.26192e+308
8.19572e+307
...
0
1.64584e+304
```

It based on standard [External sorting](https://en.wikipedia.org/wiki/External_sorting) algorithm:

1. **Divide** data into smaller 'chunks'
2. **Sort** each chunk and **write** them back to the external memory (disk)
3. **Merge** sorted chunks into output file 

### Prerequisites
- C++23 compatible compiler
- CMake (version 3.26 or higher)

## Quick Start

### Build
```bash
mkdir build
cd build
cmake ..
make
```

### Run

```bash
./large_file_sorter name_of_unsorted_file name_of_sorted_file
```

Additionally, you can generate large file, and iterate through it. See:
```text
./large_file_sorter 
    --generate=filename  : Generate file of size 1GB with given name 
    --iterate=filename   : Iterate through file line by line
    inputFile outputFile : Sort given inputFile into outputFile
```

## Core features

- **Generator for unsorted file**. Implemented generator to get numbers from file one by one 
- **Generate large file**. Implemented large file generation to test

## Performance benchmarking 

| Experiment number | File size (GB) | Time (s) | RAM Usage (MB) | Additional Hard drive usage (MB) |
|-------------------|----------------|----------|----------------|----------------------------------|
| 1                 | 1.1            | 152      | 71,798         | 660.08                           |
| 2                 | 1.1            | 163      | 71,796         | 660.08                           |
| 3                 | 1.1            | 158      | 71,82          | 660.08                           |

## Note

This task could be much easier for binary file, in this case we would be able to implement efficient inplace sort as explained in [An Efficient External Sort Algorithm with no Additional Space](https://www.researchgate.net/publication/220460059_An_Efficient_External_Sort_Algorithm_with_no_Additional_Space_Short_Note).
But this task is almost imposable due data structure: we are using strings as data, so each individual element 
could have different size

## Resources 

- [External sorting](https://en.wikipedia.org/wiki/External_sorting)
- [k-way merge algorithm](https://en.wikipedia.org/wiki/K-way_merge_algorithm)
- [An Efficient External Sort Algorithm with no Additional Space](https://www.researchgate.net/publication/220460059_An_Efficient_External_Sort_Algorithm_with_no_Additional_Space_Short_Note)

