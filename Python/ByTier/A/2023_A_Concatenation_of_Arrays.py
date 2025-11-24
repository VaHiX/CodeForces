# Problem: CF 2023 A - Concatenation of Arrays
# https://codeforces.com/contest/2023/problem/A

"""
Algorithm: Concatenation of Arrays to Minimize Inversions
Purpose: Given n arrays of length 2, concatenate them to form a single array with minimum inversions.
Approach:
1. For each array a[i] = [a[i][0], a[i][1]], compute the sum of its elements.
2. Sort the arrays in ascending order of their element sums.
3. Concatenate the sorted arrays sequentially to form the result.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the input and result arrays.

This greedy approach works because placing arrays with smaller sums earlier in the sequence reduces
the chance of creating inversions when elements from later arrays are placed.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):  # Process each test case
    n = int(input())  # Read number of arrays
    X = [list(map(int, input().split())) for _ in range(n)]  # Read all arrays
    X.sort(key=lambda x: x[1] + x[0])  # Sort by sum of elements in ascending order
    Y = []
    for i in X:
        Y += i  # Concatenate all arrays
    print(*Y)  # Print the concatenated result


# https://github.com/VaHiX/CodeForces/