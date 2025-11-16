# Problem: CF 1766 D - Lucky Chains
# https://codeforces.com/contest/1766/problem/D

"""
Algorithm: 
- Precompute smallest prime factor (SPF) for all numbers up to 10^7 using Sieve of Eratosthenes.
- For each query pair (x, y):
    - Compute difference d = y - x.
    - If d = 1, output -1 (infinite chain possible).
    - Find all unique prime factors of d.
    - For each prime factor p, compute the smallest non-negative value k such that (x + k) % p == 0.
    - The minimum such k over all prime factors gives the length of the longest lucky chain.
    
Time Complexity: O(N log N + M), where N = 10^7, M = number of queries
Space Complexity: O(N)
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
lim = 10**7 + 1
ls = [i for i in range(lim)]
for i in range(2, lim):
    if ls[i] != i:
        continue
    for j in range(i * i, lim, i):
        ls[j] = i
for _ in range(int(input())):
    x, y = map(int, input().split())
    d = y - x
    ans = (-x) % d
    if d == 1:
        print(-1)
        continue
    s = set()
    while d > 1:
        s.add(ls[d])
        d //= ls[d]
    for v in s:
        ans = min(ans, (-x) % v)
    print(ans)


# https://github.com/VaHiX/CodeForces/