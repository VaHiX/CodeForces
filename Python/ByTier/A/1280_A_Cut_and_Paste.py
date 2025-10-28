# Problem: CF 1280 A - Cut and Paste
# https://codeforces.com/contest/1280/problem/A

"""
Algorithms/Techniques: Simulation with string manipulation and optimization using precomputed segments.

Time Complexity: O(x * log(x)) in the worst case, due to iterative operations on the string with exponential growth,
                 but optimized using segment-based approach.
Space Complexity: O(x), as we store a temporary array of size up to x to simulate parts of the string.

The problem involves simulating a series of cursor-based string operations on a string s, where each step
involves moving the cursor, cutting the right portion into clipboard, and pasting the clipboard
a number of times based on the current character under the cursor. The goal is to determine
the final length of the string after x steps.
"""

import sys

input = lambda: sys.stdin.readline().strip()


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def LFI():
    return list(map(float, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


fmax = lambda x, y: x if x > y else y
fmin = lambda x, y: x if x < y else y
MOD = 10**9 + 7
t = II()
outs = []
for _ in range(t):
    x = II()
    s = I()
    n = len(s)
    tmp = [0] * x
    # Initialize the first part of tmp array with values from string s
    for i in range(fmin(n, x)):
        tmp[i] = int(s[i]) - 1
    l = 0
    # Simulate the process until we reach x operations
    while n < x and l < x:
        left = n
        right = min(x, n + (n - l - 1) * tmp[l])
        # Fill in repeated pattern from previous segment
        for i in range(left, right):
            tmp[i] = tmp[i - (n - l - 1)]
        # Update the length of string based on current expansion rules
        n += (n - l - 1) * tmp[l] % MOD
        l += 1
    # Continue with remaining operations if necessary
    while l < x:
        n += (n - l - 1) * tmp[l] % MOD
        l += 1
    outs.append(n % MOD)
print("\n".join(map(str, outs)))


# https://github.com/VaHiX/codeForces/