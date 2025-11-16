# Problem: CF 1899 D - Yarik and Musical Notes
# https://codeforces.com/contest/1899/problem/D

"""
Algorithm: Counting valid pairs (i, j) such that b_i^(b_j) == b_j^(b_i)
where b_i = 2^a_i and b_j = 2^a_j.

Key Insight:
- Let b_i = 2^a_i, b_j = 2^a_j
- The condition b_i^(b_j) == b_j^(b_i) translates to (2^a_i)^(2^a_j) == (2^a_j)^(2^a_i)
- This simplifies to 2^(a_i * 2^a_j) == 2^(a_j * 2^a_i)
- Thus: a_i * 2^a_j == a_j * 2^a_i
- Rearranging: a_i / 2^a_i == a_j / 2^a_j

So we need to count pairs (i, j) where a_i / 2^a_i = a_j / 2^a_j.

The approach:
1. Count frequency of each value in array a.
2. For each unique value k in a:
   - If frequency is 1, do nothing.
   - If frequency is v > 1, add C(v, 2) = v*(v-1)/2 to result.
3. Special case for k=1 and k=2:
   - All elements with a_i=1 contribute to pairs with a_j=2 and vice versa.
   - So add count(1) * count(2) to result.

Time Complexity: O(n)
Space Complexity: O(n)

"""

import sys
from collections import Counter

t = int(input())
for i in range(t):
    n = int(input())
    a = sys.stdin.readline().split()
    d = Counter(a)
    ans = d["1"] * d["2"]
    for k, v in d.items():
        if v > 1:
            ans += (v - 1) * v // 2
    print(ans)


# https://github.com/VaHiX/CodeForces/