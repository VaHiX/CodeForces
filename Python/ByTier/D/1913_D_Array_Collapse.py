# Problem: CF 1913 D - Array Collapse
# https://codeforces.com/contest/1913/problem/D

"""
Algorithm: Dynamic Programming with Stack
Techniques: Monotonic Stack, Prefix Sum, DP Transition

Time Complexity: O(n) per test case
Space Complexity: O(n) for stack, dp array, and prefix sum array

This solution uses a monotonic stack to keep track of indices in increasing order.
For each element, we calculate how many ways we can form a subarray ending at that element
by considering all valid previous subarrays. The DP state represents number of ways to
collapse the array up to that point, and we use prefix sums for efficiency.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


MOD = 998_244_353


def solve() -> None:
    n = sint()
    nums = ints()
    pres = [0] * (n + 1)  # prefix sum array for dp values
    dp = [0] * n          # dp[i] stores number of ways to reach state ending at i
    stk = []              # monotonic stack storing indices
    s = 0                 # running sum of dp values, used to track valid transitions
    
    for i, x in enumerate(nums):
        # Maintain monotonic stack (decreasing order by value)
        while stk and nums[stk[-1]] > x:
            s -= dp[stk.pop()]  # Remove contribution of smaller elements from running sum
        
        # Determine the leftmost index for valid subarray ending at i
        j = 0 if not stk else stk[-1] + 1
        
        # Calculate dp[i]: number of ways to collapse subarray ending at i
        dp[i] = (s + pres[i] - pres[j] + int(not stk)) % MOD

        # Update prefix sum
        pres[i + 1] = (pres[i] + dp[i]) % MOD

        # Update running sum
        s = (s + dp[i]) % MOD
        stk.append(i)  # Push current index to stack
    
    print(s)  # Total number of reachable arrays


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/