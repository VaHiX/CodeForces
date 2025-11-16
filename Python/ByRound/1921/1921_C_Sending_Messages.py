# Problem: CF 1921 C - Sending Messages
# https://codeforces.com/contest/1921/problem/C

"""
Purpose: Determine if Stepan can send all messages given phone charge constraints.
         The phone consumes 'a' units of charge per time unit when on, and 'b' units
         when turning off and on. Messages must be sent at specific times.

Approach:
    - For each message, calculate the minimum charge needed to reach that time.
    - At each step, decide whether to turn off/on (costs 'b') or continue (costs 'a * time_diff').
    - If the available charge is insufficient, return "NO". Otherwise, continue.
    - The decision is made by comparing 'a * (m[i] - t)' and 'b' to choose the minimum cost.

Time Complexity: O(n) per test case, where n is the number of messages.
Space Complexity: O(n) for storing the message times, plus O(1) extra space.

Algorithms/Techniques:
    - Greedy approach with optimal decision at each step.
    - Linear scan through message times.
"""

import sys

input = sys.stdin.readline


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, f, a, b = readInts()  # n: number of messages, f: initial charge, a: cost/time, b: cost on/off
    m = readList()  # list of message times
    t = 0  # current time
    for i in range(n):
        # Calculate the minimum charge needed to reach message time m[i]
        # Either turn off/on (cost b) or continue (cost a * (m[i] - t))
        v = min(a * (m[i] - t), b)
        # If remaining charge is not enough to cover this cost, impossible to send message
        if f <= v:
            return "NO"
        t = m[i]  # update current time to message time
        f -= v  # reduce charge by the cost
    return "YES"  # all messages can be sent


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/