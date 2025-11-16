# Problem: CF 1981 A - Turtle and Piggy Are Playing a Game
# https://codeforces.com/contest/1981/problem/A

"""
Algorithm: Greedy approach to maximize the number of divisions by choosing the largest possible number in the range.
The key insight is that to maximize the number of operations, we should choose the largest number in the range and keep dividing it by 2 (the smallest prime factor).
This leads to a logarithmic number of operations.

Time Complexity: O(log r) per test case
Space Complexity: O(1)
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    l, r = map(int, input().split())
    score = 0
    # Keep dividing r by 2 until it becomes 1
    # This gives the maximum number of operations possible for the largest number in range
    while r != 1:
        score += 1
        r //= 2  # Integer division by 2
    print(score)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/