# Problem: CF 1783 E - Game of the Year
# https://codeforces.com/contest/1783/problem/E

"""
Algorithm: 
  - For each k from 1 to n, simulate the game to determine if Monocarp kills all bosses.
  - Optimization using prefix sum technique to avoid simulating the game for each k.
  - For each boss i, determine whether Monocarp will kill it when k = k0.
  - Build a prefix sum array that encodes the "turn" information:
    - If a[i] > b[i], Monocarp kills the boss at a[i]-th attempt (Polycarp fails before).
    - We increment pref[b[i]] and decrement pref[a[i]].
  - Then compute prefix sums to get the number of times each step happens.
  - For each k, check if all bosses are killed by Monocarp in the sequence.

Time Complexity: O(n^2) in worst case (but due to optimization using prefix sum, more efficient in practice).
Space Complexity: O(n) for the prefix array and result list.

"""

import sys

input = sys.stdin.readline
I = lambda: list(map(int, input().split()))

(t,) = I()
for _ in range(t):
    (n,) = I()
    a = I()
    b = I()
    an = []
    pref = [0] * (n + 2)
    for i in range(n):
        if a[i] > b[i]:
            # Mark the interval [b[i], a[i]) where Monocarp is in control
            pref[b[i]] += 1
            pref[a[i]] -= 1
    # Compute prefix sum to get the count of how many times Monocarp has turn
    for i in range(2, n + 2):
        pref[i] += pref[i - 1]

    # For each possible k from 1 to n, check if Monocarp wins
    for i in range(1, n + 1):
        pos = 1  # Assume Monocarp wins
        for j in range(i, n + 1, i):  # Check every k-th boss
            if pref[j]:  # If Monocarp is in control at step j
                pos = 0  # Monocarp didn't kill this boss, so he loses
        if pos:
            an.append(i)
    print(len(an))
    print(*an)


# https://github.com/VaHiX/CodeForces/