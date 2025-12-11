#!/bin/bash

# Comprehensive KNN Performance Benchmark Script
# Tests both bruteforce and kdtree implementations with various:
# - Dataset sizes
# - Dimensions
# - K values

# Build the programs first
make clean && make

# Create results directory if it doesn't exist
mkdir -p benchmark_results

# Define test parameters
NUM_QUERIES=500  # Reduced for faster testing with multiple dimensions

# Test configurations
SIZES=(1000 5000 10000 25000)
DIMENSIONS=(2 3 5 10 20)
K_VALUES=(1 5 10 20)

echo "Comprehensive KNN Performance Benchmark"
echo "======================================="
echo "Queries: $NUM_QUERIES"
echo ""

# Create comprehensive results file
RESULTS_FILE="benchmark_results/comprehensive_timing_results.txt"
echo "Comprehensive KNN Performance Benchmark Results" > $RESULTS_FILE
echo "Generated on: $(date)" >> $RESULTS_FILE
echo "Queries: $NUM_QUERIES" >> $RESULTS_FILE
echo "" >> $RESULTS_FILE
echo "Size,Dimensions,K,Bruteforce_Real,Bruteforce_User,Bruteforce_Sys,KDTree_Real,KDTree_User,KDTree_Sys,Speedup" >> $RESULTS_FILE

total_tests=$((${#SIZES[@]} * ${#DIMENSIONS[@]} * ${#K_VALUES[@]}))
current_test=0

for size in "${SIZES[@]}"; do
    for dim in "${DIMENSIONS[@]}"; do
        for k in "${K_VALUES[@]}"; do
            current_test=$((current_test + 1))
            echo "Test $current_test/$total_tests: ${size} points, ${dim}D, K=${k}"
            
            # Generate test data
            echo "  Generating data..."
            ./knn-genpoints $size $dim > benchmark_results/points_${size}_${dim}d
            ./knn-genpoints $NUM_QUERIES $dim > benchmark_results/queries_${size}_${dim}d
            
            # Test bruteforce
            echo "  Testing bruteforce..."
            TIME_OUTPUT_BF=$(command time -p ./knn-bruteforce benchmark_results/points_${size}_${dim}d benchmark_results/queries_${size}_${dim}d $k 2>&1 | grep -E "^real|^user|^sys")
            BF_REAL=$(echo "$TIME_OUTPUT_BF" | grep "^real" | awk '{print $2}')
            BF_USER=$(echo "$TIME_OUTPUT_BF" | grep "^user" | awk '{print $2}')
            BF_SYS=$(echo "$TIME_OUTPUT_BF" | grep "^sys" | awk '{print $2}')
            
            # Test kdtree
            echo "  Testing kdtree..."
            TIME_OUTPUT_KD=$(command time -p ./knn-kdtree benchmark_results/points_${size}_${dim}d benchmark_results/queries_${size}_${dim}d $k 2>&1 | grep -E "^real|^user|^sys")
            KD_REAL=$(echo "$TIME_OUTPUT_KD" | grep "^real" | awk '{print $2}')
            KD_USER=$(echo "$TIME_OUTPUT_KD" | grep "^user" | awk '{print $2}')
            KD_SYS=$(echo "$TIME_OUTPUT_KD" | grep "^sys" | awk '{print $2}')
            
            # Calculate speedup
            SPEEDUP=$(echo "scale=2; $BF_REAL / $KD_REAL" | bc -l)
            
            # Save results
            echo "$size,$dim,$k,$BF_REAL,$BF_USER,$BF_SYS,$KD_REAL,$KD_USER,$KD_SYS,$SPEEDUP" >> $RESULTS_FILE
            
            # Print summary
            printf "  Result: BF: %.3fs | KD: %.3fs | Speedup: %sx\n" "$BF_REAL" "$KD_REAL" "$SPEEDUP"
            echo ""
        done
    done
done

echo "Comprehensive benchmark complete! Results saved to: $RESULTS_FILE"
echo ""

# Generate analysis script
cat > benchmark_results/analyze_results.py << 'EOF'
#!/usr/bin/env python3
import pandas as pd
import numpy as np

# Read the results
df = pd.read_csv('comprehensive_timing_results.txt', skiprows=4)

print("=== KNN Performance Analysis ===\n")

# Average speedup by dimension
print("Average Speedup by Dimension:")
speedup_by_dim = df.groupby('Dimensions')['Speedup'].mean().sort_index()
for dim, speedup in speedup_by_dim.items():
    print(f"  {dim}D: {speedup:.2f}x")
print()

# Average speedup by K value
print("Average Speedup by K value:")
speedup_by_k = df.groupby('K')['Speedup'].mean().sort_index()
for k, speedup in speedup_by_k.items():
    print(f"  K={k}: {speedup:.2f}x")
print()

# Average speedup by dataset size
print("Average Speedup by Dataset Size:")
speedup_by_size = df.groupby('Size')['Speedup'].mean().sort_index()
for size, speedup in speedup_by_size.items():
    print(f"  {size}: {speedup:.2f}x")
print()

# Best and worst performing configurations
best_config = df.loc[df['Speedup'].idxmax()]
worst_config = df.loc[df['Speedup'].idxmin()]

print("Best Performance Configuration:")
print(f"  Size: {best_config['Size']}, Dim: {best_config['Dimensions']}, K: {best_config['K']}")
print(f"  Speedup: {best_config['Speedup']:.2f}x (BF: {best_config['Bruteforce_Real']:.3f}s, KD: {best_config['KDTree_Real']:.3f}s)")
print()

print("Worst Performance Configuration:")
print(f"  Size: {worst_config['Size']}, Dim: {worst_config['Dimensions']}, K: {worst_config['K']}")
print(f"  Speedup: {worst_config['Speedup']:.2f}x (BF: {worst_config['Bruteforce_Real']:.3f}s, KD: {worst_config['KDTree_Real']:.3f}s)")
print()

# Effect of dimensionality on performance
print("Dimensionality Effect Analysis:")
print("(Higher dimensions tend to reduce KD-tree effectiveness)")
for dim in sorted(df['Dimensions'].unique()):
    dim_data = df[df['Dimensions'] == dim]
    avg_speedup = dim_data['Speedup'].mean()
    avg_bf_time = dim_data['Bruteforce_Real'].mean()
    avg_kd_time = dim_data['KDTree_Real'].mean()
    print(f"  {dim}D: Avg BF={avg_bf_time:.3f}s, Avg KD={avg_kd_time:.3f}s, Avg Speedup={avg_speedup:.2f}x")
EOF

chmod +x benchmark_results/analyze_results.py

echo "Analysis script created at: benchmark_results/analyze_results.py"
echo "Run 'cd benchmark_results && python3 analyze_results.py' to analyze the results"