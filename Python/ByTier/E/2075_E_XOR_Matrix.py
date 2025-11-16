# Problem: CF 2075 E - XOR Matrix
# https://codeforces.com/contest/2075/problem/E

"""
Problem: XOR Matrix
Algorithm: Mathematical Combinatorics + Bit Manipulation
Time Complexity: O(1) per test case (30 iterations for bit processing)
Space Complexity: O(1)

We are counting the number of pairs of arrays (a, b) such that their XOR matrix contains at most two distinct values.
The solution uses inclusion-exclusion principle and bit manipulation techniques to count valid combinations efficiently.

Approach:
1. Count all possible pairs of arrays (a, b) where a[i] ∈ [0, A], b[j] ∈ [0, B].
2. Subtract cases where XOR matrix has more than two distinct values.
3. Use bit-level analysis to determine when the XOR values are limited to 2 or fewer.
4. Apply modular arithmetic for large numbers.
"""

M = 998244353
for _ in range(int(input())):
    n, m, a, b = map(int, input().split())
    a += 1
    b += 1
    # x = number of ways to select a1, a2 such that a1^x = a2^x (i.e., same value)
    x = (pow(2, n, M) - 2 + M) % M
    # y = number of ways to select b1, b2 such that b1^x = b2^x (i.e., same value)
    y = (pow(2, m, M) - 2 + M) % M
    # z = contribution from cases involving 2 or more distinct values
    z = (
        a * b
        + a * (a - 1) // 2 % M * b % M * x % M
        + b * (b - 1) // 2 % M * a % M * y % M
    ) % M
    # Combine x and y for further computation
    x = x * y % M
    y = 0
    j = 0
    # Iterate through all possible bits to compute valid configurations
    for i in range(30):
        # Calculate how many pairs satisfy certain constraints on bit levels
        p1 = ((a >> (i + 1)) << i) + ((a & j) if (a >> i) & 1 else 0)
        p2 = ((b >> (i + 1)) << i) + ((b & j) if (b >> i) & 1 else 0)
        y = (y + p1 * p2 % M * (1 << i)) % M
        j = (j << 1) | 1
    # Final result includes both base combinations and bit-level constraints
    print((x * y + z) % M)


# https://github.com/VaHiX/CodeForces/