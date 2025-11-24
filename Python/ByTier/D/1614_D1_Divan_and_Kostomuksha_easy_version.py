# Problem: CF 1614 D1 - Divan and Kostomuksha (easy version)
# https://codeforces.com/contest/1614/problem/D1

"""
Algorithm: Dynamic Programming with GCD properties
Technique: 
- Use a frequency count array to determine how many multiples exist for each number
- Apply dynamic programming from larger numbers down to smaller ones
- For each number i, compute the maximum contribution of subarrays ending at i
- Use inclusion-exclusion principle to count how many elements are divisible by i

Time Complexity: O(M log M) where M is the maximum element in the array
Space Complexity: O(M) for the frequency and DP arrays

This solution leverages the fact that for a prefix of the array, we want to maximize 
the sum of GCDs of all prefixes. By processing from largest to smallest elements, 
we can determine optimal choices efficiently.
"""

n = int(input())
arr = list(map(int, input().split()))
mx = max(arr)
cnt = [0] * (mx + 1)
dp = [0] * (mx + 1)

# Count frequency of each number
for i in arr:
    cnt[i] += 1

# For each number, count how many multiples exist
# This will help determine the contribution of a certain GCD value
for i in range(1, mx):
    for j in range(2 * i, mx + 1, i):
        cnt[i] += cnt[j]

ans = 0
# Process from largest to smallest
for i in range(mx, 0, -1):
    # dp[i] represents the best sum obtainable if we start with i as the first element
    dp[i] = cnt[i] * i
    # Try all multiples of i (i.e., higher values that are multiples of i)
    for j in range(i * 2, mx + 1, i):
        dp[i] = max(dp[i], dp[j] + (cnt[i] - cnt[j]) * i)
    # Update the final answer by considering the contribution of the entire sequence
    ans = max(ans, dp[i] + n - cnt[i])

print(ans)


# https://github.com/VaHiX/CodeForces/