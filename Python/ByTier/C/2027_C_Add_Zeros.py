# Problem: CF 2027 C - Add Zeros
# https://codeforces.com/contest/2027/problem/C

"""
C. Add Zeros
Algorithms/Techniques: Greedy, Sorting

Time Complexity: O(n log n)
Space Complexity: O(n)

The problem involves maximizing the length of an array by appending zeros based on certain conditions.
We use a greedy approach with sorting to determine the optimal order of operations. 
By precomputing potential new positions and tracking valid extensions, we can efficiently compute 
the maximum possible array length.

Key idea:
- For each element at index i (1-based), if a[i] = current_length + 1 - i, 
  we can append (i - 1) zeros to the array.
- We process elements in order of increasing value of (a[i] + 1 - i).
- Valid positions are tracked to ensure we don't double count or perform invalid operations.
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n = int(input())
    # Create list of (value + index, original_index) for sorting
    arr = [(i + x, i) for i, x in enumerate(map(int, input().split()))]
    arr.sort(key=lambda x: x[0])  # Sort by value + index to process greedily
    valid = {n}  # Set of currently valid indices where operations can be performed
    ans = n  # Initial array length
    for x, add in arr:
        # If current position is valid, perform operation
        if x in valid:
            valid.add(x + add)  # Add new valid index after appending zeros
            if x + add > ans:
                ans = x + add  # Update maximum length
    print(ans)


# https://github.com/VaHiX/codeForces/