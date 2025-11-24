# Problem: CF 1672 F1 - Array Shuffling
# https://codeforces.com/contest/1672/problem/F1
 
"""
Algorithm: Array Shuffling for Maximum Sadness
Purpose: Given an array 'a', find a permutation 'b' such that the minimum number of swaps to transform 'b' into 'a' is maximized.
Approach:
1. Group indices of elements by their value to form cycles.
2. For each group of indices with the same value, sort them based on the values they point to.
3. Assign new values to these indices such that the resulting array 'b' has maximum sadness.
Time Complexity: O(n log n) due to sorting within cycles
Space Complexity: O(n) for storing counts, cycles, and the new array
"""
 
import sys
 
I = lambda: [*map(int, sys.stdin.readline().split())]  # Fast input helper
 
(t,) = I()
for _ in range(t):
    (n,) = I()
    a = I()
    counts = [0] * (n + 1)  # Count of occurrences of each value
    cycles = []  # List to store indices grouped by value
    
    # Group indices by their values
    for i in range(n):
        val = a[i]
        ind = counts[val]  # Determine which cycle this index belongs to
        if len(cycles) <= ind:
            cycles.append([i])  # Create new cycle if needed
        else:
            cycles[ind].append(i)  # Add index to existing cycle
        counts[val] += 1  # Increment count for this value
 
    new = [0] * n  # Resulting array
    # For each cycle, rearrange indices to maximize swaps needed
    for cycle in cycles:
        cycle.sort(key=lambda x: a[x])  # Sort cycle indices by the values at those indices
        l = len(cycle)
        for i in range(l):
            new[cycle[i - 1]] = a[cycle[i]]  # Assign value from next index in cycle (circular)
    print(*new)
 
 
# https://github.com/VaHiX/CodeForces/