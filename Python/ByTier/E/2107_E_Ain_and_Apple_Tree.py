# Problem: CF 2107 E - Ain and Apple Tree
# https://codeforces.com/contest/2107/problem/E

"""
E. Ain and Apple Tree

Purpose:
This code determines whether it's possible to construct a tree with n nodes such that the "weight" of the tree (sum over all pairs of nodes of the depth of their lowest common ancestor) is within 1 of a given value k.
If such a tree exists, it outputs the edges forming the tree.

Algorithms/Techniques:
- Greedy construction: Build the tree by adding edges to minimize or maximize the total weight depending on how far k is from the maximum possible weight.
- Mathematical formula for max weight: For n nodes arranged in a path (a star-like structure), the maximum weight is calculated as n*(n-1)*(n-2)/6.

Time Complexity:
O(n^2) per test case in the worst case due to nested loops for edge construction. However, in practice, since we're building a tree greedily by choosing children, the actual performance can be much better.

Space Complexity:
O(1) extra space excluding the input/output storage and recursion stack (if any). The algorithm uses constant additional memory.
"""

import sys

input = sys.stdin.read
data = input().split()
idx = 0
t = int(data[idx])
idx += 1
for _ in range(t):
    n = int(data[idx])
    idx += 1
    k = int(data[idx])
    idx += 1
    # Compute maximum possible weight for an n-node tree (when tree is a path)
    mx = n * (n - 1) * (n - 2) // 6
    # If k is too large to be achievable within 1 unit of max weight, no solution exists
    if k > mx + 1:
        print("No")
        continue
    print("Yes")
    # Adjust k for the greedy approach (think of how far away from max it is)
    k = mx - min(k, mx)
    p = n - 1  # Start building tree with last node p = n-1
    # Iterate from n down to 2 to build edges in reverse order
    for i in range(n, 1, -1):
        # Reduce p while the number of pairs that can be formed is greater than current k
        while p * (p - 1) // 2 > k:
            p -= 1
        # Subtract from k how many pairs are being added via this edge
        k -= p * (p - 1) // 2
        # Output the edge (i-p, i)
        print(f"{i - p} {i}")
        # Move to next node, unless p=1 in which case we stop adjusting
        if p != 1:
            p -= 1


# https://github.com/VaHiX/codeForces/