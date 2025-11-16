# Problem: CF 1914 G2 - Light Bulbs (Hard Version)
# https://codeforces.com/contest/1914/problem/G2

"""
Code Purpose:
This code solves the problem of finding the minimum number of light bulbs to initially turn on 
and the number of such minimum sets, given a configuration of 2n light bulbs with n colors 
(2 bulbs per color). It uses XOR-based grouping and combinatorics to compute the solution.

Algorithms/Techniques:
- XOR prefix sums to group positions
- Hash map to track last occurrence of XOR value
- Combinatorial counting with modular arithmetic

Time Complexity: O(n) amortized per test case, where n is the number of bulbs.
Space Complexity: O(n) for storing auxiliary arrays and hash maps.
"""

import random
import sys

input = sys.stdin.readline
rd = random.randint(10**9, 2 * 10**9)
Mod = 998244353
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    n *= 2
    rd = [-1] * (n + 1)
    for i in range(n):
        if rd[a[i]] == -1:
            rd[a[i]] = random.randint(0, 10**18)
            a[i] ^= rd[a[i]]
        else:
            a[i] ^= rd[a[i]]
    xor = [0] * n
    xor[0] = a[0]
    cnt = [0] * (n + 1)
    from collections import defaultdict

    last = defaultdict(lambda: -1)
    for i in range(1, n):
        xor[i] = xor[i - 1] ^ a[i]
    for i in range(n):
        if xor[i] and last[xor[i]] != -1:
            cnt[i] -= 1
            cnt[last[xor[i]]] += 1
        last[xor[i]] = i
    for i in range(1, n + 1):
        cnt[i] += cnt[i - 1]
    x = 0
    ans = 0
    res = 1

    for i in range(n):
        x += not cnt[i]
        if not xor[i]:
            ans += 1
            res *= x
            res %= Mod
            x = 0
    print(ans, res)


# https://github.com/VaHiX/CodeForces/