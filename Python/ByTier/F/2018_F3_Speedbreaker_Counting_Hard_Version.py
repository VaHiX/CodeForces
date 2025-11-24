# Problem: CF 2018 F3 - Speedbreaker Counting (Hard Version)
# https://codeforces.com/contest/2018/problem/F3

"""
F3. Speedbreaker Counting (Hard Version)

This problem involves counting the number of valid arrays `a` of length n such that for each i,
the value a[i] represents the latest time when city i can be conquered in a valid conquest strategy.

The problem uses dynamic programming with inclusion-exclusion principle and combinatorics on trees.
We define f[l] as part of the DP state, representing combinations of valid paths or states related to
conquering cities in order.

Key Algorithmic Techniques:
- Dynamic Programming with memoization and transitions
- Modular arithmetic using Fermat's little theorem for modular inverse (implicit)
- Inclusion-exclusion principle

Time Complexity: O(n^3) per test case due to nested loops
Space Complexity: O(n) for storing the DP array f

"""

for t in range(int(input())):
    n, p = map(int, input().split())
    f = [0 for i in range(n + 3)]
    f[0] = pow(n, n, p)  # Precompute base case using modular exponentiation
    f[n] = 1
    for l in range(1, n)[::-1]:  # Backward iteration through states
        f[l] = (f[l + 1] * (n - l) * 2 - f[l + 2] * (n - l - 1) * (n - l - 1)) % p
    for i in range(1, n + 1):  # Multiply by combinatorial factors
        for j in range(i):
            f[i] = f[i] * (n + 1 - max(j + 1, i - j)) % p
    for i in range(1, n + 1):  # Apply inclusion-exclusion or correction terms
        f[i] = (f[i] - 2 * f[i + 1] + f[i + 2]) % p
        f[0] = (f[0] - f[i]) % p
    print(*f[: n + 1])


# https://github.com/VaHiX/codeForces/