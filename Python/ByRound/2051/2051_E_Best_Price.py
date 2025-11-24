# Problem: CF 2051 E - Best Price
# https://codeforces.com/contest/2051/problem/E

"""
E. Best Price

Algorithms/Techniques: Two Pointers, Sorting, Greedy

Time Complexity: O(n log n) per test case due to sorting and linear traversal.
Space Complexity: O(n) for storing the input arrays and merged values.

The problem involves setting a price for Christmas trees such that:
- Each customer buys at most one tree if their willingness to pay is sufficient.
- Customers who pay up to 'a_i' give positive reviews.
- Customers who pay up to 'b_i' give negative reviews.
- The store can have at most k negative reviews.

Approach:
1. Sort both arrays 'a' and 'b'.
2. Create a merged list of all unique values from 'a' and 'b', sorted.
3. For each possible price value (from the merged list):
   - Use two pointers to determine how many customers buy trees at this price.
   - Count how many negative reviews would result (customers paying up to b_i but not a_i).
   - If count of negative reviews is <= k, compute earnings: price * number of buyers.
4. Return the maximum possible earnings.

This greedy solution leverages sorting and two-pointer technique to efficiently 
compute valid price points that do not exceed allowed negative reviews.
"""

import sys

input = sys.stdin.readline


def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    a.sort()
    b.sort()
    vals = [*a, *b]
    vals.sort()
    ans = 0
    l = 0
    r = 0
    for c in vals:  # Iterate through all unique price points
        while l < n and b[l] < c:  # Move pointer l to find customers with b[i] >= current price
            l += 1
        while r < n and a[r] < c:  # Move pointer r to find customers with a[i] >= current price
            r += 1
        cnt = r - l  # Number of customers who will buy at this price (paying up to b[i] but not a[i])
        if cnt > k:
            continue  # Skip if more negative reviews than allowed
        ans = max(ans, c * (n - l))  # Compute earnings: price * number of buyers
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/