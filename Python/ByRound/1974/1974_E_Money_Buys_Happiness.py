# Problem: CF 1974 E - Money Buys Happiness
# https://codeforces.com/contest/1974/problem/E

"""
Algorithm: Dynamic Programming with optimized state space
Techniques: 0/1 knapsack variant with time constraints and money flow

Time Complexity: O(m * H * x) where m is the number of months, H is the total happiness sum
Space Complexity: O(H) where H is the total happiness sum

The solution uses dynamic programming where dp_cur[h] represents the minimum money needed
to achieve happiness sum h by the current month. For each month, we update the DP array
based on whether we can afford to buy the happiness or not, considering the money earned
in previous months and the cost of purchasing happiness.

Since borrowing isn't allowed, money can only be spent in later months.
"""

import sys

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s) - 1])


def invr():
    return map(int, input().split())


def solution():
    m, x = inlt()
    stat = []
    tot_h = 0
    for i in range(m):
        ci, hi = inlt()
        tot_h += hi
        stat.append((ci, hi))
    dp_cur = [-1] * (tot_h + 1)
    dp_cur[0] = 0
    for i in range(m):
        ci, hi = stat[i]
        dp_nxt = [-1] * (tot_h + 1)
        dp_nxt[0] = 0
        for h in range(tot_h + 1 - hi):
            if dp_cur[h] >= 0:
                # We can carry forward the money (earn x pounds) without buying anything
                dp_nxt[h] = max(dp_nxt[h], dp_cur[h] + x)
            if dp_cur[h] >= ci:
                # We can afford to buy the happiness in current month
                # Update the state for higher happiness
                dp_nxt[h + hi] = max(dp_nxt[h + hi], dp_cur[h] - ci + x)
        dp_cur = dp_nxt

    ans = max(h for h in range(tot_h + 1) if dp_cur[h] >= 0)
    print(ans)
    return


if __name__ == "__main__":
    t = inp()
    for i in range(t):
        solution()


# https://github.com/VaHiX/CodeForces/