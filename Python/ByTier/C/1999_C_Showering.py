# Problem: CF 1999 C - Showering
# https://codeforces.com/contest/1999/problem/C

"""
Code Purpose:
This code determines whether Alex can take a shower given a set of non-overlapping busy time intervals and the duration of the shower.
It checks for gaps between tasks and at the end of the day to see if there is a continuous free interval of at least `s` minutes.

Algorithms/Techniques:
- Greedy approach: Iterates through the sorted intervals to check for available gaps.
- Linear scan: Processes each interval once to find potential shower time.

Time Complexity: O(n)
Space Complexity: O(1)
"""

import sys


def debug(*args):
    pass


def pow(x, y, m=10**9 + 7):
    ans = 1
    x %= m
    while y:
        if y & 1:
            ans = (ans * x) % m
        x = (x * x) % m
        y >>= 1
    return ans


def solve():
    n, s, m = map(int, input().split())  # Read number of tasks, shower time, and total minutes in a day
    last = 0  # Initialize the end of the last interval processed
    f = 0  # Flag to indicate if a sufficient gap was found
    for _ in range(n):
        l, r = map(int, input().split())  # Read current task interval
        t = l - last  # Compute the gap between the last interval and current interval
        debug(l, r, last, t, s)
        last = r  # Update the end of the last interval
        if t >= s:  # If the gap is sufficient for the shower
            f = 1  # Mark that a valid gap exists
    if m - last >= s:  # Check if the gap at the end of the day is sufficient
        f = 1
    print("YES" if f else "NO")  # Output the result


if __name__ == "__main__":
    input = sys.stdin.readline
    TCS = int(input())  # Read number of test cases
    for TC in range(1, TCS + 1):
        debug(TC)
        solve()


# https://github.com/VaHiX/CodeForces/