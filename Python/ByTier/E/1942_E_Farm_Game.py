# Problem: CF 1942 E - Farm Game
# https://codeforces.com/contest/1942/problem/E

"""
Code Purpose:
This code solves the problem of counting the number of game configurations where Farmer John (FJ) wins in a game played on a number line with walls at points 0 and l+1. The game involves placing n cows for each farmer (FJ and FN) such that no two cows from the same farmer are adjacent. The game proceeds by moving cows toward the walls or in the direction of the other farmer's cows. FJ goes first and the task is to count all valid initial configurations where FJ wins if both players play optimally.

The solution uses combinatorics to calculate valid arrangements and applies inclusion-exclusion principles to determine the winning configurations.

Algorithms/Techniques:
1. Preprocessing factorials and inverse factorials for efficient computation of combinations.
2. Iteration over possible even spacing between cows to compute valid arrangements.
3. Combinatorial mathematics for counting valid cow placements.
4. Modular arithmetic for calculations under modulo 998244353.

Time Complexity: O(MAX + t * l) where MAX = 2 * 10^6 + 5
Space Complexity: O(MAX) for storing precomputed factorials and inverse factorials.
"""

MOD = 998244353
MAX = 2 * 10**6 + 5

# Precompute factorials and inverse factorials
fact = [1] * MAX
ifact = [1] * MAX

for i in range(1, MAX):
    fact[i] = fact[i - 1] * i % MOD

ifact[MAX - 1] = pow(fact[MAX - 1], MOD - 2, MOD)
for i in range(MAX - 2, -1, -1):
    ifact[i] = ifact[i + 1] * (i + 1) % MOD


def ncr(n, r):
    # Computes combination C(n, r) modulo MOD
    if n < 0 or r > n:
        return 0
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD


def solve():
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    for _ in range(t):
        l = int(data[idx])
        n = int(data[idx + 1])
        idx += 2
        all_even = 0
        # Iterate through all even positions from 0 to l (inclusive)
        for s in range(0, l + 1, 2):
            # Calculate terms for inclusion-exclusion principle
            term1 = ncr(s // 2 + n - 1, n - 1)   # Ways to arrange FJ cows in valid positions
            term2 = ncr(l - s - n, n)            # Ways to arrange FN cows in remaining positions
            all_even = (all_even + 2 * term1 % MOD * term2 % MOD) % MOD
        # Total ways to arrange 2n cows in l positions (with proper constraints)
        total = 2 * ncr(l, 2 * n) % MOD
        # Compute result using inclusion-exclusion: Total - Invalid arrangements
        result = (total - all_even + MOD) % MOD
        print(result)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/