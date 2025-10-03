# Problem: CF 2067 F - Bitwise Slides
# https://codeforces.com/contest/2067/problem/F

"""
F. Bitwise Slides

Problem Description:
Given an array of integers a[1..n], we need to assign each element to one of three variables P, Q, R using XOR operations.
After each assignment, the values of P, Q, and R must remain pairwise non-distinct (i.e., not all three are different).
We count how many valid sequences exist modulo 10^9 + 7.

Approach:
This is a dynamic programming problem where we track the number of ways to assign values such that at any point,
the current values of P, Q, R are not pairwise distinct. We use prefix XORs to efficiently compute state transitions.
We maintain a mapping from XOR value to the number of ways we can end up with that value for P (or equivalently Q, or R).
The key insight is that if three numbers are not pairwise distinct, then at least two of them are equal.
So in each step we only track valid states where at least two variables are equal.

Time Complexity: O(n)
Space Complexity: O(n)

"""
import sys


def solve():
    """
    Solves a single test case for the Bitwise Slides problem.
    """
    MOD = 10**9 + 7
    try:
        n_str = sys.stdin.readline()
        if not n_str:
            return
        n = int(n_str)
        a = list(map(int, sys.stdin.readline().split()))
    except (IOError, ValueError):
        return

    # Compute prefix XOR to help with state transitions
    prefix_xor = [0] * (n + 1)
    for i in range(n):
        prefix_xor[i + 1] = prefix_xor[i] ^ a[i]

    # Initialize DP tracking:
    # ways_triple: number of sequences where P = Q = R at current step (i.e. all three are equal)
    # ways_pair: map from XOR value to number of sequences ending with that value such that two of P, Q, R are equal
    ways_triple = 1
    ways_pair = {}
    
    for i in range(1, n + 1):
        x_prev = prefix_xor[i - 1]  # Previous cumulative XOR (represents prefix before current element)
        x_curr = prefix_xor[i]      # Current cumulative XOR (includes current element)

        # Count of sequences transitioning to triple equality via pair
        count_from_pair_to_triple = ways_pair.pop(x_curr, 0)
        new_ways_triple = count_from_pair_to_triple

        # Contribution from previous states
        contrib_to_x_prev = (3 * ways_triple + 2 * count_from_pair_to_triple) % MOD
        # Update the number of ways to reach x_prev with two equal variables
        ways_pair[x_prev] = (ways_pair.get(x_prev, 0) + contrib_to_x_prev) % MOD
        
        # Update triple way count for next iteration
        ways_triple = new_ways_triple

    total_ways = ways_triple
    for count in ways_pair.values():
        total_ways = (total_ways + count) % MOD
    print(total_ways)


try:
    t_str = sys.stdin.readline()
    if t_str:
        t = int(t_str)
        for _ in range(t):
            solve()
except (IOError, ValueError):
    pass


# https://github.com/VaHiX/codeForces/