# Problem: CF 1913 F - Palindromic Problem
# https://codeforces.com/contest/1913/problem/F

"""
Algorithm: Palindromic Problem
Approach:
- Use Manacher's algorithm to find all palindromes in the string.
- Calculate the number of palindromic substrings for each position.
- For each position, determine the optimal character to replace it with to maximize the number of palindromes.
- If there is a tie in the number of palindromes, choose the lexicographically smallest string.

Time Complexity: O(n log n)
Space Complexity: O(n)

Manacher's algorithm implementation is used to efficiently find all palindromic substrings in O(n) time.
The rest of the code manipulates these palindromes to find the best replacement strategy.
"""

import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def manacher(s):
    i, j = 0, 0
    n = len(s)
    ans = [0] * n
    while i < n:
        while i - j >= 0 and i + j < n and s[i - j] == s[i + j]:
            j += 1
        ans[i] = j
        k = 1
        while i - k >= 0 and k + ans[i - k] < j:
            ans[i + k] = ans[i - k]
            k += 1
        i += k
        j -= k
    return ans


def f(u, v, w):
    return u << 38 ^ v << 19 ^ w


def random_mod():
    mod, p = 2 * random.randint(3 * pow(10, 8), 5 * pow(10, 8)) + 1, 1
    while not mod % p:
        mod, p = mod + 2, 3
        while p * p < mod and mod % p:
            p += 2
    return mod


n = int(input())
s = list(input().rstrip())
s = [i - 96 for i in s]
u = [0] * (2 * n + 1)
for i in range(n):
    u[2 * i + 1] = s[i]
p = manacher(u)
p = [i >> 1 for i in p[1:-1]]
c = [0] * (n + 2)
for i in range(n):
    l, m, r = i - p[2 * i] + 1, i + 1, i + p[2 * i] + 1
    c[l], c[m], c[r] = c[l] + 1, c[m] - 2, c[r] + 1
for i in range(n - 1):
    if not p[2 * i + 1]:
        continue
    l, m1, m2, r = i - p[2 * i + 1] + 1, i + 1, i + 2, i + p[2 * i + 1] + 2
    c[l], c[m1], c[m2], c[r] = c[l] + 1, c[m1] - 1, c[m2] - 1, c[r] + 1
for _ in range(2):
    for i in range(1, n + 2):
        c[i] += c[i - 1]
for i in range(n):
    c[i] -= p[2 * i]
x = []
for i in range(2 * n - 1):
    l, r = (i >> 1) - p[i], (i >> 1) + p[i] + (i & 1)
    if 0 <= l and r < n:
        x.append(f(l << 5 ^ s[r], l, r))
        x.append(f(r << 5 ^ s[l], l, r))
m1, m2 = random_mod(), random_mod()
p1, p2 = [1] * (2 * n + 1), [1] * (2 * n + 1)
h1, h2 = [0] * (2 * n + 1), [0] * (2 * n + 1)
for i in range(1, 2 * n + 1):
    p1[i] = 29 * p1[i - 1] % m1
    p2[i] = 29 * p2[i - 1] % m2
ss = s + s[::-1]
for i in range(2 * n):
    h1[i + 1] = h1[i] + p1[i] * ss[i]
    h2[i + 1] = h2[i] + p2[i] * ss[i]
pow2 = [1]
for _ in range(n.bit_length()):
    pow2.append(2 * pow2[-1])
s.append(0)
la, ma, k, cnt = n << 5, 0, n << 5, 0
for i in sorted(x):
    u, l, r = i >> 38, (i >> 19) & 0x7FFFF, i & 0x7FFFF
    v = 0
    if l and (r + 1) ^ n and s[l - 1] == s[r + 1]:
        d = 2 * n - (l + r + 1)
        for j in pow2[::-1]:
            l0, l1, r0, r1 = l - v - j, l - 1, r + 1, r + v + j
            if not 0 <= l0 or not r1 < n:
                continue
            hl = (h1[l1 + 1] - h1[l0]) % m1 * p1[d] % m1
            hr = (h1[2 * n - r0] - h1[2 * n - r1 - 1]) % m1
            if hl ^ hr:
                continue
            hl = (h2[l1 + 1] - h2[l0]) % m2 * p2[d] % m2
            hr = (h2[2 * n - r0] - h2[2 * n - r1 - 1]) % m2
            if hl ^ hr:
                continue
            v += j
    v += 1
    if la ^ u:
        y = cnt - c[la >> 5]
        if ma < y or (ma == y and s[k >> 5] <= k & 31 and (la >> 5) ^ (k >> 5)):
            ma, k = y, la
        cnt = 0
    la, cnt = u, cnt + v
y = cnt - c[la >> 5]
if ma < y or (ma == y and s[k >> 5] <= k & 31 and (la >> 5) ^ (k >> 5)):
    ma, k = y, la
ans = [chr(i + 96) for i in s[:-1]]
if (k >> 5) ^ n:
    ans[k >> 5] = chr((k & 31) + 96)
if n == 1:
    ans = ["a"]
m = sum(p) + ma
print(m)
sys.stdout.write("".join(ans))


# https://github.com/VaHiX/CodeForces/