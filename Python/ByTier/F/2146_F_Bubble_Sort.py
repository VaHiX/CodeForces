# Problem: CF 2146 F - Bubble Sort
# https://codeforces.com/contest/2146/problem/F

"""
F. Bubble Sort

This code solves a problem involving counting permutations of length n under constraints defined by bubble sort rounds.

Key Concepts:
- The function sort(a) returns the number of rounds needed to sort array a using bubble sort.
- For each position i in a permutation p, we compute b[i] = sort(p[0:i+1]).
- We are given m tuples (k_i, l_i, r_i) that constrain how many positions have b[y] <= k_i.
  
Algorithm:
1. Precompute factorials and inverse factorials modulo 998244353 for use in combinations.
2. Use dynamic programming with events to track valid permutations.
3. Events are either start or end of a range constraint.
4. Process these events from right to left, maintaining a DP array that stores number of ways to achieve various b values.

Time Complexity: O(n * m + n * log(n))
Space Complexity: O(n + m)

The approach uses:
- Prefix sums
- Dynamic Programming
- Event processing on intervals
- Modular arithmetic with precomputed factorials

"""

import sys

MOD = 998244353
MR = 10**6 + 5
fac = [1] * MR
ifac = [1] * MR
for i in range(1, MR):
    fac[i] = fac[i - 1] * i % MOD
ifac[-1] = pow(fac[-1], MOD - 2, MOD)
for i in range(MR - 2, -1, -1):
    ifac[i] = ifac[i + 1] * (i + 1) % MOD

def F(l: int, r: int, x: int) -> int:
    # Computes a value based on the interval [l,r] and point x
    if l > r:
        return 1
    if x <= l:
        return pow(x % MOD, r - l + 1, MOD)
    if r <= x:
        return fac[r] * ifac[l - 1] % MOD
    return fac[x] * ifac[l - 1] % MOD * pow(x % MOD, r - x, MOD) % MOD

def solve():
    it = iter(sys.stdin.buffer.read().split())
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        ev = []
        ev.append((0, 1, 0))  # start event at position 1 with value 0
        for _ in range(m):
            k = int(next(it))  # threshold on bubble rounds
            l = int(next(it))  # lower bound on count of b[y] <= k
            r = int(next(it))  # upper bound on count of b[y] <= k
            ev.append((0, l, k))  # start event
            if r != n:
                ev.append((1, r + 1, k))  # end event (at pos r+1 with value k)
        ev.append((0, n, n - 1))  # final event at position n with value n-1
        ev.sort(key=lambda z: z[1])  # sort events by position
        
        ys = sorted({y for _, _, y in ev})  # distinct y-values across all events
        mp = {y: i + 1 for i, y in enumerate(ys)}  # map to new indices
        rev = [0] * (len(ys) + 1)
        for y, idx in mp.items():
            rev[idx] = y  # reverse mapping from index to original value
            
        dp = [0] * (len(ys) + 1)  # DP array storing number of valid ways for each y
        last_type, last_x, last_y = ev[-1]
        dp[mp[last_y]] = 1  # initialize with final state
        
        for i in range(len(ev) - 2, -1, -1):  # process events in reverse order
            typ, x, y = ev[i]
            nx, ny = ev[i + 1][1], ev[i + 1][2]  # next event
            l = x + 1
            r = nx  # interval of influence
            
            if l <= r:
                tdp = [0] * (len(ys) + 1)
                for j in range(1, len(ys) + 1):
                    v = dp[j]
                    if v:
                        tdp[j] = (v * F(l, r, rev[j] + 1)) % MOD
            else:
                tdp = dp  # no interval to process; keep current DP

            dp = [0] * (len(ys) + 1)
            
            if typ == 0:  # start of range constraint
                yidx = mp[y]
                for j in range(1, len(ys) + 1):
                    v = tdp[j]
                    if v:
                        idx = j if j <= yidx else yidx
                        dp[idx] = (dp[idx] + v) % MOD
            else:  # end of range constraint
                yidx = mp[y]
                for j in range(1, len(ys) + 1):
                    v = tdp[j]
                    if not v:
                        continue
                    dp[j] = (dp[j] + v) % MOD
                    idx = j if j <= yidx else yidx
                    dp[idx] = (dp[idx] - v) % MOD

        res = dp[mp[0]] % MOD  # result for the root value 0
        out_lines.append(str(res if res >= 0 else res + MOD))
    print("\n".join(out_lines))

if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/