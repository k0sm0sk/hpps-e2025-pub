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
