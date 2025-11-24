# Problem: CF 1716 E - Swap and Maximum Block
# https://codeforces.com/contest/1716/problem/E

"""
Segment Tree with Maximum Subarray Sum
Algorithms/Techniques: Segment Tree, Dynamic Programming on Trees, Maximum Subarray Sum (Kadane's Algorithm)
Time Complexity: O(n log n) for preprocessing, O(1) per query
Space Complexity: O(n log n) for the segment tree storage

The code uses a segment tree where each node stores information about maximum subarray sum
and other relevant values needed for merging segments during query processing.
"""

import sys

input = sys.stdin.readline


def seg(start, end):
    # Base case: if start equals end, initialize the segment tree node
    if start == end:
        val = max(arr[start], 0)  # Maximum subarray sum starting at this element (can be 0 for empty)
        return [(val, val, val, arr[start])]  # (best_sum, left_sum, right_sum, total_sum)
    
    # Divide the array into two halves
    mid = (start + end) // 2
    l = seg(start, mid)  # Process left half
    r = seg(mid + 1, end)  # Process right half
    
    result = []
    # Combine the left and right segments
    for i in range((end - start + 1) // 2):
        lb, ls, lp, lS = l[i]  # left best, left sum, left prefix, left total
        rb, rs, rp, rS = r[i]  # right best, right sum, right prefix, right total
        # Merge the segments to compute new values
        result.append(
            (max(lb, rb, ls + rp), max(rs, rS + ls), max(lp, lS + rp), lS + rS)
        )
    
    # Reassign l and r for the second loop (invariant part of logic)
    l, r = r, l
    for i in range((end - start + 1) // 2):
        lb, ls, lp, lS = l[i]  
        rb, rs, rp, rS = r[i]
        result.append(
            (max(lb, rb, ls + rp), max(rs, rS + ls), max(lp, lS + rp), lS + rS)
        )
    return result


n = int(input())
l = 1 << n  # 2^n
arr = list(map(int, input().split()))
tree = seg(0, l - 1)  # Build segment tree
i = 0  # Current active query state index
for _ in range(int(input())):
    i ^= 1 << int(input())  # Toggle the bit corresponding to the query index
    print(tree[i][0])  # Print the maximum subarray sum from the segment tree result


# https://github.com/VaHiX/CodeForces/