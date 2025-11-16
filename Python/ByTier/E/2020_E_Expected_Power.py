# Problem: CF 2020 E - Expected Power
# https://codeforces.com/contest/2020/problem/E

"""
Algorithm: Dynamic Programming with XOR expectation
Technique: Bitwise XOR expectation calculation using DP over all possible XOR values

Time Complexity: O(n * 1024) per test case, where n is the size of the array
Space Complexity: O(1024) for the DP arrays, which is constant (1024 is a fixed constant)

This solution calculates the expected value of (f(S))^2 where f(S) is the XOR of all elements in a random multiset S.
Each element ai is inserted with probability pi/10000.
We use dynamic programming to compute the probability of each possible XOR result.
Then we compute the expected value of (XOR)^2 by summing over all XOR values.
Finally, we adjust for the overall probability using modular inverse.
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
    n, a, p = readInt(), readList(), readList()
    dp, ndp = [0] * 1024, [0] * 1024  # DP arrays for current and next state
    dp[0] = 1  # Initially, probability of XOR = 0 is 1
    v = 10**4  # Total probability denominator
    
    # For each element, update the probability distribution of XOR values
    for ai, pi in zip(a, p):
        # For each possible XOR value, calculate new probabilities
        for j in range(1024):
            # Probability of getting XOR j:
            # - Keep current XOR j: dp[j] * (v - pi) / v
            # - Get new XOR j ^ ai: dp[j ^ ai] * pi / v
            ndp[j] = ((dp[j] * (v - pi)) + dp[j ^ ai] * pi) % m
        # Swap dp and ndp arrays
        dp, ndp = ndp, dp
    
    # Calculate expected value of (XOR)^2
    ans = 0
    for i in range(1024):
        ans += (i**2 * dp[i]) % m  # Add contribution of XOR value i squared
        ans %= m  # Keep result within modulo
    
    # The result needs to be multiplied by (10000)^(-n) to normalize
    # Using modular inverse: (10000)^(-n) = pow(10000, m-2, m) ^ n
    dv = pow(v, m - 2, m)  # Modular inverse of v under modulo m
    return ((ans % m) * pow(dv, n, m)) % m  # Apply normalization


m = 10**9 + 7  # Modulo value
for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/