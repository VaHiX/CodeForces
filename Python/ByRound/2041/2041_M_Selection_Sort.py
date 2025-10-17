# Contest 2041, Problem M: Selection Sort
# URL: https://codeforces.com/contest/2041/problem/M

import sys, math

# input = sys.stdin.readline

rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():
    n, a = rn(), rl()
    b = sorted(list(set(a)))

    mp = {}
    for i in range(len(b)):
        mp[b[i]] = i + 1
    c = [0] + [mp[x] for x in a] + [0]
    d = [0] + sorted(c[1:-1]) + [0]

    def calc(c, d):
        cnt = [0] * (1 << 20)

        for i in range(1, n + 1):
            cnt[c[i]] += 1

        cnt_pre_sum = [0]
        for i in range(1, 1 << 20):
            cnt_pre_sum.append(cnt_pre_sum[-1] + cnt[i])
        zl = [0] * (n + 2)
        for i in range(n, 0, -1):
            zl[i] = zl[i + 1] + 1 if c[i] == d[i] else 0
        cnt2 = [0] * (1 << 20)

        suf_min, pre_min = [math.inf] * (n + 2), [math.inf] * (n + 2)

        for i in range(n, 0, -1):
            suf_min[i] = min(suf_min[i + 1], c[i])
        for i in range(1, n + 1):
            pre_min[i] = min(pre_min[i - 1], c[i])

        res = n * n
        for i in range(1, n - 1):
            cnt2[c[i]] += 1
            m = suf_min[i + 1]
            k = cnt_pre_sum[m - 1] + cnt2[m]
            p = n - k if k < i else n - k - zl[i + 1]
            res = min(res, i * i + p * p)
        return res

    c_rev, d_rev = list(reversed([n - u + 1 for u in c])), list(
        reversed([n - u + 1 for u in d])
    )
    print(min(calc(c, d), calc(c_rev, d_rev)))


solve()
