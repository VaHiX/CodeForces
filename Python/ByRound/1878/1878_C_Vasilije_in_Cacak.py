# Problem: CF 1878 C - Vasilije in Cacak
# https://codeforces.com/contest/1878/problem/C

"""
Problem: Determine if it's possible to choose k distinct integers from [1, n] such that their sum equals x.

Approach:
- To check feasibility, we compute the minimum and maximum possible sums of k distinct integers from [1, n].
- Minimum sum: Choose 1, 2, ..., k => sum = k*(k+1)/2
- Maximum sum: Choose (n-k+1), (n-k+2), ..., n => sum = k*n - k*(k-1)/2
- If x lies within this range, return "YES", else "NO".

Time Complexity: O(1) per test case
Space Complexity: O(1) excluding input/output storage
"""

from sys import stdin

input = stdin.readline


def ri():
    return int(input())


def rl(v_type=int, output=list):
    return output(map(v_type, input().split()))


def rs():
    return input()[:-1]


def out(x, sep="\n"):
    print(sep.join(x))


def solve():
    n, k, s = rl(output=tuple)
    # Check if the sum s is within the possible range
    # Minimum sum when choosing 1,2,...,k
    min_sum = k * (k + 1) // 2
    # Maximum sum when choosing (n-k+1), ..., n
    max_sum = k * n - (k - 1) * k // 2
    if s <= max_sum and s >= min_sum:
        return "YES"
    return "NO"


output = []
for _ in range(ri()):
    output.append(solve())
out(output)


# https://github.com/VaHiX/CodeForces/