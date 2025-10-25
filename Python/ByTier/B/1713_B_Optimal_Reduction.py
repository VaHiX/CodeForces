# Problem: CF 1713 B - Optimal Reduction
# https://codeforces.com/contest/1713/problem/B

"""
B. Optimal Reduction

Purpose:
This code determines whether a given array has the property that its minimum number of operations 
to reduce all elements to zero (using a specific operation: select a subarray and decrease all elements by 1) 
is minimized among all permutations of the array.

Algorithms/Techniques:
- Greedy approach with reverse iteration
- Key insight: The minimal number of operations equals the sum of differences between consecutive elements in a sorted order from right to left, plus the first element

Time Complexity: O(n log n) per test case due to sorting (the comparison is implicit in the logic)
Space Complexity: O(1) additional space excluding input storage

The algorithm works by simulating the process from right to left and accumulating the required operations,
comparing it with just the maximum element in the array.

Input:
- Number of test cases t
- For each test case:
  - n (length of array)
  - Array of n integers

Output:
- YES if the current array is optimal among all permutations, NO otherwise.
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = max(arr)  # Maximum element represents a lower bound on operations
    res = arr[0]    # Start with first element
    for i in range(n - 1, 0, -1):  # Traverse from right to left
        res += max(0, arr[i] - arr[i - 1])  # Accumulate difference if positive
    print("YES" if res == ans else "NO")  # Compare result with maximum element


# https://github.com/VaHiX/codeForces/