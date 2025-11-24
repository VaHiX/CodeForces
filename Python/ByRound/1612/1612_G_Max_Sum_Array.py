# Problem: CF 1612 G - Max Sum Array
# https://codeforces.com/contest/1612/problem/G

"""
Algorithm: Max Sum Array
Techniques: Dynamic Programming, Combinatorics, Modular Arithmetic

Time Complexity: O(max(c) * log(max(c)) + sum(c))
Space Complexity: O(max(c))

This solution computes the maximum value of f(a) and the count of arrays achieving it.
It uses dynamic programming to calculate how many times each count of elements appears,
and then computes the total contribution using a formula for sum of distances.
The number of valid permutations is calculated using factorials modulo 10^9 + 7.
"""

MD = 10**9 + 7
m = int(input())
c = list(map(int, input().split()))


mc = max(c)
dp = [0] * (2 * mc + 2)
for cnt in c:
    dp[cnt - 1] += 1

# Propagate counts backwards to accumulate occurrences
for i in range(mc - 3, -mc, -1):
    dp[i] = (dp[i] + dp[i + 2]) % MD if i >= 0 else dp[-i]

# Precompute factorials up to the maximum count
fact = [1] * (max(dp) + 1)
for i in range(1, len(fact)):
    fact[i] = (fact[i - 1] * i) % MD

ans, num, p = 0, 1, sum(c)
# Iterate through possible counts in reverse to compute maximum f(a)
for i in range(mc - 1, -mc, -1):
    # Compute contribution of current count to total sum of distances
    ans = (ans + i * (p + p - dp[i] + 1) * dp[i] // 2) % MD
    # Multiply number of permutations by factorial of count
    num = (num * fact[dp[i]]) % MD
    # Update remaining count of elements
    p -= dp[i]

print(ans, num)


# https://github.com/VaHiX/CodeForces/