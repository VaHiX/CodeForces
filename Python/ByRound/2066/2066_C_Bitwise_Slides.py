# Problem: CF 2066 C - Bitwise Slides
# https://codeforces.com/contest/2066/problem/C

"""
C. Bitwise Slides

Purpose:
This code solves a dynamic programming problem where we are given an array of integers and need to count the number of ways to assign operations (P⊕, Q⊕, R⊕) to each element such that after every step, P, Q, and R remain pairwise non-distinct.

Techniques:
- Prefix XOR with randomization to reduce collisions
- Dynamic Programming on states representing possible values of P, Q, R
- Bit manipulation using XOR operations

Time Complexity: O(n), where n is the size of the input array.
Space Complexity: O(1), as we use a fixed-size dictionary and prefix XOR array.

Algorithm:
We maintain a prefix XOR array to represent cumulative XORs up to each index. For each step,
we consider two values l and r which correspond to previous and current XOR state respectively.
We update the DP states using transitions, where for each state value, it's updated based on 
the number of valid operations that do not violate the pairwise distinct rule for P, Q, R.

The core idea relies on maintaining a mapping from XOR results to how many ways lead to that result,
and applying transitions correctly as we progress through elements.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
from collections import defaultdict
from random import randint

mod = 1000000007


def solve():
    n = int(input())
    # Random seed to avoid collisions in XOR values
    rd = randint(1, (1 << 30) - 1)
    xor = [rd]  # Prefix XOR array initialized with random value
    
    # Compute prefix XORs for the input array
    for x in map(int, input().split()):
        xor.append(xor[-1] ^ x)
    
    # dp maps current XOR state to number of ways to reach that state
    dp = defaultdict(int)
    dp[rd] = 1  # Start with initial random value
    
    # Iterate over the array and process each element
    for i in range(n):
        l, r = xor[i], xor[i + 1]  # Previous and current prefix XOR values
        # Update the number of ways to reach state 'l' using transitions:
        # Each way to get to 'l' can produce 3 new paths, and ways from 'r' contribute 2 new paths.
        dp[l] = (dp[l] * 3 + dp[r] * 2) % mod
    
    # Return the sum of all valid paths modulo 10^9 + 7
    return sum(dp.values()) % mod


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/