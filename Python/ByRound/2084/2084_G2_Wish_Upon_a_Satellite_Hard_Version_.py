# Contest 2084, Problem G2: Wish Upon a Satellite (Hard Version)
# URL: https://codeforces.com/contest/2084/problem/G2

import pprint
from math import isqrt

import random

random.seed()


def ril():
    return map(int, input().split())


T = int(input())

for _ in range(T):
    n = int(input())
    a = list(ril())

    loc = [-1] * (n + 1)
    for i, x in enumerate(a):
        if x > 0:
            loc[x] = i % 2

    oc = loc.count(1)
    ec = loc.count(0)
    jmin = [n // 2] * (n + 1)
    jmax = [0] * (n + 1)

    oused = 0
    eused = 0
    odd_count = 0
    for i in range(1, n + 1):
        if loc[i] == 0:
            pass
        elif loc[i] == 1:
            odd_count += 1
        elif odd_count < i // 2:
            if oc + oused < n // 2:
                oused += 1
                odd_count += 1
            else:
                eused += 1
        else:
            if ec + eused < n - n // 2:
                eused += 1
            else:
                oused += 1
                odd_count += 1
        # k = isqrt(min(i, n+1-i))//20 + 30
        k = 30
        jmin[i] = min(jmin[i], max(odd_count - k, 0))
        jmax[i] = max(jmax[i], min(odd_count + k, n // 2))
        jmax[i] = min(jmax[i], i)
    assert ec + eused == n - n // 2
    assert oc + oused == odd_count == n // 2

    jmin[0] = 0

    # dp[i][j] = max from assigning 1..i given j odd indices remain (=> n//2 - j have been used)

    dp = [0]

    for i in range(1, n + 1):
        filled = n - i
        # dp[i] = [-float('inf')] * (jmax[i] - jmin[i] + 1)
        ndp = [-float("inf")] * (jmax[i] - jmin[i] + 1)
        # for j in range(min(i, n//2) + 1):
        for j in range(jmin[i], jmax[i] + 1):
            jj = j - jmin[i]
            mode = 0  # 1 = forced odd, 2 = forced even
            if loc[i] == 1:
                if j == 0:
                    # dp[i][jj] = -float('inf')
                    continue
                else:
                    mode = 1

            if loc[i] == 0:
                if j == i:
                    # dp[i][jj] = -float('inf')
                    continue
                else:
                    mode = 2
            # print(i, j, mode)

            used_odd = n // 2 - j
            used_even = filled - used_odd
            rem_even = i - j
            # print(i, j, jj, mode)
            if mode != 2 and jmin[i - 1] <= j - 1 <= jmax[i - 1]:
                odd = (j - 0) * i + used_even * i
                ndp[jj] = max(ndp[jj], dp[j - 1 - jmin[i - 1]] + odd)

            if mode != 1 and jmin[i - 1] <= j <= jmax[i - 1]:
                even = used_odd * i + (rem_even - 0) * i
                ndp[jj] = max(ndp[jj], dp[j - jmin[i - 1]] + even)
        dp = ndp

    print(dp[n // 2 - jmin[n]])
