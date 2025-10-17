# Problem: CF 2018 F2 - Speedbreaker Counting (Medium Version)
# https://codeforces.com/contest/2018/problem/F2

"""
F2. Speedbreaker Counting (Medium Version)

This problem computes the number of arrays a[1..n] such that each element is between 1 and n,
and for each k from 0 to n, we count how many such arrays result in exactly k valid starting cities
when solving the city conquest game.

Algorithms/Techniques:
    - Dynamic Programming with combinatorial math
    - Modular arithmetic for large numbers
    - Recurrence relations using prefix and suffix computations

Time Complexity: O(n^3)
Space Complexity: O(n^2)

The solution involves computing recurrence relations to count valid configurations of conquest times,
and uses modular exponentiation and multiplicative inverse for efficient computation.
"""
for t in range(int(input())):
    n, p = map(int, input().split())
    f = [0 for i in range(n + 3)]
    f[0] = pow(n, n, p)  # Base case: all possible sequences
    f[n] = 1             # Terminal condition
    for l in range(1, n)[::-1]:     # Iterate backwards to build recurrence
        f[l] = (f[l + 1] * (n - l) * 2 - f[l + 2] * (n - l - 1) * (n - l - 1)) % p
    for i in range(1, n + 1):       # Multiply by combinatorial factors
        for j in range(i):
            f[i] = f[i] * (n + 1 - max(j + 1, i - j)) % p
    for i in range(1, n + 1):       # Final corrections using recurrence
        f[i] = (f[i] - 2 * f[i + 1] + f[i + 2]) % p
        f[0] = (f[0] - f[i]) % p
    print(*f[: n + 1])


# https://github.com/VaHiX/codeForces/