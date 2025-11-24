# Problem: CF 2027 E2 - Bit Game (Hard Version)
# https://codeforces.com/contest/2027/problem/E2

"""
Algorithm: Game Theory with Bit Manipulation and Dynamic Programming
Purpose: Count the number of game states where Bob wins, given constraints on pile sizes and move rules.
Time Complexity: O(n * log^2(max(b_i)) + log^3(max(a_i)))
Space Complexity: O(log^2(max(a_i)) + log^3(max(b_i)))

The approach uses:
1. Precomputed binomial coefficients for combinatorial calculations
2. Bitwise analysis to determine valid moves for each pile
3. Dynamic programming to compute winning states
4. Mathematical manipulation to handle range queries efficiently
"""

import sys
from functools import reduce
from operator import add

input = sys.stdin.readline
rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():
    def init():
        # Precompute binomial coefficients for combinations
        comb = [[0] * 32 for _ in range(32)]
        for i in range(32):
            for j in range(i + 1):
                comb[i][j] = [1, comb[i - 1][j] + comb[i -1][j - 1]][j > 0]
        return comb

    M, comb = int(1e9 + 7), init()
    n, piles = rn(), list(zip(rl(), rl()))

    def calc_fl(piles):
        list_add = lambda l1, l2: list(map(add, l1, l2))

        def calc1(n, k):
            # Calculate contribution from numbers with certain bit counts
            f, cnt = [0] * 32, 0
            for i in range(k - 1, -1, -1):
                if n & (1 << i):
                    for r in range(cnt, cnt + i + 1):
                        f[r] += comb[i][r - cnt]
                    cnt += 1
            f[n.bit_count()] += 1
            return f

        def calc2(a, c, k):
            # More complex function to handle boundary cases
            f, cnt1, cnt2, in_prefix = [0] * 32, 1, 0, True
            p = (a - (1 << (k - 1))).bit_length()
            for i in range(k - 2, -1, -1):
                x, y = (a & (1 << i)) > 0, (c & (1 << i)) > 0
                in_prefix = in_prefix and x == y
                cnt1 += in_prefix and x
                cnt2 += not in_prefix and y
                cnt = cnt1 + cnt2
                if not y:
                    if cnt2 == 0:
                        f[0] += 1
                    elif cnt & 1 and cnt1 == 1 and (1 << i) + (1 << (k - 1)) > a:
                        f[cnt - 1] += 1
                    else:
                        f[cnt + 1] += 1
                    for r in range(cnt + 2, cnt + i + 2):
                        if ~r & 1 and cnt1 == 1:
                            f[r] += (
                                comb[i][r - cnt - 1] - comb[max(0, i - p)][r - cnt - 1]
                            )
                            f[r - 2] += comb[max(0, i - p)][r - cnt - 1]
                        else:
                            f[r] += comb[i][r - cnt - 1]
            return f

        def calc3(a, k):
            # Combine results of calc1 and calc2
            return list_add(calc1(a, k), calc2(a, a, k))

        def calc4(a, b, k):
            # Calculate difference between two calculated functions
            return (
                calc1(min(a, b), k)
                if b <= a
                else [u - v for (u, v) in zip(calc3(a, k), calc2(a, b, k))]
            )

        def calc5(a, b):
            # Main function to calculate the base state for a given range
            len_a = a.bit_length()
            t = b & ~(-1 << len_a)
            f = list(zip(calc3(a, len_a), calc4(a, t, len_a)))
            r = [u * (b >> len_a) + v for (u, v) in f]
            return [r[i] - [0, 1][i == 0] for i in range(32)]

        return [calc5(a, b) for (a, b) in piles]

    def calc_dp(fl):
        # Dynamic programming using bitwise XOR to combine game states
        def dp_updater(dp, f):
            return [sum([dp[j] * f[i ^ j] for j in range(32)]) % M for i in range(32)]

        return reduce(dp_updater, fl, [1] + [0] * 31)

    def solver(piles):
        fl = calc_fl(piles)
        return calc_dp(fl)[0] % M

    init(), print(solver(piles))


[solve() for _ in range(rn())]


# https://github.com/VaHiX/CodeForces/