# Problem: CF 2162 H - Beautiful Problem
# https://codeforces.com/contest/2162/problem/H

"""
Algorithm: Dynamic Programming with Segment Handling
Time Complexity: O(n^2 * m) in worst case, but optimized by segment processing
Space Complexity: O(n^2) for DP table and auxiliary arrays

This solution determines for each x from 1 to n whether there exists a rearrangement
of input array such that for all given intervals [l_i, r_i], the condition f(a', x, l_i, r_i) = 1 holds.

The key insight is to process intervals as segments and use dynamic programming to track
feasible placements of elements for each possible x value.

The function f(a', x, l, r) evaluates whether x lies outside the range [min(a'_l, ..., a'_r), max(a'_l, ..., a'_r)].
For f(a', x, l, r) = 1, x must be either less than or equal to all elements in the range,
or greater than or equal to all elements in the range.

We first merge overlapping intervals and then use DP to compute possible placements,
finally checking for each x whether it can be satisfied given available free positions.
"""

import sys

INF = 10**9
rd = sys.stdin.buffer.read().split()
it = iter(rd)
out = []


def main():
    T = int(next(it))
    for _ in range(T):
        n = int(next(it))
        m = int(next(it))
        cnt = [0] * (n + 1)
        for i in range(n):
            v = int(next(it))
            cnt[v] += 1
        mxr = [0] * (n + 2)
        for i in range(m):
            l = int(next(it))
            r = int(next(it))
            if r > mxr[l]:
                mxr[l] = r

        segs = []
        for i in range(1, n + 1):
            if mxr[i] == 0:
                continue
            if not segs or segs[-1][1] < mxr[i]:
                segs.append((i, mxr[i]))
        sz = len(segs)

        pref = [0] * (n + 1)
        for i in range(1, n + 1):
            pref[i] = pref[i - 1] + cnt[i]

        tag = [0] * (n + 1)
        for l, r in segs:
            for j in range(l, r + 1):
                tag[j] = 1
        freePos = sum(1 - tag[i] for i in range(1, n + 1))

        if sz == 0:

            out.append("1" * n)
            continue

        L0 = segs[0][1] - segs[0][0] + 1
        dp_prev = [[-INF, -INF] for _ in range(n + 1)]
        dp_prev[0][0] = L0
        if L0 <= n:
            dp_prev[L0][1] = 0

        for i in range(1, sz):
            curL, curR = segs[i]
            prevL, prevR = segs[i - 1]
            inter = max(0, min(prevR, curR) - max(prevL, curL) + 1)
            add = (curR - curL + 1) - inter
            dp_cur = [[-INF, -INF] for _ in range(n + 1)]

            for j in range(n + 1):
                s0, b0 = dp_prev[j]
                if s0 > -INF:

                    val = s0 + add
                    if val > dp_cur[j][0]:
                        dp_cur[j][0] = val

                    nj = j + add
                    if nj <= n:
                        val = s0 - inter
                        if val > dp_cur[nj][1]:
                            dp_cur[nj][1] = val
                if b0 > -INF:

                    nj = j + add
                    if nj <= n:
                        val = b0
                        if val > dp_cur[nj][1]:
                            dp_cur[nj][1] = val

                    nj = j - inter
                    if nj >= 0:
                        val = b0 + add
                        if val > dp_cur[nj][0]:
                            dp_cur[nj][0] = val
            dp_prev = dp_cur

        ans = []
        for x in range(1, n + 1):
            less = pref[x - 1]
            greater = n - pref[x]
            ok = False
            for j in range(n + 1):
                mx = max(dp_prev[j])
                if mx < 0:
                    continue
                need_less = max(0, less - j)
                need_big = max(0, greater - mx)
                if need_less + need_big <= freePos:
                    ok = True
                    break
            ans.append("1" if ok else "0")
        out.append("".join(ans))

    sys.stdout.write("\n".join(out))


main()


# https://github.com/VaHiX/CodeForces/