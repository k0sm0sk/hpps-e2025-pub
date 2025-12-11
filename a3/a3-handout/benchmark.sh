#!/bin/bash

# KNN Performance Benchmark Script
# Tests both bruteforce and kdtree implementations with various dataset sizes

# Build the programs first
make clean && make

# Create results directory if it doesn't exist
mkdir -p benchmark_results

# Define test parameters
DIMENSIONS=2
K=5
NUM_QUERIES=1000

# Test sizes (number of points)
SIZES=(1000 5000 10000 25000 50000)

echo "KNN Performance Benchmark"
echo "========================="
echo "Dimensions: $DIMENSIONS"
echo "K: $K"
echo "Queries: $NUM_QUERIES"
echo ""

# Create results file
RESULTS_FILE="benchmark_results/timing_results.txt"
echo "KNN Performance Benchmark Results" > $RESULTS_FILE
echo "Generated on: $(date)" >> $RESULTS_FILE
echo "Dimensions: $DIMENSIONS, K: $K, Queries: $NUM_QUERIES" >> $RESULTS_FILE
echo "" >> $RESULTS_FILE
echo "Size,Bruteforce_Real,Bruteforce_User,Bruteforce_Sys,KDTree_Real,KDTree_User,KDTree_Sys" >> $RESULTS_FILE

for size in "${SIZES[@]}"; do
    echo "Testing with $size points..."
    
    # Generate test data
    echo "  Generating points and queries..."
    ./knn-genpoints $size $DIMENSIONS > benchmark_results/points_${size}
    ./knn-genpoints $NUM_QUERIES $DIMENSIONS > benchmark_results/queries_${size}
    
    # Test bruteforce
    echo "  Testing bruteforce..."
    TIME_OUTPUT_BF=$(command time -p ./knn-bruteforce benchmark_results/points_${size} benchmark_results/queries_${size} $K 2>&1 | grep -E "^real|^user|^sys")
    BF_REAL=$(echo "$TIME_OUTPUT_BF" | grep "^real" | awk '{print $2}')
    BF_USER=$(echo "$TIME_OUTPUT_BF" | grep "^user" | awk '{print $2}')
    BF_SYS=$(echo "$TIME_OUTPUT_BF" | grep "^sys" | awk '{print $2}')
    
    # Test kdtree
    echo "  Testing kdtree..."
    TIME_OUTPUT_KD=$(command time -p ./knn-kdtree benchmark_results/points_${size} benchmark_results/queries_${size} $K 2>&1 | grep -E "^real|^user|^sys")
    KD_REAL=$(echo "$TIME_OUTPUT_KD" | grep "^real" | awk '{print $2}')
    KD_USER=$(echo "$TIME_OUTPUT_KD" | grep "^user" | awk '{print $2}')
    KD_SYS=$(echo "$TIME_OUTPUT_KD" | grep "^sys" | awk '{print $2}')
    
    # Save results
    echo "$size,$BF_REAL,$BF_USER,$BF_SYS,$KD_REAL,$KD_USER,$KD_SYS" >> $RESULTS_FILE
    
    # Print summary
    printf "  %-8s: Bruteforce: %.3fs  |  KDTree: %.3fs  |  Speedup: %.2fx\n" \
           "${size}" "$BF_REAL" "$KD_REAL" $(echo "scale=2; $BF_REAL / $KD_REAL" | bc -l)
    
    echo ""
done

echo "Benchmark complete! Results saved to: $RESULTS_FILE"
echo ""
echo "Summary:"
echo "--------"
cat $RESULTS_FILE | tail -n +5