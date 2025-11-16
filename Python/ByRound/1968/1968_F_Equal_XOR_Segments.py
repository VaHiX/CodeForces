# Problem: CF 1968 F - Equal XOR Segments
# https://codeforces.com/contest/1968/problem/F

"""
Algorithm: 
This solution uses prefix XOR and binary search to determine if a subarray can be split into segments with equal XOR values.

The key insight is:
1. If we can split the array into k parts with equal XORs, the prefix XOR at the end of the array should be 0 (because XOR of all elements would be 0).
2. For a valid k-split, we can select any valid starting point for the first segment (after the prefix), and a valid ending point for the last segment.
3. This translates to checking if there are valid indices in our prefix array where we can create valid cuts.

Time Complexity:
- Preprocessing: O(n) for building prefix XOR and map
- Each query: O(log n) due to binary search using bisect
- Total: O(n + q * log n)

Space Complexity: O(n) for prefix array and map storage
"""

import sys

input = sys.stdin.read
from bisect import bisect_left
from collections import defaultdict


def solve():
    data = input().split()
    index = 0

    t = int(data[index])
    index += 1

    results = []

    for _ in range(t):

        n = int(data[index])
        q = int(data[index + 1])
        index += 2

        a = [0] * (n + 1)
        pf = [0] * (n + 1)
        mp = defaultdict(list)

        mp[0].append(0)

        for i in range(1, n + 1):
            a[i] = int(data[index])
            index += 1
            pf[i] = pf[i - 1] ^ a[i]
            mp[pf[i]].append(i)

        for _ in range(q):
            l = int(data[index])
            r = int(data[index + 1])
            index += 2

            x = pf[r] ^ pf[l - 1]
            if x == 0:
                results.append("YES")
                continue

            v1 = mp[pf[r]]      # All indices with prefix XOR equal to pf[r]
            v2 = mp[pf[l - 1]]  # All indices with prefix XOR equal to pf[l-1]

            # Find first index in v1 >= l
            it1 = bisect_left(v1, l)
            # Find last index in v2 <= r
            it2 = bisect_left(v2, r) - 1

            # Check if there exists a valid segment split
            if it1 < len(v1) and it2 >= 0 and v1[it1] < v2[it2]:
                results.append("YES")
            else:
                results.append("NO")

    print("\n".join(results))


solve()


# https://github.com/VaHiX/CodeForces/