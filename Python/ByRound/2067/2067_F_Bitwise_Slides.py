# Contest 2067, Problem F: Bitwise Slides
# URL: https://codeforces.com/contest/2067/problem/F

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

    # prefix_xor[i] will store a_1 ^ a_2 ^ ... ^ a_i
    prefix_xor = [0] * (n + 1)
    for i in range(n):
        prefix_xor[i + 1] = prefix_xor[i] ^ a[i]

    # ways_triple: number of ways to have P = Q = R
    # ways_pair: map from Y to count of ways to have a permutation of (Y, Y, X_i)
    ways_triple = 1
    ways_pair = {}

    for i in range(1, n + 1):
        x_prev = prefix_xor[i - 1]
        x_curr = prefix_xor[i]

        # Ways to form the new triple state (x_curr, x_curr, x_curr) must come from
        # a pair state (x_curr, x_curr, x_prev) at step i-1.
        count_from_pair_to_triple = ways_pair.pop(x_curr, 0)

        new_ways_triple = count_from_pair_to_triple

        # Calculate contributions to the new ways_pair map.
        # - From the old triple state, we get 3 ways to form a pair state with paired value x_prev.
        # - From the pair states that just became triple, 2 of 3 choices lead to a pair state
        #   with paired value x_prev.
        contrib_to_x_prev = (3 * ways_triple + 2 * count_from_pair_to_triple) % MOD

        # Add the contribution to the ways_pair map for the key x_prev.
        # Other keys in ways_pair are implicitly carried over.
        ways_pair[x_prev] = (ways_pair.get(x_prev, 0) + contrib_to_x_prev) % MOD

        # Update ways_triple for the next iteration.
        ways_triple = new_ways_triple

    # The final answer is the sum of ways for all possible valid final states.
    total_ways = ways_triple
    for count in ways_pair.values():
        total_ways = (total_ways + count) % MOD

    print(total_ways)


# Main execution loop
try:
    t_str = sys.stdin.readline()
    if t_str:
        t = int(t_str)
        for _ in range(t):
            solve()
except (IOError, ValueError):
    pass
