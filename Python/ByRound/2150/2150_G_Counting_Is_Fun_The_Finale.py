# Problem: CF 2150 G - Counting Is Fun: The Finale
# https://codeforces.com/contest/2150/problem/G

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(x * y * (x + y))
Space Complexity: O(x * y)

This solution uses dynamic programming to count valid binary strings that satisfy:
1. Exactly x zeros and y ones
2. A specific condition on the longest non-decreasing subsequence
3. Lexicographically greater than the given string

The approach involves:
- Precomputing factorials and modular inverses for combinations
- Using DP arrays to track valid states
- Processing the string character by character to count valid extensions
"""

import sys
from array import array


def solve():
    d = sys.stdin.buffer.read().split()
    it = iter(d)
    ni = lambda: int(next(it))
    nb = lambda: next(it)
    M = 998244353

    def bfi(L):
        # Precompute factorials and modular inverses
        f = [1] * (L + 1)
        for i in range(1, L + 1):
            f[i] = f[i - 1] * i % M
        g = [1] * (L + 1)
        g[L] = pow(f[L], M - 2, M)
        for i in range(L, 0, -1):
            g[i - 1] = g[i] * i % M
        return f, g

    def makc(f, g):
        # Function to compute combinations C(n, k)
        def C(n, k):
            return f[n] * (g[k] * g[n - k] % M) % M

        return C

    def np(A, B, K, C):
        # Precompute prefix sums for DP states
        W = B + 1
        tot = (A + 1) * W
        nw = array("I", [0]) * tot
        pw = array("I", [0]) * tot
        for i in range(A + 1):
            base = i * W
            pb = (i - 1) * W
            for j in range(B + 1):
                s = i + j
                if s >= K:
                    if i >= K or j >= K:
                        cur = C(s, i)
                    else:
                        cur = C(s, K)
                else:
                    cur = 0
                nw[base + j] = cur
                v = cur
                if i > 0 and j < B:
                    v += pw[pb + (j + 1)]
                    if v >= M:
                        v -= M
                pw[base + j] = v
        return nw, pw

    def one(A, B, K, S, C, f, g):
        # Main function to count valid strings
        N = A + B
        W = B + 1
        nw, pw = np(A, B, K, C)
        ans = 0
        cz = 0
        cl = 0
        ca = A
        cb = B
        fd = False
        for cp in range(N):
            if S[cp] == 49:  # '1' character
                cl += 1
                cb -= 1
                if cl == K and not fd:
                    fd = True
                    cl = 0
                    cz = 0
                continue
            cl += 1
            cb -= 1
            if cb >= 0:
                if fd:
                    # When we've already seen enough 1s
                    if cb + cl >= K or ((ca if ca > cb else cb) + cz >= K):
                        ans += C(ca + cb, ca)
                        if ans >= M:
                            ans -= M
                    elif ca + cb + cz >= K:
                        ans += C(ca + cb, K - cz)
                        if ans >= M:
                            ans -= M
                elif cl == K:
                    # When we just hit K 0s in a row
                    idx = ca * W + cb
                    ans += pw[idx]
                    if ans >= M:
                        ans -= M
                    if ca > 0 and cb < B:
                        idx2 = (ca - 1) * W + (cb + 1)
                        ans -= pw[idx2]
                        if ans < 0:
                            ans += M
                else:
                    # General case, compute valid arrangements
                    lim = N - cp
                    for L in range(1, lim):
                        R = N - cp - L - 1
                        if L + cl < K or R < K:
                            continue
                        if L + cz < K:
                            zl = L - (K - cl)
                            ol = L - zl
                            zr = ca - zl
                            orr = cb - ol
                            if zl >= 0 and zr >= 0 and ol >= 0 and orr >= 0:
                                left = C(zl + ol - 1, zl)
                                add = left * nw[zr * W + orr] % M
                                ans += add
                                if ans >= M:
                                    ans -= M
                            continue
                        if K - cz <= L - (K - cl):
                            continue
                        zl = K - cz
                        ol = L - zl
                        zr = ca - zl
                        orr = cb - ol
                        if zl >= 0 and zr >= 0 and ol >= 0 and orr >= 0:
                            numl = C(zl + ol, zl)
                            if ol:
                                sub = (C(zl + ol - 1, zl) * 2) % M
                                numl -= sub
                                numl %= M
                            add = numl * nw[zr * W + orr] % M
                            ans += add
                            if ans >= M:
                                ans -= M
                        zl = L - (K - cl)
                        ol = L - zl
                        zr = ca - zl
                        orr = cb - ol
                        if zl >= 0 and zr >= 0 and ol >= 0 and orr >= 0:
                            numl = C(zl + ol - 1, zl)
                            if max(zl, ol - 1) >= K - cz:
                                numl = 0
                            elif zl + ol - 1 >= K - cz:
                                numl -= C(zl + ol - 1, K - cz)
                                numl %= M
                            add = numl * nw[zr * W + orr] % M
                            ans += add
                            if ans >= M:
                                ans -= M
                        lo = L - (K - cl) + 1
                        hi = K - cz - 1
                        if hi > ca:
                            hi = ca
                        t = L - cb
                        if lo < t:
                            lo = t
                        if lo <= hi:
                            cur = C(L, K - cz)
                            if L > K - cz:
                                cur -= 2 * C(L - 1, K - cz) % M
                                cur %= M
                            id = (ca - lo) * W + (R - ca + lo)
                            onr = pw[id]
                            if ca > hi:
                                id2 = (ca - hi - 1) * W + (R - (ca - hi - 1))
                                onr -= pw[id2]
                                onr %= M
                            ans += cur * onr % M
                            if ans >= M:
                                ans -= M
            cb += 1
            ca -= 1
            if ca < 0:
                break
            cl -= 1
            cz += 1
            if cl < cz:
                cl = cz
            if cl == K and not fd:
                fd = True
                cl = 0
                cz = 0
        return ans % M

    t = ni()
    T = []
    mx = 0
    for _ in range(t):
        A = ni()
        B = ni()
        K = ni()
        S = nb()
        T.append((A, B, K, S))
        n = A + B
        if n > mx:
            mx = n
    f, g = bfi(mx)
    C = makc(f, g)
    o = []
    for A, B, K, S in T:
        o.append(str(one(A, B, K, S, C, f, g)))
    sys.stdout.write("\n".join(o))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/