# Problem: CF 1809 G - Prediction
# https://codeforces.com/contest/1809/problem/G

"""
Purpose: This code solves the problem of counting the number of ways to assign indices to participants in a tournament such that all game results are predictable based on their ratings and a given threshold k.

Algorithms/Techniques:
- Dynamic Programming with prefix/suffix handling
- Modular arithmetic with precomputed factorials and inverse factorials
- Two-pointer technique for efficiently managing ranges

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm uses a dynamic programming approach where it tracks valid assignments using prefix and suffix counts.
It maintains a sliding window over the sorted array of ratings and checks for valid transitions between players.
"""

MOD = 998244353


def modmul(x, y, c=0):
    # Modular multiplication helper function
    return (x * y + c) % MOD


def inv(x):
    # Modular inverse using Fermat's little theorem
    return pow(x, MOD - 2, MOD)


MAX = 10**6 + 10
# Precompute factorials and inverse factorials for modular arithmetic
fact = [1]
for i in range(1, MAX):
    fact.append(modmul(i, fact[i - 1]))
invfact = [1] * (MAX)
invfact[MAX - 1] = inv(fact[MAX - 1])
for i in range(MAX - 2, -1, -1):
    invfact[i] = modmul(i + 1, invfact[i + 1])

n, k = map(int, input().split())
l = list(map(int, input().split()))[::-1]  # Reverse the list for easier processing
dp = [1]
left = 0
right = 1
# If the first two elements can't be distinguished by the threshold, no valid assignment exists
if l[0] <= l[1] + k:
    print(0)
    quit()
pointer = 0
for i in range(1, n):
    # Adjust the sliding window based on rating difference
    while l[pointer] > l[i] + k:
        base = dp[pointer]
        diff = modmul(invfact[pointer - 1], fact[i - 2])
        ch = modmul(diff, base)
        right -= ch
        left += ch
        pointer += 1
    left %= MOD
    right %= MOD
    dp.append(left)
    left = modmul(left, i)
    right = modmul(right, i - 1)
    right += dp[i]
print((left + right) % MOD)


# https://github.com/VaHiX/CodeForces/