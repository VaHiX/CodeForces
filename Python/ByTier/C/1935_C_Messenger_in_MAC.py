# Problem: CF 1935 C - Messenger in MAC
# https://codeforces.com/contest/1935/problem/C

"""
Algorithm: Dynamic Programming with Optimization
Techniques: 
- Sorting messages by b_i values
- Using a DP array to track minimum cost for selecting i messages
- Using a prefix minimum array (mn) to optimize transitions

Time Complexity: O(n^2) per test case, where n is the number of messages
Space Complexity: O(n) for the DP and mn arrays

The problem involves selecting a subset of messages such that the total reading time is at most l,
and we want to maximize the number of messages selected. The reading time of a set of messages is:
sum(a_i) + sum(|b_i - b_{i+1}|) for consecutive messages in the subset.

We sort messages by b_i and use dynamic programming where:
- dp[i] represents the minimum cost to select exactly i messages
- mn[i] keeps track of the minimum value of (dp[i] - b_i) seen so far
"""

import sys

int1 = lambda x: int(x) - 1
pDB = lambda *x: print(*x, end="\n", file=sys.stderr)
p2D = lambda x: print(*x, sep="\n", end="\n\n", file=sys.stderr)


def II():
    return int(sys.stdin.readline())


def LI():
    return list(map(int, sys.stdin.readline().split()))


def LLI(rows_number):
    return [LI() for _ in range(rows_number)]


def LI1():
    return list(map(int1, sys.stdin.readline().split()))


def LLI1(rows_number):
    return [LI1() for _ in range(rows_number)]


def SI():
    return sys.stdin.readline().rstrip()


dij = [(0, 1), (-1, 0), (0, -1), (1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
inf = -1 - (-1 << 62)

md = 10**9 + 7


def solve():
    n, l = LI()
    ab = LLI(n)
    ab.sort(key=lambda x: x[1])  # Sort messages by b_i
    dp = [inf] * (n + 1)  # dp[i] = minimum cost to select exactly i messages
    mn = [inf] * (n + 1)  # mn[i] = minimum (dp[i] - b_i) seen so far
    for a, b in ab:
        # Process from right to left to avoid overwriting values we need
        for i in range(2, n + 1)[::-1]:
            # Compute cost of extending a set of size (i-1) with current message
            cur = mn[i - 1] + b + a  # Cost for selecting i messages with current b as last
            dp[i] = min(dp[i], cur)
            mn[i] = min(mn[i], cur - b)  # Update minimum (dp[i] - b_i)
        # Update case for selecting exactly 1 message
        dp[1] = min(dp[1], a)
        mn[1] = min(mn[1], a - b)
    
    # Find maximum number of messages whose cost <= l
    for i in range(n, -1, -1):
        if dp[i] <= l:
            print(i)
            return
    print(0)


testnumber = II()

for testcase in range(testnumber):
    solve()


# https://github.com/VaHiX/CodeForces/