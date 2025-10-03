# Contest 2005, Problem C: Lazy Narek
# URL: https://codeforces.com/contest/2005/problem/C

from sys import stdin, stdout
from collections import deque, Counter
from bisect import bisect_left as bl
from math import inf
I = lambda: stdin.buffer.readline().decode().rstrip()
flush = stdout.flush

for _ in range(int(I())):
    n, m = map(int, I().split())
    dp = [0, -1e9, -1e9, -1e9, -1e9]
    for _ in range(n):
        cur = I()
        ndp = dp.copy()
        for i in range(5):
            if dp[i] == -1e9: continue
            k = i
            for c in cur:
                if c in "narek":
                    dp[i] -= 1
                if c == "narek"[k]:
                    k += 1
                    if k == 5:
                        dp[i] += 10
                        k = 0
            ndp[k] = max(ndp[k], dp[i])
        dp = ndp
    print(max(dp))
