# Problem: CF 1985 F - Final Boss
# https://codeforces.com/contest/1985/problem/F

"""
Algorithm: Binary Search on Answer
Technique: Use binary search to find the minimum number of turns needed to kill the boss.
           For a given number of turns 't', we calculate the total damage that can be dealt
           using all attacks that are not on cooldown at that time.

Time Complexity: O(N * log(max_turns)) where N is the number of attacks.
                 max_turns is roughly bounded by (h / min_damage) * max_cooldown.
Space Complexity: O(1) - only using a few variables for computation.

The solution uses binary search over the number of turns, and for each candidate number of turns,
it computes how much damage can be done with all available attacks considering their cooldowns.
"""

import sys

input = sys.stdin.readline


def solve():
    h, n = map(int, input().strip().split())
    A = list(map(int, input().strip().split()))
    C = list(map(int, input().strip().split()))
    
    # Initialize binary search bounds
    l = 0
    a, c = A[0], C[0]
    # Estimate an upper bound based on the best attack
    natt = (h + a - 1) // a  # Number of times the best attack needs to be used
    r = 1 + (natt - 1) * c + 1  # Upper bound: turn when the last attack can be used

    # Binary search for minimum number of turns
    while r - l > 1:
        m = l + (r - l) // 2  # Midpoint, current number of turns being tested
        s = 0  # Total damage that can be dealt in m turns
        for aa, cc in zip(A, C):  # For each attack
            # Calculate how many times attack 'aa' can be used in 'm' turns
            # (m - 1) // cc gives number of full cooldown cycles before turn m
            # +1 because we can use the attack one more time at turn m
            s += ((m - 1) // cc + 1) * aa
            if s >= h:  # Early termination if we've already killed the boss
                r = m
                break
        else:
            # If we didn't break, then we couldn't kill the boss in 'm' turns
            l = m
    
    print(r)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/