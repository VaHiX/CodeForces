# Problem: CF 2004 E - Not a Nim Problem
# https://codeforces.com/contest/2004/problem/E

"""
Purpose: Solve the game theory problem where players take stones from piles under GCD constraints.
Algorithm: 
- Precompute Sprague-Grundy values for all numbers up to 10^7 using sieve-like approach.
- For each pile size, lookup its Grundy number and XOR them all.
- If total XOR is 0, second player (Bob) wins; otherwise, first player (Alice) wins.
Time Complexity: O(N log log N) for computing Sprague-Grundy table + O(n) per query
Space Complexity: O(N) for storing Sprague-Grundy values
"""

import functools
import operator
import sys

input = lambda: sys.stdin.buffer.readline().decode()
N = 10**7 + 1
sg = [0] * N
sg[1] = 1
primes = []
for i in range(3, N, 2):
    if sg[i] == 0:
        primes.append(i)
        sg[i] = len(primes) + 1
    for p in primes:
        if p > primes[sg[i] - 2] or i * p >= N:
            break
        sg[i * p] = sg[p]
ansout = []
for _ in range(int(input())):
    ans = []
    input()
    ans = functools.reduce(
        operator.xor, (sg[x] for x in map(int, input().strip().split())), 0
    )
    ansout.append("Bob" if ans == 0 else "Alice")
sys.stdout.write("\n".join(ansout))


# https://github.com/VaHiX/CodeForces/