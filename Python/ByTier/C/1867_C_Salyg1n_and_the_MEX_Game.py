# Problem: CF 1867 C - Salyg1n and the MEX Game
# https://codeforces.com/contest/1867/problem/C

"""
Algorithm/Technique: 
- The problem is an interactive game between Alice (maximizer) and Bob (minimizer).
- The goal is to maximize the MEX of the set S.
- Alice starts by finding the minimum excluded non-negative integer (MEX) from the initial set.
- Then, she adds this MEX to the set to ensure that the MEX remains at least this value.
- Bob aims to minimize the MEX by removing numbers, but only those less than the last number Alice added.
- The key insight is that Alice can always add the MEX of the current set (which ensures that it's at least that value) and then Bob can only remove numbers less than the last number added.
- If Alice adds a number x, then Bob can remove any number y < x.
- Alice will always add a number that keeps MEX as high as possible.
- The MEX is at least as large as any valid non-negative integer in the set S.
- By starting with MEX, Alice ensures that the final MEX after all moves is at least the MEX of the initial set.
Time Complexity: O(n + M) where n is the size of set S and M is the MEX value to be found (at most 10^5)
Space Complexity: O(n) for storing the set S
"""

import os
import sys

input = sys.stdin.buffer.readline


def fp(x):
    # Function to print output and flush it
    os.write(1, str(x).encode("ascii") + b"\n")


def solve() -> None:
    # Read the size of initial set (we don't use this in logic, just for reading)
    int(input())
    # Read the initial set S
    s = set(map(int, input().split()))
    # Find the minimum excluded non-negative integer (MEX) of the set
    for i in range(100001):  # We only check up to 10^5 as per constraints
        if i not in s:
            fp(i)  # Add the MEX to set S
            x = int(input())  # Read Bob's move
            # Process Bob's moves until game ends
            while x >= 0:
                fp(x)  # Tell Bob to remove y
                x = int(input())  # Read next move from Bob
            return


t = 1
t = int(input())  # Read number of test cases
while t:
    t -= 1
    solve()  # Solve each test case


# https://github.com/VaHiX/CodeForces/