# Problem: CF 2018 F1 - Speedbreaker Counting (Easy Version)
# https://codeforces.com/contest/2018/problem/F1

"""
Problem: Counting arrays of positive integers a_1, ..., a_n such that 1 <= a_i <= n,
and for each k, count the number of such arrays where exactly k starting cities
allow you to win, i.e., conquer city i at time no later than a_i.

Algorithms/Techniques:
- Dynamic Programming with inclusion-exclusion principle
- Modular arithmetic using modular exponentiation and inverse elements
- Preprocessing with recurrence relations

Time Complexity: O(n^3) per test case
Space Complexity: O(n^2) for the DP arrays

This solution uses a complex recurrence and multiple iterations over f to compute
the counts of valid arrays for different values of k.
"""

for t in range(int(input())):
    n, p = map(int, input().split())
    f = [0 for i in range(n + 3)]
    f[0] = pow(n, n, p)  # Compute n^n mod p
    f[n] = 1              # Base case for recurrence
    
    # Build the recurrence from back to front
    for l in range(1, n)[::-1]:
        f[l] = (f[l + 1] * (n - l) * 2 - f[l + 2] * (n - l - 1) * (n - l - 1)) % p
    
    # Multiply by terms related to the constraint a_i <= n and time ordering
    for i in range(1, n + 1):
        for j in range(i):
            f[i] = f[i] * (n + 1 - max(j + 1, i - j)) % p
    
    # Update using another recurrence relation
    for i in range(1, n + 1):
        f[i] = (f[i] - 2 * f[i + 1] + f[i + 2]) % p
        f[0] = (f[0] - f[i]) % p
    
    print(*f[: n + 1])


# https://github.com/VaHiX/codeForces/