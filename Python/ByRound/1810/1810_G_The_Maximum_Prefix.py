# Problem: CF 1810 G - The Maximum Prefix
# https://codeforces.com/contest/1810/problem/G

"""
Code Purpose:
This code computes the expected score for arrays of varying lengths, where each element of the array
is either 1 or -1, with probabilities specified for each position. The expected score is computed
based on the maximum prefix sum of the generated array, using dynamic programming to efficiently
calculate the expected values.

Algorithms/Techniques:
- Dynamic Programming
- Modular Exponentiation for computing inverses
- Probabilistic calculation of prefix sums

Time Complexity: O(n^2)
Space Complexity: O(n)
"""

mod = int(1e9 + 7)


def fpow(a, b):
    # Fast exponentiation to compute modular inverse
    ans = 1
    while b:
        if b & 1:
            ans = (ans * a) % mod
        a = (a * a) % mod
        b >>= 1
    return ans


t = int(input())
for _ in range(t):
    n = int(input())
    p_arr = [0] * n
    q_arr = [0] * n

    for i in range(n):
        x, y = map(int, input().split())
        # Compute probability p_i = x/y mod (10^9 + 7)
        p = (x * fpow(y, mod - 2)) % mod
        p_arr[i] = p
        # q_i = 1 - p_i
        q_arr[i] = (1 - p_arr[i] + mod) % mod

    h_arr = list(map(int, input().split()))

    # sol[0] represents the previous state, sol[1] the current state
    sol = [[0] * (n + 1), [0] * (n + 1)]
    sol[0] = h_arr  # Initialize with base case: expected score when max prefix sum is j

    result = [0] * n  # Stores final expected scores for k = 1 to n
    for i in range(1, n + 1):
        # Compute new expected scores using the recurrence relation:
        # For each prefix sum j, we compute the expected value for k = i
        sol[1] = [
            (p_arr[i - 1] * sol[0][j + 1] + q_arr[i - 1] * sol[0][max(0, j - 1)]) % mod
            for j in range(n)
        ] + [(q_arr[i - 1] * sol[0][n]) % mod]
        sol[0] = [e for e in sol[1]]  # Update previous state
        result[i - 1] = sol[1][0]     # The expected score for k = i

    print(*result)


# https://github.com/VaHiX/CodeForces/