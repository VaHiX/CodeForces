# Problem: CF 1919 E - Counting Prefixes
# https://codeforces.com/contest/1919/problem/E

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n^3), where n is the size of the array
Space Complexity: O(n^3), for the dp table and auxiliary arrays

This problem involves reconstructing an array of 1s and -1s from its sorted prefix sums.
The key idea is that each element in the original array affects the prefix sum, and we must count how many valid 
arrays can produce the given sorted prefix sum.

Approach:
1. Precompute factorials and reverse factorials for combinations.
2. For each test case:
   - Check for invalid prefix sums (gaps > 1 or both positive and negative).
   - Count occurrences of each prefix sum value.
   - Use dynamic programming to count valid arrangements, tracking how many 1s and -1s 
     can be placed at each prefix sum level.
   - Return the total number of valid combinations modulo 998244353.

Note: The algorithm tracks valid configurations of 1s and -1s in the prefix sum space.
"""

mod = 998244353
fact = [1] * 5005
rfact = [1] * 5005
for i in range(1, 5005):
    fact[i] = fact[i - 1] * i % mod
    rfact[i] = pow(fact[i], mod - 2, mod)


def C(n, r):
    # Computes combination C(n, r) modulo 998244353
    if n < r or r < 0:
        return 0
    return fact[n] * rfact[r] * rfact[n - r] % mod


t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split())) + [0]  # Add a 0 to handle boundary cases
    arr.sort()
    m, M = arr[0], arr[-1]  # Minimum and maximum prefix sums
    flag = 0
    for i in range(n - 1):
        # If there is a gap > 1 in sorted prefix sums, impossible to form valid array
        if arr[i + 1] - arr[i] > 1:
            flag = 1
            break
    if flag == 1 or m * M > 0:
        # If there's a gap or all values are same sign, no valid array exists
        print(0)
    else:
        # Count occurrences of each prefix sum
        cnt = [0] * 10005
        for i in arr:
            cnt[i] += 1
        
        # dp[i][j][0/1] = number of ways to reach prefix sum i with j 1s, 0 for ending with -1, 1 for ending with 1
        dp = [[[0, 0] for _ in range(cnt[i + m] + 1)] for i in range(M - m + 1)]
        # Initialize base case: with the starting prefix sum of 0, we can have cnt[m] 1s or -1s with one -1
        dp[0][cnt[m] - 1][0] = 1
        for i in range(1, M - m + 1):
            p = i + m  # Current prefix sum value
            for j in range(cnt[p] + 1):
                for j2 in range(cnt[p - 1] + 1):
                    if p <= 0:
                        # For current prefix sum <= 0, compute transitions accordingly
                        hole = cnt[p] - j
                        if hole == j2 + 2:
                            # Special transition for 1s
                            dp[i][j][0] = (
                                dp[i][j][0] + dp[i - 1][j2][0] * C(cnt[p] - 1, hole - 1)
                            ) % mod
                        if hole == j2 + 1:
                            # Transition to 1s or -1s with 1
                            dp[i][j][1] = (
                                dp[i][j][1]
                                + dp[i - 1][j2][0] * C(cnt[p] - 1, hole - 1)
                                + dp[i - 1][j2][1] * C(cnt[p] - 1, hole - 1)
                            ) % mod
                    else:
                        # For prefix sum > 0
                        hole = cnt[p] - j
                        if hole == j2 + 1:
                            # Transition to 1s or -1s with 1
                            dp[i][j][0] = (
                                dp[i][j][0] + dp[i - 1][j2][0] * C(cnt[p] - 1, hole - 1)
                            ) % mod
                        if hole == j2:
                            # Special transition for 1s
                            dp[i][j][1] = (
                                dp[i][j][1]
                                + dp[i - 1][j2][0] * C(cnt[p] - 1, hole - 1)
                                + dp[i - 1][j2][1] * C(cnt[p] - 1, hole - 1)
                            ) % mod
        # Sum up final results
        ans = sum(dp[-1][0]) % mod
        print(ans)


# https://github.com/VaHiX/CodeForces/