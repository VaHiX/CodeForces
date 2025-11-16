# Problem: CF 2030 F - Orangutan Approved Subarrays
# https://codeforces.com/contest/2030/problem/F

"""
F. Orangutan Approved Subarrays
Algorithms/Techniques: Segment Tree with Range Max Query, Preprocessing with Next Occurrence and Dynamic Programming

Time Complexity:
- For each test case: O(n * log n + q * log n)
- Building next occurrence array: O(n)
- Segment tree updates and queries: O(log n) per operation
- Processing queries: O(q * log n)

Space Complexity:
- O(n * log n) for segment tree and auxiliary arrays

The task is to determine whether a subarray can be emptied through valid operations.
Each operation removes a maximal contiguous subarray where all elements are equal to some element in S.
We preprocess the next occurrence of each element, then use a segment tree to efficiently compute
the maximum index needed to be avoided for a valid sequence from l to r.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def update(i, x):
    # XOR with l1 to map the index to segment tree's leaves
    i ^= l1
    tree[i] = x  # Update leaf node with value x
    i >>= 1      # Move to parent
    while i:
        # Propagate up the maximum of children nodes
        tree[i] = max(tree[i << 1], tree[i << 1 ^ 1])
        i >>= 1
    return


def get_max(s, t):
    # Get maximum in range [s, t] using segment tree
    s, t = s ^ l1, t ^ l1  # Map to leaf indices
    ans = 0
    while s <= t:
        if s & 1:          # If s is left child of its parent
            ans = max(ans, tree[s])
            s += 1         # Move to next node
        s >>= 1            # Move to parent
        if not t & 1:      # If t is right child of its parent
            ans = max(ans, tree[t])
            t -= 1         # Move to previous node
        t >>= 1            # Move to parent
    return ans


t = int(input())
ans = []
for _ in range(t):
    n, q = map(int, input().split())
    a = [0] + list(map(int, input().split()))  # 1-indexed array
    nx, u = [0] * (n + 1), [0] * (n + 1)   # nx: next occurrence indices, u: last seen index for each value
    for i in range(n, 0, -1):              # Traverse backwards to compute next occurrences
        j = a[i]
        if u[j]:                           # If element j was seen before
            nx[i] = u[j]                   # Mark next occurrence of j
        u[j] = i                           # Update last seen index of j
    
    l1 = pow(2, (n + 1).bit_length())      # Compute smallest power of 2 >= n+1
    l2 = 2 * l1                            # Size of segment tree (2 * l1)
    tree = [0] * l2                        # Initialize segment tree
    ng = [0] * (n + 1)                     # ng[i]: max start index for valid subarray ending at i
    
    for l in range(1, n + 1):              # For each index
        if not nx[l]:                      # If no next occurrence
            continue
        r = nx[l]                          # Range from l to nx[l]
        ng[r] = get_max(l + 1, r - 1)      # Get max start for valid subarray [l+1, r-1]
        update(r, l)                       # Update segment tree with value l at position r
    
    for i in range(1, n + 1):              # Propagate maximum forward
        ng[i] = max(ng[i], ng[i - 1])
    
    for _ in range(q):
        l, r = map(int, input().split())   # Query range
        ans0 = "YES" if ng[r] < l else "NO" # Check condition
        ans.append(ans0)
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/codeForces/