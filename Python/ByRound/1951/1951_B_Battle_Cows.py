# Problem: CF 1951 B - Battle Cows
# https://codeforces.com/contest/1951/problem/B

"""
Code Purpose:
This code solves the "Battle Cows" problem where cows with distinct ratings compete in a tournament. 
The goal is to determine the maximum number of matches cow k can win by optionally swapping its position with another cow once.

Algorithm/Techniques:
1. Simulate tournament process where each match is between the current position and the winner of previous match.
2. Try all valid swaps for cow k to see how many matches it can win.
3. For efficiency, avoid full simulation of all possible swaps by analyzing when cow k can win.

Time Complexity: O(n) per test case, since we do a single pass through the array for each swap candidate.
Space Complexity: O(n) for storing temporary arrays for simulation.
"""

import sys

rl = sys.stdin.readline


def cal():
    N, K = map(int, rl().split())  # Read number of cows and index of our cow
    ns = list(map(int, rl().split()))  # Read ratings of all cows
    me = ns[K - 1]  # Rating of our cow
    nstemp = ns[:]  # Copy original array for temporary use
    ans = 0  # Maximum wins our cow can get
    j = 0  # Track start of second phase
    tt = ns[0]  # Store original rating of first cow
    
    # Try swapping cow k with first cow (as it's the most impactful)
    ns[0], ns[K - 1] = ns[K - 1], ns[0]
    
    # Simulate the tournament with the swap
    for i in range(1, N):
        if ns[i] > me:  # If current cow has higher rating than ours
            ans = i - 1  # We win up to (i-1) matches
            # Swap back to simulate the other case (without change)
            nstemp[i], nstemp[K - 1] = nstemp[K - 1], nstemp[i]
            if K - 1 <= i or tt > me:
                # If we're not in a better position or original first cow was stronger
                return ans
            j = i  # Mark starting point for next section
            break
    else:
        # If we never lost, we win all matches except last one
        return N - 1
    
    # Continue simulation from where we left off to calculate further wins
    for i in range(j, N):
        if nstemp[i] > me:
            ans = max(ans, i - j)  # Update max wins
            break
    return ans


T = int(rl())
for _ in range(T):
    print(cal())


# https://github.com/VaHiX/CodeForces/