# Problem: CF 1832 E - Combinatorics Problem
# https://codeforces.com/contest/1832/problem/E

"""
Combinatorics Problem

This problem involves computing a transformed array b where each element is a weighted sum of previous elements using binomial coefficients.
The key insight is using dynamic programming with prefix sums and modular arithmetic to efficiently compute the result.

Algorithms/Techniques:
- Modular arithmetic
- Dynamic programming with sliding window
- Prefix sum optimization
- Bitwise XOR operation

Time Complexity: O(n * k)
Space Complexity: O(k)

The algorithm uses a rolling DP array of size k to store intermediate values and computes binomial coefficients on-the-fly using a sliding window approach.
"""

n, a, x, y, m, k = map(int, input().split())
mod = 998244353
dp = [0] * k
pref = 0
res = 0
for idx in range(n):
    # Shift elements in dp array to simulate binomial coefficient update
    for i in range(k - 1, 0, -1):
        dp[i] += dp[i - 1]
    # Add current a value to prefix sum
    pref += a
    pref %= mod
    # Add prefix sum to first element of dp (which represents binomial coefficient)
    dp[0] += pref
    # Apply modulo to all elements of dp
    for i in range(k):
        dp[i] %= mod
    # Compute XOR of result with c_i = b_i * i
    res ^= dp[-1] * (idx + 1)
    # Generate next a_i according to given recurrence relation
    a = (a * x + y) % m
print(res)


# https://github.com/VaHiX/CodeForces/