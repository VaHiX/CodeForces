# Problem: CF 2140 E1 - Prime Gaming (Easy Version)
# https://codeforces.com/contest/2140/problem/E1

"""
E1. Prime Gaming (Easy Version)
time limit per test3 seconds
memory limit per test512 megabytes

This is the easy version of the problem. The difference between the versions is that in this version,
m≤2. You can hack only if you solved all versions of this problem.

A valid configuration is defined as an arrangement of n piles of stones such that:
The number of stones in each pile is an integer between 1 and m (both inclusive).
Given a valid configuration of n piles of stones, some indices from 1 to n are marked as good. 
Alice and Bob start playing a game taking n−1 turns alternately with Alice going first. In each turn, 
they have to perform the following operation:
Choose any integer i such that 1≤i≤p (where p is the number of piles left) and i is good, and remove 
the i-th pile completely.
Note that after performing the operation once, the number of piles decreases by 1 and the remaining piles 
are re-indexed. The game will end when there is only one pile left. It is guaranteed that the index 1 is 
always good.

Let x denote the number of stones in the final remaining pile. Alice wants to maximize x, whereas Bob 
wants to minimize it. Both Alice and Bob play optimally.

Find the sum of x over all the possible valid configurations modulo 10^9 + 7.

Algorithm:
- Dynamic programming with bitmasking to compute the game states.
- For each subproblem, we determine if a state leads to a win for the current player (Alice or Bob) 
  by simulating optimal play using minimax logic on possible moves.
- Time complexity: O(n * 2^n)
- Space complexity: O(2^n)
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = map(int, input().split())
    k, c, mod = int(input()), list(map(int, input().split())), 10**9 + 7
    if m == 1:
        print(1)
        continue
    a = [[] for _ in range(n + 1)]
    for p in range(1, n + 1):
        for x in c:
            if x <= p:
                a[p].append(x)
    q = bytearray(2)
    q[0] = 0
    q[1] = 1
    for p in range(2, n + 1):
        s = 1 << p
        u = bytearray(s)  # `u` represents the DP state for the current pile size p.
        t = (n - p) % 2 == 0  # Determines if it's Alice's turn for this subgame.
        o = a[p]
        for S in range(s):   # Iterate over all possible subsets of piles represented by bitmask S
            if t:  # If it is Alice's turn (maximizing player)
                r = 0
                for i in o:
                    l = S & ((1 << (i - 1)) - 1)   # left part of mask
                    h = S >> i                     # right part of mask
                    sh = l | (h << (i - 1))        # combine masks after removing pile i
                    if q[sh]:                      # if this move is winning for the opponent, skip
                        r = 1
                        break
                u[S] = r
            else:  # If it is Bob's turn (minimizing player)
                r = 1
                for i in o:
                    l = S & ((1 << (i - 1)) - 1)
                    h = S >> i
                    sh = l | (h << (i - 1))
                    if not q[sh]:                  # if this move is losing for the opponent, skip
                        r = 0
                        break
                u[S] = r
        q = u   # Update current DP state
    w = sum(q)  # Count total winning configurations
    T = pow(m, n, mod)  # Total number of valid configurations
    z = (T - w + mod) % mod  # Number of losing configurations
    ans = (z + 2 * w) % mod   # Final result combining wins and losses appropriately
    print(ans)


# https://github.com/VaHiX/codeForces/