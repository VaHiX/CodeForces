# Problem: CF 1783 D - Different Arrays
# https://codeforces.com/contest/1783/problem/D

"""
Purpose: 
    This code calculates the number of reachable arrays after performing a sequence of operations 
    on an input array. Each operation involves transferring a value from one element to its neighbor.
    The problem is modeled using dynamic programming where we track how many ways we can reach 
    a specific difference between adjacent elements.

Algorithms/Techniques:
    - Dynamic Programming (DP)
    - Difference tracking between adjacent elements in the array
    - Modular arithmetic for large results

Time Complexity: O(n * M) where M is the maximum possible difference (around 90000)
Space Complexity: O(M) where M is the range of possible differences

The key idea:
    Instead of tracking complete arrays, we track the differences between adjacent elements.
    For each step, we update the DP state by considering adding/subtracting the value to neighbors.
    The answer is the sum of all possible DP states at the end.

"""

mod = 998244353

n = int(input())
a = list(map(int, input().split()))
# dp[j] stores the number of ways to achieve a certain difference j
# Since values can be up to 300 and we have up to 300 elements,
# the total difference range is bounded, so we use a large enough array
dp = [0] * 2 * 10**5
# Initialize base case: the difference between a[1] and a[0] is a[1]
dp[a[1]] = 1

for i in range(2, n):
    # New DP array for current step
    ndp = [0] * 2 * 10**5
    # Iterate through all possible differences in current DP state
    for j in range(-90010, 90010):
        # Add a[i] to the difference (i.e., decrease the difference by a[i])
        ndp[j + a[i]] += dp[j]
        # Subtract a[i] from the difference (i.e., increase the difference by a[i])
        if j != 0:
            ndp[j - a[i]] += dp[j]
    # Update dp for next iteration
    dp = [j % mod for j in ndp]

# Sum all possible final differences to get the total count of reachable arrays
print(sum(dp) % mod)


# https://github.com/VaHiX/CodeForces/