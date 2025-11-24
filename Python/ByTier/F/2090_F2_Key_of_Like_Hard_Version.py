# Problem: CF 2090 F2 - Key of Like (Hard Version)
# https://codeforces.com/contest/2090/problem/F2

# Flower Box Description

"""
Code Purpose:
This solution computes the expected number of successful matches for each participant 
in a game where members take turns trying to open locks using keys. Each key either
opens a lock or is a counterfeit. The members play optimally, choosing the best 
key-lock pairs to maximize the probability of success. The problem involves dynamic 
programming with probabilistic analysis to compute expected values under optimal play.

Algorithms & Techniques:
- Dynamic Programming (DP) with state transitions
- Probabilistic analysis with modular arithmetic
- Precomputation of modular inverses for efficient computation
- Optimal strategy modeling where players select pairs that maximize success probability

Time Complexity:
O(k * l * n) where:
- k: number of counterfeit keys
- l: number of locks
- n: number of participants
This complexity arises from nested loops over all states of keys, locks, and players.

Space Complexity:
O(k * l * n) for the DP table f[d][i][j] where:
- d: number of counterfeit keys used so far
- i: number of locks remaining
- j: index of current player

The code maintains an array of modular inverses for efficient modular division operations.
"""

import sys

MOD = 10**9 + 7
INV2 = 500000004
MAXN = 20000
inv = [0] * MAXN
inv[1] = 1
for i in range(2, MAXN):
    inv[i] = MOD - MOD // i * inv[MOD % i] % MOD  # Precompute modular inverses


def readints():
    return list(map(int, sys.stdin.read().split()))


input_data = []


def read():
    global input_data
    if not input_data:
        input_data = readints()
    return input_data.pop(0)


def solve():
    T = read()
    for _ in range(T):
        init()


def init():
    n = read()
    l = read()
    k = read()
    f = [[[0] * n for _ in range(l + 1)] for _ in range(k + 1)]  # DP table
    pre = [0] * (n + 1)  # Prefix sums for optimization
    p = [0] * n  # Temporary array for intermediate calculations
    q = [0] * n  # Temporary array for intermediate calculations
    for i in range(1, l + 1):  # Iterate through number of locks
        s = 1  # Initialize sum
        a = i // n  # Calculate integer division for optimization
        b = i % n  # Calculate modulo for optimization
        
        # Update s with previous state values
        for j in range(n):
            s += f[0][i - 1][j]
            if s >= MOD:
                s -= MOD
                
        s = a * s % MOD  # Multiply with a
        pre[0] = 0  # Initialize prefix sum array
        for j in range(n):
            pre[j + 1] = pre[j] + f[0][i - 1][j]
            if pre[j + 1] >= MOD:
                pre[j + 1] -= MOD
                
        pre[n] += 1  # Add 1 to final element of prefix array
        if pre[n] >= MOD:
            pre[n] -= MOD
            
        # Compute f[0][i][j] for all players for current lock count
        for j in range(b):
            temp = pre[j] + pre[n] - pre[n - b + j]
            if temp >= MOD:
                temp -= MOD
            if temp < 0:
                temp += MOD
            f[0][i][j] = temp
            
        for j in range(b, n):
            temp = pre[j] - pre[j - b]
            if temp < 0:
                temp += MOD
            f[0][i][j] = temp
            
        # Normalize the results using modular inverse
        for j in range(n):
            f[0][i][j] = (f[0][i][j] + s) * inv[i] % MOD
            
    # Process all values of counterfeit keys
    for d in range(1, k + 1):
        for i in range(1, l + 1):
            s = 1
            a = i // n
            b = i % n
            
            for j in range(n):
                s += f[d][i - 1][j]
                if s >= MOD:
                    s -= MOD
                    
            s = a * s % MOD
            pre[0] = 0
            for j in range(n):
                pre[j + 1] = pre[j] + f[d][i - 1][j]
                if pre[j + 1] >= MOD:
                    pre[j + 1] -= MOD
                    
            pre[n] += 1
            if pre[n] >= MOD:
                pre[n] -= MOD
                
            # Compute p[j] for optimization
            for j in range(b):
                temp = pre[j] + pre[n] - pre[n - b + j]
                if temp >= MOD:
                    temp -= MOD
                if temp < 0:
                    temp += MOD
                p[j] = temp
                
            for j in range(b, n):
                temp = pre[j] - pre[j - b]
                if temp < 0:
                    temp += MOD
                p[j] = temp
                
            # Update p[j] using add_term and other calculations
            for j in range(n):
                add_term = d * f[d - 1][i][(j + n - i % n) % n] % MOD
                p[j] = (p[j] + s + add_term) * inv[i + d] % MOD
                
            # Prepare q[j] for second computation step
            s = 1
            a = (i + d) // n
            b = (i + d) % n
            
            for j in range(n):
                s += f[d][i - 1][j]
                if s >= MOD:
                    s -= MOD
                    
            s = a * s % MOD
            pre[0] = 0
            for j in range(n):
                pre[j + 1] = pre[j] + f[d][i - 1][j]
                if pre[j + 1] >= MOD:
                    pre[j + 1] -= MOD
                    
            pre[n] += 1
            if pre[n] >= MOD:
                pre[n] -= MOD
                
            for j in range(b):
                temp = pre[j] + pre[n] - pre[n - b + j]
                if temp >= MOD:
                    temp -= MOD
                if temp < 0:
                    temp += MOD
                q[j] = temp
                
            for j in range(b, n):
                temp = pre[j] - pre[j - b]
                if temp < 0:
                    temp += MOD
                q[j] = temp
                
            # Update q[j] and compute final value
            for j in range(n):
                q[j] = (q[j] + s) * inv[i + d] % MOD
                
            # Final computation for f[d][i][j] using weighted average
            for j in range(n):
                num = (i - 1) * p[j] + (i + d - 1) * q[j]
                f[d][i][j] = num % MOD * inv[(i << 1) + d - 2] % MOD
                
    # Print results for all players
    print(" ".join(str(f[k][l][i]) for i in range(n)))

solve()

# https://github.com/VaHiX/CodeForces/