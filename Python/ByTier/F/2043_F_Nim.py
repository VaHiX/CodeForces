# Contest 2043, Problem F: Nim
# URL: https://codeforces.com/contest/2043/problem/F

import sys
from collections import defaultdict

mod = 998244353
oo = 10**18


def main():
    input = sys.stdin.read
    data = input().split()
    ptr = 0

    n = int(data[ptr])
    q = int(data[ptr + 1])
    ptr += 2

    a = list(map(int, data[ptr : ptr + n]))
    ptr += n

    # Preprocess count array
    cnt = [[0] * 51 for _ in range(n + 1)]
    for i in range(n):
        for j in range(51):
            cnt[i + 1][j] = cnt[i][j]
        cnt[i + 1][a[i]] += 1

    mp = {}

    for _ in range(q):
        l = int(data[ptr]) - 1
        r = int(data[ptr + 1])
        ptr += 2

        c = [0] * 51
        c2 = 0
        for i in range(51):
            c[i] = cnt[r][i] - cnt[l][i]
            c2 += c[i] * (c[i] - 1)

        if c[0] > 0:
            print(r - l - 1, c[0])
        elif c2 > 0:
            print(r - l - 2, (c2 // 2) % mod)
        else:
            msk = 0
            for i in range(51):
                if c[i]:
                    msk |= 1 << i

            if msk not in mp:
                cnt_dp = [0] * 64
                f = [10] * 64

                for i in range(51):
                    if c[i]:
                        for j in range(64):
                            if f[j] > f[i ^ j] + 1:
                                f[j] = f[i ^ j] + 1
                                cnt_dp[j] = cnt_dp[i ^ j]
                            elif f[j] == f[i ^ j] + 1:
                                cnt_dp[j] += cnt_dp[i ^ j]
                                if cnt_dp[j] >= mod:
                                    cnt_dp[j] -= mod
                        f[i] = 1
                        cnt_dp[i] = 1

                if f[0] == 10:
                    mp[msk] = (-1, -1)
                else:
                    mp[msk] = (r - l - f[0], cnt_dp[0] % mod)

            if mp[msk][0] == -1:
                print(-1)
            else:
                print(mp[msk][0], mp[msk][1])


if __name__ == "__main__":
    main()
