import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
t = int(input())
ans = []
inf = pow(10, 12) + 1
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    if n == 1:
        ans0 = 0
    elif not n & 1:
        u, v = [0] * n, [0] * n
        for i in range(0, n, 2):
            u[i], u[i + 1] = a[i] + a[i + 1], a[i + n] + a[i + n + 1]
            v[i], v[i + 1] = a[i] + a[i + n + 1], a[i + n] + a[i + 1]
            if u[i] > u[i + 1]:
                u[i], u[i + 1] = u[i + 1], u[i]
            if v[i] > v[i + 1]:
                v[i], v[i + 1] = v[i + 1], v[i]
        ans0 = inf
        for i in range(0, n, 2):
            for _ in range(2):
                l, r = u[i], u[i + 1]
                for j in range(0, n, 2):
                    if i == j or r == inf:
                        continue
                    c = inf
                    if l <= u[j]:
                        c = min(c, u[j + 1])
                    if l <= v[j]:
                        c = min(c, v[j + 1])
                    r = max(r, c)
                ans0 = min(ans0, r - l)
                u[i], v[i] = v[i], u[i]
                u[i + 1], v[i + 1] = v[i + 1], u[i + 1]
    else:
        b, j = [0] * (2 * n), 0
        for i in range(0, 2 * n, 2):
            b[i], b[i + 1] = a[j], a[j + 1]
            j = (j + n + 1) % (2 * n)
        a = b
        x, u = [0] * (4 * n), 0
        mi = inf
        for i in range(0, 2 * n, 2):
            ma = 0
            for j in [i, i - 1]:
                for k in [i + 1, i + 2]:
                    x[u] = a[j] + a[k % (2 * n)]
                    ma = max(ma, x[u])
                    u += 1
            mi = min(mi, ma)
        y = []
        for i in sorted(x):
            if i <= mi and (not y or y[-1] ^ i):
                y.append(i)
        random.shuffle(y)
        ans0 = inf - max(y)
        for _ in range(2):
            for l in y:
                dp = [l, inf]
                for i in range(0, 2 * n - 2, 2):
                    dp0 = [inf] * 2
                    for k in range(2):
                        if dp[k] == inf:
                            continue
                        for j in range(2):
                            if l <= a[i - k] + a[i + j + 1]:
                                dp0[j] = min(
                                    dp0[j], max(dp[k], a[i - k] + a[i + j + 1])
                                )
                    dp = dp0
                    if min(dp) - l >= ans0:
                        break
                for k in range(2):
                    if l <= a[-1] + a[-2 - k]:
                        r = max(dp[k], a[-1] + a[-2 - k])
                        ans0 = min(ans0, r - l)
            a[0], a[-1] = a[-1], a[0]
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))
