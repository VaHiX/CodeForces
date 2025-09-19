# Contest 2116, Problem C: Gellyfish and Flaming Peony
# URL: https://codeforces.com/contest/2116/problem/C

from math import gcd
from collections import deque

for _ in range(int(input())):
    n = int(input())
    arr = [*map(int, input().split())]
    g = gcd(*arr)
    x = arr.count(g)
    if x > 0:
        print(n - x)
        continue
    new = [*map(int, set(map(str, arr)))]
    dp = [-1] * (max(arr) + 1)
    for i in new:
        dp[i] = 0
    q = deque(new)
    while q:
        cur = q.popleft()
        for i in new:
            if cur != i:
                x = gcd(cur, i)
                if dp[x] == -1:
                    dp[x] = dp[cur] + 1
                    q.append(x)
                if x == g:
                    break
    print(n + dp[g] - 1)
