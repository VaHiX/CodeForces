# Problem: CF 1991 H - Prime Split Game
# https://codeforces.com/contest/1991/problem/H

"""
Algorithm: Game Theory with Sprague-Grundy Theory and Precomputed Values
Time Complexity: O(N + T * n) where N = 2 * 10^5, T is number of test cases, n is average pile size
Space Complexity: O(N) for precomputed arrays and sieve

This program solves a game theory problem where players take turns splitting stones into prime-sized piles.
The key insight is to precompute the Grundy number (nimber) for each pile size, which determines the game state.
We use a sieve to find primes and then build lookup tables for valid moves and game outcomes.
"""

N = 2 * 10**5 + 1
sieve = [-1] * N
primes = []
for i in range(2, N):
    if sieve[i] == -1:
        for j in range(i, N, i):
            sieve[j] = i
        primes.append(i)
p = [0] * N
primes1 = []
for i in primes:
    if sieve[i - 2] == i - 2:
        p[i] = p[i - 2] + 1
        p[i] %= 2
        if i != 7:
            primes1.append(i)
l = [0] * N
l1 = [0] * N
for i in range(0, N, 6):
    l[i] = 3
for i in range(2, N, 6):
    l[i] = 3
for i in range(4, N, 6):
    l[i] = 1
for i in range(0, 12, 2):
    l[i] = 0
l[16] = 0
l[14] = 1
for i in [
    12,
    42,
    72,
    20,
    26,
    32,
    38,
    50,
    56,
    62,
    68,
    80,
    92,
    98,
    110,
    122,
    128,
    140,
    152,
    182,
    188,
    212,
    266,
    272,
    296,
    332,
    361,
    392,
    482,
    512,
]:
    l[i] = 2
for i in primes:
    l[i] = 1 << 1 - p[i]
    if i + 2 < N:
        l[i + 2] = 1 << p[i]
    if i + 3 < N:
        l[i + 3] |= 1 << p[i]
    if i + 5 < N:
        l[i + 5] |= 2
for i in range(len(primes1)):
    for j in range(i, len(primes1)):
        if primes1[i] + primes1[j] < N:
            l1[primes1[i] + primes1[j]] = 1
        else:
            break
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = [l[i] for i in a]
    x = sum(l1[i] for i in a)
    if n % 2 == 0:
        if 3 in b or 1 in b:
            print("Alice")
        else:
            print("Bob")
    else:
        if b == [3] * n:
            if x == n:
                print("Bob")
            elif x > 0:
                print("Alice")
            else:
                print("Bob")
        elif (1 in b or 3 in b) and (0 in b or 2 in b or 0 < x < n):
            print("Alice")
        else:
            print("Bob")


# https://github.com/VaHiX/CodeForces/