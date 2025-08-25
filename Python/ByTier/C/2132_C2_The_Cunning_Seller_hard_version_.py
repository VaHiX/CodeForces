# Contest 2132, Problem C2: The Cunning Seller (hard version)
# URL: https://codeforces.com/contest/2132/problem/C2

import sys

it = iter(sys.stdin.read().strip().split())
t = int(next(it))
out = []
for _ in range(t):
    n = int(next(it))
    k = int(next(it))
    s3 = 0
    tmp = n
    while tmp:
        s3 += tmp % 3
        tmp //= 3
    if k < s3:
        out.append("-1")
        continue
    r = min(k, n)
    if (r ^ n) & 1:
        r -= 1
    M = (n - r) // 2
    surcharge = 0
    ai = n // 3
    pow3 = 1
    while M and ai:
        take = min(M, ai)
        surcharge += take * pow3
        M -= take
        ai //= 3
        pow3 *= 3
    total_cost = 3 * n + surcharge
    out.append(str(total_cost))
print("\n".join(out))
