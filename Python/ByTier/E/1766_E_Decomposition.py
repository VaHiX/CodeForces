# Problem: CF 1766 E - Decomposition
# https://codeforces.com/contest/1766/problem/E

"""
Algorithm: Dynamic Programming with State Compression
Time Complexity: O(n)
Space Complexity: O(1)

This solution uses a dynamic programming approach where each state represents
a possible decomposition configuration of the sequence processed so far.
States are represented as tuples of integers, and transitions are computed
based on bitwise AND operations. For each element in the input, we update
the DP states and accumulate the total count of subsequences.

The key idea is to precompute all valid transitions between states and
use a rolling DP to count contributions efficiently.
"""

import sys

input = sys.stdin.buffer.readline

n = int(input())
A = list(map(int, input().split()))

# Predefined set of states (configurations of subsequences)
states = {
    (1, 2, 1),
    (1, 2),
    (2,),
    (2, 1),
    (3, 1),
    (1, 1),
    (1, 1, 2),
    (1,),
    (3, 2, 1),
    (2, 1, 2),
    (2, 2, 1),
    (3, 1, 2),
    (2, 2),
    (3, 2),
    (),
    (3,),
}
states = sorted(states)
K = len(states)
istate = {s: i for i, s in enumerate(states)}
state_lens = [len(s) for s in states]


def transition(s, x):
    # Compute the new state after adding x to the current state s
    if x == 0:
        return s
    else:
        for i, y in enumerate(s):
            if x & y:  # Check if bitwise AND is non-zero
                return s[:i] + (x,) + s[i + 1 :]
    return s + (x,)


# Precompute transition map for all states and input values (0-3)
trans_map = [[istate[transition(states[k], x)] for x in range(4)] for k in range(K)]

ret = 0
dp = [0] * K  # DP array to store count of each state
for a in A:
    dp2 = [0] * K  # Next DP state
    for k in range(K):
        # Update the transition based on current input value
        dp2[trans_map[k][a]] += dp[k]

    # Add new state for single element when a is not 0
    if a != 0:
        dp2[istate[(a,)]] += 1
    else:
        dp2[istate[()]] += 1

    dp = dp2  # Update DP array
    # Sum up the contribution of current state to the final answer
    cnt = sum([l * c for l, c in zip(state_lens, dp)])
    ret += cnt


# Handle special case for zeros in the sequence
for i, a in enumerate(A):
    if a == 0:
        ret += (i + 1) * (n - i)

print(ret)


# https://github.com/VaHiX/CodeForces/