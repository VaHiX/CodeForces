# Problem: CF 1716 D - Chip Move
# https://codeforces.com/contest/1716/problem/D

"""
Purpose: 
    Count the number of ways to reach each point x in [1, n] starting from 0,
    where each move's length must be divisible by k, k+1, k+2, etc. for consecutive moves.
    
Algorithm:
    - Use dynamic programming with modular arithmetic.
    - For each step, maintain a sliding window of possible previous positions.
    - Use a memoization array to track how many ways we can reach each modulo class.
    
Time Complexity: O(n * k)
Space Complexity: O(n)

The approach uses a rolling window technique:
- At each iteration, we compute the number of ways to reach positions up to L + k - 1.
- The memo array tracks how many paths end at each modulo class.
- We update the answer array and memo array iteratively.
"""

mod = 998244353
n, k = map(int, input().split())

L = 0
ans = [0] * (n + 1)
now = [0] * (n + 1)
now[0] = 1
while True:
    memo = [0] * k
    for i in range(L, n + 1):
        # Add the number of ways to reach position i from previous positions
        ans[i] += memo[i % k]
        ans[i] %= mod
        # Update memo and now arrays for next iteration
        memo[i % k], now[i] = (memo[i % k] + now[i]) % mod, memo[i % k]
    L += k
    k += 1
    if L > n:
        break

print(*ans[1:])


# https://github.com/VaHiX/CodeForces/