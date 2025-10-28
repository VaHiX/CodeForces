# Problem: CF 1888 D2 - Dances (Hard Version)
# https://codeforces.com/contest/1888/problem/D2

"""
Code Purpose:
This solution solves the problem of finding the minimum number of operations to make array 'a' elements strictly less than array 'b' elements,
after reordering both arrays optimally. The problem is extended to handle multiple test cases, where the first element of array 'a' varies from 1 to m.
This is solved using a greedy two-pointer technique to match elements, then calculating the total operations across all values of 'a[0]' from 1 to m.

Algorithms/Techniques:
- Greedy two-pointer matching to minimize operations.
- Prefix sum technique to compute cumulative operations efficiently.
- Binary search or direct computation to handle the range [1..m] efficiently.

Time Complexity: O(n log n) per test case due to sorting, where n is the size of the array.
Space Complexity: O(1) excluding input storage, as we only use a few variables for computation.

Note: The algorithm works under the assumption that a[0] in the first element of c[i] is varied from 1 to m, and for each such variation,
we compute the minimum operations required to satisfy the condition a[i] < b[i] for all valid indices, and accumulate the results.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    a.sort()
    b.sort()
    i = 0
    j = 0
    ans = 0
    while i < n - 1 and j < n:
        if a[i] < b[j]:
            i += 1
            j += 1
        else:
            mx = b[j]
            ans += 1
            j += 1
    if j < n:
        ans += 1
        mx = b[-1]
    if mx > m:
        # If the maximum b[j] is greater than m, we can only go up to m, so 
        # compute the answer as (ans-1)*m to count all operations across range [1,m]
        print((ans - 1) * m)
    else:
        # If maximum b[j] is less than or equal to m,
        # we need to split calculation into two parts: 
        # 1. From 1 to mx - 1, and 2. From mx to m
        print((ans - 1) * (mx - 1) + ans * (m - mx + 1))


# https://github.com/VaHiX/CodeForces/