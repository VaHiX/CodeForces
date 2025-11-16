# Problem: CF 1768 E - Partial Sorting
# https://codeforces.com/contest/1768/problem/E

"""
Code Purpose:
This program computes the sum of minimum operations required to sort all permutations of length 3n,
where each operation sorts either the first 2n or the last 2n elements.
It uses combinatorics and inclusion-exclusion principle to calculate contributions
of different cases (0, 1, 2, 3 operations) efficiently.

Algorithms/Techniques:
- Preprocessing factorials and inverse factorials for combinatorial calculations
- Combinatorial inclusion-exclusion to count permutations requiring specific number of operations
- Modular arithmetic for large number handling

Time Complexity: O(n)
Space Complexity: O(n)
"""

n, m = map(int, input().split())

N = 3 * n + 1
fact = [1] * N
ifact = [1] * N
for i in range(1, N):
    fact[i] = i * fact[i - 1] % m

ifact[N - 1] = pow(fact[N - 1], m - 2, m)
for i in range(N - 1, 0, -1):
    ifact[i - 1] = i * ifact[i] % m


def nCr(n, r):
    return fact[n] * ifact[r] % m * ifact[n - r] % m


ans = [1] * 4


ans[1] = (fact[2 * n] * 2 - fact[n]) % m


ans[2] = 2 * nCr(2 * n, n) * fact[2 * n] % m * fact[n] % m
for i in range(n + 1):
    ans[2] = (
        ans[2]
        - (
            nCr(n, i)
            * nCr(n, n - i)
            % m
            * nCr(2 * n - i, n)
            % m
            * fact[n]
            % m
            * fact[n]
            % m
            * fact[n]
            % m
        )
        + 2 * m
    ) % m


ans[3] = fact[3 * n]

res = 0
for i in range(1, 4):
    res = (res + i * (ans[i] - ans[i - 1])) % m
print(res)


# https://github.com/VaHiX/CodeForces/