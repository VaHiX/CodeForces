# Problem: CF 933 A - A Twisty Movement
# https://codeforces.com/contest/933/problem/A

"""
Algorithm: Dynamic Programming
Techniques: Sliding window with state tracking

Time Complexity: O(n)
Space Complexity: O(1)

This solution uses a dynamic programming approach to find the maximum length of a non-decreasing subsequence
after potentially reversing one contiguous subarray. The key insight is that since all elements are either 1 or 2,
we can track the maximum length of subsequence ending at each state (1, 2, 3, 4) where:
- dp[1]: max length of subsequence ending with 1
- dp[2]: max length of subsequence ending with 1 or 2
- dp[3]: max length of subsequence ending with 2
- dp[4]: max length of subsequence ending with 2

For each element in the array, we update these states accordingly:
- If element is 1, we update state transitions to extend subsequences ending with 1 or 2
- If element is 2, we update state transitions to extend subsequences ending with 2 or 3
"""

def solve() -> None:
    int(input())
    arr = list(map(int, input().split()))
    dp = [0] * 5
    for x in arr:
        if x == 1:
            dp[1] += 1
            dp[2] = max(dp[1], dp[2])
            dp[3] = max(dp[2], dp[3] + 1)
            dp[4] = max(dp[3], dp[4])
        else:
            dp[2] = max(dp[1], dp[2] + 1)
            dp[3] = max(dp[2], dp[3])
            dp[4] = max(dp[3], dp[4] + 1)
    print(dp[4])


solve()


# https://github.com/VaHiX/CodeForces/