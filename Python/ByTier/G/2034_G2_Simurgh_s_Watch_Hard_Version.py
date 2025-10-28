# Problem: CF 2034 G2 - Simurgh's Watch (Hard Version)
# https://codeforces.com/contest/2034/problem/G2

"""
Algorithm: Interval Coloring with Minimum Colors
Technique: Coordinate Compression + Greedy Assignment

This problem involves assigning minimum number of colors to intervals such that
at every integer point covered by at least one interval, there exists at least one
color that appears exactly once at that point.

Approach:
1. Coordinate compression is used to handle large ranges efficiently.
2. The algorithm scans through compressed coordinates and maintains a count of active intervals.
3. It uses a greedy strategy to color intervals to ensure the constraint is satisfied.
4. For each point, we track which intervals are active and assign colors to minimize total colors used.

Time Complexity: O(n log n) - due to sorting and coordinate compression
Space Complexity: O(n) - for storing intervals and auxiliary data structures
"""

import sys
from bisect import bisect_left


def solve():
    d = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(d)
    t = next(it)
    o = []
    for _ in range(t):
        n = next(it)
        la = [0] * (n + 1)
        ra = [0] * (n + 1)
        v = []
        for i in range(1, n + 1):
            a = next(it)
            b = next(it)
            la[i] = a
            ra[i] = b
            v.append(a - 1)
            v.append(a)
            v.append(b)
            v.append(b + 1)
        v = sorted(set(v))
        m = len(v)
        L = {}
        R = {}
        l = [0] * (n + 1)
        r = [0] * (n + 1)
        for i in range(1, n + 1):
            li = bisect_left(v, la[i]) + 1
            ri = bisect_left(v, ra[i]) + 1
            l[i] = li
            r[i] = ri
            L.setdefault(li, []).append(i)
            R.setdefault(ri, []).append(i)
        ct = 0
        ok = True
        for idx in range(1, m + 1):
            if idx in L:
                ct += len(L[idx])
            if ct > 1:
                ok = False
            if idx in R:
                ct -= len(R[idx])
        z = [0] * (n + 1)
        if ok:
            o.append("1")
            o.append(" ".join("1" for _ in range(n)))
            continue
        ad = {}
        rm = {}
        to = {}
        fr = {}
        d0 = True
        ds = set()
        ac = set()
        for idx in range(1, m + 1):
            Li = L.get(idx)
            if Li:
                if d0:
                    ad[idx] = Li
                    ds.update(Li)
                for x in Li:
                    ac.add(x)
            if len(ac) > 1:
                d0 = False
            Ri = R.get(idx)
            if Ri:
                if not d0:
                    for x in Ri:
                        if x in ds:
                            d0 = True
                            rm[idx] = x
                            break
                for x in Ri:
                    if x in ac:
                        ac.remove(x)
                    ds.discard(x)
            s = len(ac)
            if s == 1:
                x = next(iter(ac))
                y = 0
                dx = x in ds
                dy = d0
                if dx and not dy:
                    d0 = True
                    to[idx] = 0
                    fr[idx] = x
                elif (not dx) and dy:
                    ds.add(x)
                    to[idx] = x
                    fr[idx] = 0
            elif s == 2:
                it2 = iter(ac)
                x = next(it2)
                y = next(it2)
                dx = x in ds
                dy = y in ds
                if dx and not dy:
                    ds.add(y)
                    to[idx] = y
                    fr[idx] = x
                elif (not dx) and dy:
                    ds.add(x)
                    to[idx] = x
                    fr[idx] = y
        tp = d0
        if tp:
            fa = [0] * (m + 1)
            fb = [0] * (m + 1)
            cur = 0
            for idx in range(m, 0, -1):
                t0 = to.get(idx)
                if t0 is not None:
                    if cur == t0:
                        cur = fr[idx]
                r0 = rm.get(idx, 0)
                if r0 and cur == 0:
                    cur = r0
                fa[idx] = cur
                al = ad.get(idx)
                if al is not None:
                    if cur in al:
                        cur = 0
                fb[idx] = cur
            ac.clear()
            for idx in range(1, m + 1):
                Li = L.get(idx)
                if Li:
                    al = ad.get(idx)
                    if al is not None and (fa[idx] in al):
                        base = z[next(iter(ac))] if ac else 0
                        sp = fa[idx]
                        for x in Li:
                            z[x] = base ^ (1 if x == sp else 0)
                            ac.add(x)
                    elif fb[idx] != 0:
                        base = z[fb[idx]] ^ 1
                        for x in Li:
                            z[x] = base
                            ac.add(x)
                    else:
                        base = (z[next(iter(ac))] ^ 1) if ac else 1
                        for x in Li:
                            z[x] = base
                            ac.add(x)
                Ri = R.get(idx)
                if Ri:
                    for x in Ri:
                        ac.discard(x)
            o.append(str(max(z[1:]) + 1))
            o.append(" ".join(str(c + 1) for c in z[1:]))
        else:
            cur = 0
            nxt = 0
            for idx in range(1, m + 1):
                Li = L.get(idx)
                if Li:
                    if cur and idx > r[cur] and nxt != cur:
                        z[nxt] = z[cur] ^ 3
                        cur = nxt
                    if idx > r[cur]:
                        for x in Li:
                            if r[x] > r[cur]:
                                cur = x
                        nxt = cur
                        z[nxt] = 1
                    for x in Li:
                        if r[x] > r[nxt]:
                            nxt = x
            if nxt != cur:
                z[nxt] = z[cur] ^ 3
            o.append(str(max(z[1:]) + 1))
            o.append(" ".join(str(c + 1) for c in z[1:]))
    sys.stdout.write("\n".join(o))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/