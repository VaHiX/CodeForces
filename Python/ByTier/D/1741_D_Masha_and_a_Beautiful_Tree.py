# Problem: CF 1741 D - Masha and a Beautiful Tree
# https://codeforces.com/contest/1741/problem/D

"""
Algorithm: Tree Sorting via Swap Operations
This solution determines the minimum number of swaps required to sort a binary tree 
represented as a permutation in a specific way. The key idea is to recursively check 
and fix the ordering of elements in pairs at each level of the tree.

Approach:
- The permutation represents the leaves of a complete binary tree.
- We process the tree level by level from bottom to top.
- For each level, we check if adjacent elements in pairs are in correct relative order.
- If not, we swap their positions and increment the operation count.
- If at any point, the required condition fails (the difference in values doesn't match the required gap), 
  then the tree cannot be made beautiful and we return -1.

Time Complexity: O(n log n) where n is the size of the permutation.
Space Complexity: O(1) excluding input storage.
"""

for _ in range(int(input())):
    n = int(input())
    p = [*map(int, input().split())]
    j, ans, f = 1, 0, 0
    while j < n:
        for i in range(0, n, j * 2):
            # Check if the absolute difference between elements in pair is correct
            if abs(p[i] - p[i + j]) != j:
                f = 1  # Mark impossibility
            # Swap if out of order
            if p[i] > p[i + j]:
                p[i], p[i + j], ans = p[i + j], p[i], ans + 1
        j <<= 1  # Move to next level (left shift by 1 = multiply by 2)
    print([ans, -1][f])


# https://github.com/VaHiX/CodeForces/