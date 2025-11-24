# Problem: CF 1726 E - Almost Perfect
# https://codeforces.com/contest/1726/problem/E

"""
Almost Perfect Permutation Counting

This code computes the number of "almost perfect" permutations of length n.
A permutation p is almost perfect if for every index i, |p[i] - p^{-1}[i]| <= 1,
where p^{-1} is the inverse permutation.

The solution uses dynamic programming with memoization and generates the counts
using a recurrence relation. The recurrence relation is derived from the structure
of valid permutations where elements can only be at most 1 position away from
their original index.

Time Complexity: O(n) preprocessing + O(n) per query
Space Complexity: O(n) for precomputed values

Algorithms/Techniques:
- Dynamic Programming with recurrence relation
- Modular arithmetic using inverse modulo
- Precomputation of factorials and DP values
"""

m = 998244353
f = [1] * (300001)  # f[i] stores the number of almost perfect permutations of length i
fac = [1] * (300001)  # fac[i] stores i! mod m
fac[2] = 2
f[1] = 1
f[2] = 2
# Precompute f[i] using recurrence relation f[i] = f[i-1] + (i-1)*f[i-2]
for i in range(3, 300001):
    f[i] = (f[i - 1] + (i - 1) * f[i - 2]) % m
    fac[i] = (i * fac[i - 1]) % m


def calc(n):
    ans = 0
    k = 0
    # Iterate over all possible valid combinations of positions
    while 4 * k <= n:
        # Calculate contribution of current combination
        # Combine factorial terms with modular inverse
        ans += (fac[n - 2 * k] * pow(fac[n - 4 * k] * fac[k], -1, m) * f[n - 4 * k]) % m
        k += 1
    return ans % m


for _ in range(int(input())):
    n = int(input())
    print(calc(n))


# https://github.com/VaHiX/CodeForces/