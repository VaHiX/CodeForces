# Contest 2125, Problem E: Sets of Complementary Sums
# URL: https://codeforces.com/contest/2125/problem/E

import sys

le = sys.__stdin__.read().split("\n")[::-1]
af = []
mo = 998244353

for _ in range(int(le.pop())):
    n, x = map(int, le.pop().split())  # can add 1 at much as you want
    if n == 1:
        af.append(x)
        continue

    dp = [0] * (x + 2)
    t = (n * (n + 1)) // 2
    if t > x + 1:
        af.append(0)
        continue
    dp[t] = 1
    for v in range(1, n):  # complexité n racine de n
        for k in range(t + v, x + 2):
            dp[k] = (dp[k] + dp[k - v]) % mo

    af.append(sum((x + 2 - i) * v for i, v in enumerate(dp)) % mo)
print("\n".join(map(str, af)))
