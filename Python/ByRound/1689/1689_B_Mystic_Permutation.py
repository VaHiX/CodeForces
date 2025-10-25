# Problem: CF 1689 B - Mystic Permutation
# https://codeforces.com/contest/1689/problem/B

"""
B. Mystic Permutation
Algorithms/Techniques: Greedy, Sorting

Time Complexity: O(n^2) per test case due to swapping operations in worst case
Space Complexity: O(n) for storing the permutation and its sorted version

The problem asks to find the lexicographically smallest permutation that differs 
from the given one at every position. 

Approach:
1. Sort the input permutation to get the lexicographically smallest possible arrangement.
2. Try to place elements in such a way that no element is at its original position.
3. If we can't achieve this (i.e., when n == 1), output -1.
4. Otherwise, perform swaps to ensure all positions are different, handling edge cases 
   like duplicates or already sorted inputs carefully.

The solution works by attempting to build a valid permutation greedily through 
sorting and then fixing conflicts with adjacent elements, ensuring lexicographical minimality.
"""

import sys

for _ in range(int(input())):
    n = int(input())
    p = list(map(int, sys.stdin.readline().split()))
    if n == 1:
        print(-1)
        continue
    q = sorted(p)  # Create sorted version for minimal lexicographical result
    
    # Swap adjacent elements to ensure current element is not at same index
    for i in range(n - 1):
        if p[i] == q[i]:
            q[i], q[i + 1] = q[i + 1], q[i]  # Swap to break the match
    
    # Handle case where last element still matches original
    if p[-1] == q[-1]:
        q[-1], q[-2] = q[-2], q[-1]  # Ensure final position is also broken
    
    print(*q)


# https://github.com/VaHiX/codeForces/