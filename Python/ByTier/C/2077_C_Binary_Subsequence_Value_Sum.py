# Contest 2077, Problem C: Binary Subsequence Value Sum
# URL: https://codeforces.com/contest/2077/problem/C

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 998244353
for _ in range(int(input())):
    n, q = map(int, input().split())
    s = [int(x) for x in input()]
    res = pow(2, n - 4, mod)
    cnt = s.count(1) * 2 - n
    for _ in range(q):
        i = int(input()) - 1
        cnt = (cnt - 2) if s[i] else (cnt + 2)
        s[i] = 1 - s[i]
        print(res * (cnt**2 + n - 2) % mod)
