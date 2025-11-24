# Problem: CF 1829 H - Don't Blame Me
# https://codeforces.com/contest/1829/problem/H

"""
Algorithm: Dynamic Programming with Bitmasking
Time Complexity: O(n * 64 * 64 + 64 * 64) per test case
Space Complexity: O(64 * 64) for dp arrays and bit_counts

This solution uses dynamic programming to count subsequences whose bitwise AND
has exactly k set bits. It processes each unique number in the input array,
updating the DP state for all possible AND values. For each number, it considers
all possible subsets (using pow_2[count]) and updates the DP accordingly. The final
answer is the sum of dp values that have exactly k set bits.
"""

import sys

input = sys.stdin.readline
bit_counts = [[] for _ in range(7)]
for i in range(64):
    bit_counts[bin(i).count("1")].append(i)

mod = 10**9 + 7
pow_2 = [1]
for _ in range(2 * 10**5):
    pow_2.append(pow_2[-1] * 2 % mod)

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())

    count = [0] * 64
    for num in map(int, input().split()):
        count[num] += 1

    dp = [0] * 64
    dp[-1] = 1  # Base case: one way to have empty subsequence
    for i in range(64):
        if count[i]:
            new_dp = dp[:]
            for v in range(64):
                # Update dp[v & i] by including all subsets of current number
                new_dp[v & i] += dp[v] * (pow_2[count[i]] - 1) % mod
            dp = new_dp
            for i in range(64):
                dp[i] %= mod
    dp[-1] -= 1  # Subtract 1 to exclude empty subsequence

    ans = 0
    for i in bit_counts[k]:
        ans += dp[i]
    print(ans % mod)


# https://github.com/VaHiX/CodeForces/