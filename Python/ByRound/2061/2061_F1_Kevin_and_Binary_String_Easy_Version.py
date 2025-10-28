# Problem: CF 2061 F1 - Kevin and Binary String (Easy Version)
# https://codeforces.com/contest/2061/problem/F1

"""
F1. Kevin and Binary String (Easy Version)
Algorithms/Techniques: Greedy, Block manipulation, Simulation

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing block counts.

The problem involves transforming a binary string s into another binary string t,
using operations that swap two adjacent blocks of identical characters.
Each block is defined as a maximal substring of identical characters.

We process both strings into lists of block lengths and simulate the swaps,
using a greedy approach to match the target configuration.

Key steps:
1. Convert both strings into lists of block lengths (e.g., "00011" -> [3, 2]).
2. Check if transformation is possible by comparing total counts of '1's.
3. Simulate swaps greedily from right to left, matching blocks of t with those of s.

If at any point we cannot match or the transformation fails, return -1.
"""

import random
import sys

MOD = 10**9 + 7
RANDOM = random.randrange(2**62)


def gcd(a, b):
    if a % b == 0:
        return b
    else:
        return gcd(b, a % b)


def lcm(a, b):
    return a // gcd(a, b) * b


def w(x):
    return x ^ RANDOM


def solve():
    s = sys.stdin.readline().strip()
    t = sys.stdin.readline().strip()
    if s.count("1") != t.count("1"):  # Check if total number of '1's match
        print(-1)
        return
    i = 0
    L = []
    while i < len(s):
        f = s[i]
        count = 0
        while i < len(s) and s[i] == f:
            i += 1
            count += 1
        L.append(count)
    L1 = []
    i = 0
    while i < len(t):
        f = t[i]
        count = 0
        while i < len(t) and t[i] == f:
            i += 1
            count += 1
        L1.append(count)
    i = len(L) - 1
    len(L1) - 1  # This line does nothing but is a placeholder for potential logic
    ans = 0
    if s[-1] != t[-1]:  # If last characters don't match
        f = L.pop()  # Remove last block of s
        ans += 1  # One operation needed to match
        try:
            L[-2] += f  # Append the block to previous one (this is an optimization)
        except:
            L = [f] + L  # If no previous, create a new block at start
    while L and L1:  # While both lists have elements
        if L1[-1] < L[-1]:  # If current block in t is smaller than in s
            print(-1)
            return
        else:
            L1[-1] -= L[-1]  # Subtract the size of s's block from t's block
            L.pop()  # Remove s's block
            if L1[-1] == 0:  # If block in t is consumed completely
                L1.pop()
            else:
                ans += 1  # One more operation needed to merge two blocks
                if len(L) >= 3:  # If there are at least 3 blocks remaining
                    L[-3] += L[-1]  # Merge the last block with third last
                    L.pop()
                else:
                    if len(L) >= 2:  # If there are exactly two blocks left
                        L[-1], L[-2] = L[-2], L[-1]  # Swap them
                    else:
                        print(-1)
                        return
    if not L and not L1:  # If all blocks matched perfectly
        print(ans)
    else:
        print(-1)


for _ in range(int(sys.stdin.readline().strip())):
    solve()


# https://github.com/VaHiX/codeForces/