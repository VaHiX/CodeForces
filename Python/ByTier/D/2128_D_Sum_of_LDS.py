# Problem: CF 2128 D - Sum of LDS
# https://codeforces.com/contest/2128/problem/D

"""
D. Sum of LDS

Purpose:
This code computes the sum of the length of the longest decreasing subsequence (LDS)
for all possible contiguous subarrays of a given permutation.

Algorithm:
- Uses dynamic programming with reverse iteration to calculate for each position i,
  how much contribution it has towards the total sum based on the structure of the
  permutation and properties of LDS.
- The recurrence relation considers whether the current element is greater than
  the next one, affecting how the LDS length propagates.

Time Complexity:
O(n) per test case due to single pass through array with O(1) operations in loop.

Space Complexity:
O(n) for the dp array used to store intermediate results.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    p = list(map(int, input().split()))
    dp = [0] * (n + 1)
    dp[n - 1] = 1  # Base case: last element contributes 1 to LDS
    for i in range(n - 2, -1, -1):  # Iterate backwards from second-to-last
        if p[i] > p[i + 1]:  # If current is greater than next
            dp[i] = dp[i + 1] + n - i  # Add contribution of current element to LDS
        else:  # If not greater, we look ahead two positions (due to constraint)
            dp[i] = dp[i + 2] + n - i  # Propagate from next next element
    print(sum(dp))


# https://github.com/VaHiX/codeForces/