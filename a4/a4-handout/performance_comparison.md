# Query Performance Comparison

This document compares the performance of different approaches for querying records:

## ID Query Methods
1. **Naive**: Linear search through all records
2. **Indexed**: Hash table-based indexing
3. **Binsort**: Binary search on sorted data

## Coordinate Query Methods
4. **Coord_query_naive**: Linear search for coordinate-based queries

## Test Setup

- **ID Query Set**: 100 random IDs from respective datasets
- **Coordinate Query Set**: 10 coordinate pairs
- **Dataset Sizes**: 20,000 records (50,000 unavailable due to empty dataset)
- **Metrics**: Reading time, index building time, total query time

## Results

### 20,000 Records Dataset - ID Queries

| Approach | Reading Time | Index Building | Total Query Time (100 queries) | Avg Query Time |
|----------|--------------|----------------|--------------------------------|----------------|
| Naive    | 19ms         | 0ms           | 2,960μs                        | 29.6μs         |
| Indexed  | 17ms         | 0ms           | 1,509μs                        | 15.1μs         |
| Binsort  | 17ms         | 3ms           | 47μs                           | 0.47μs         |

### 20,000 Records Dataset - Coordinate Queries

| Approach           | Reading Time | Index Building | Total Query Time (10 queries) | Avg Query Time |
|-------------------|--------------|----------------|-------------------------------|----------------|
| Coord_query_naive | 21ms         | 0ms           | 2,359μs                       | 235.9μs        |

### 1,000 Records Dataset - Coordinate Queries (for comparison)

| Approach           | Reading Time | Index Building | Total Query Time (10 queries) | Avg Query Time |
|-------------------|--------------|----------------|-------------------------------|----------------|
| Coord_query_naive | 1ms          | 0ms           | 84μs                          | 8.4μs          |

## Analysis

### ID Query Performance
- **Binsort** provides exceptional query performance (~0.47μs average) for 20K records
- **Indexed** offers good performance (~15.1μs average) with hash table lookups
- **Naive** shows the slowest performance (~29.6μs average) with linear search

### Coordinate Query Performance
- **Coord_query_naive** shows significant performance degradation with dataset size
- 20K records: ~235.9μs average query time
- 1K records: ~8.4μs average query time
- Linear scaling behavior as expected for naive coordinate search

### Scalability Comparison
- **ID Binsort**: Excellent scalability with logarithmic search performance
- **ID Indexed**: Good scalability with near-constant hash table performance
- **ID Naive**: Linear search but relatively fast for individual record access
- **Coord_query_naive**: Poor scalability due to distance calculations for all records

### Index Building Cost
- **ID approaches**: Minimal overhead (0-3ms for Binsort sorting)
- **Coordinate approaches**: No indexing implemented in naive version

### Performance Recommendations

#### For ID-based queries:
- **Few queries**: Use **Naive** approach (no index overhead)
- **Moderate loads**: Use **Indexed** approach (balanced performance/memory)
- **High query loads**: Use **Binsort** for optimal performance

#### For coordinate-based queries:
- Current **naive** approach is inefficient for large datasets
- Consider implementing spatial indexing (R-tree, KD-tree) for better performance
- Current approach suitable only for small datasets (<1000 records)

### Dataset Size Impact
- **20,000 vs 1,000 records**: ~28x performance degradation for coordinate queries
- ID queries show much better scaling characteristics
- Coordinate queries would benefit significantly from spatial indexing

## Test Limitations

- 50,000 record dataset was unavailable (empty file)
- Coordinate queries tested with only naive implementation
- Limited to single-threaded performance testing