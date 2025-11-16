# Problem: CF 1736 E - Swap and Take
# https://codeforces.com/contest/1736/problem/E

"""
Algorithm: Dynamic Programming with optimized state transitions
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This problem uses dynamic programming to track the maximum score achievable
at each step. The key insight is to consider what happens when we can swap 
adjacent elements and set one to zero. We maintain states based on position 
and number of swaps used to compute optimal choices.

The DP state is defined as dp[i][j][k] where:
- i represents the current turn (0-indexed)
- j represents the current index in the array
- k represents the number of moves (swaps) used so far

However, the implementation is slightly optimized to reduce memory usage 
by only keeping track of current and previous states.
"""

def II():
    return int(input())
def LII():
    return list(map(int, input().split()))

def main():
    n = II()
    nums = LII()

    # dp and dp_prev_max are 2D arrays to store the maximum values
    # dp[i][j] represents maximum score up to position j with i moves
    dp = [[-1] * (n * (n + 1)) for _ in range(2)]
    dp_prev_max = [[-1] * (n * (n + 1)) for _ in range(2)]

    # Helper function to map 2D indices to 1D
    def f(x, y):
        return x * (n + 1) + y

    # Initialize first state
    for i in range(2):
        dp[0][f(i, 1 - i)] = nums[i]
        for j in range(i, n):
            dp_prev_max[0][f(j, 1 - i)] = nums[i]

    cur = 0

    # Process each turn
    for i in range(1, n):
        cur = i & 1
        last = cur ^ 1

        # Iterate over possible indices and move counts
        for j in range(min(n, 2 * i + 4)):
            for k in range(i + 2):
                # Check if transition is valid
                if j >= i and k - 1 + j - i <= i and dp_prev_max[last][f(j - 1, k - 1 + j - i)] > dp[last][f(j, k)]:
                    dp[cur][f(j, k)] = dp_prev_max[last][f(j - 1, k - 1 + j - i)]
                else:
                    dp[cur][f(j, k)] = dp[last][f(j, k)]
                
                # Add current element value if valid
                if dp[cur][f(j, k)] != -1:
                    dp[cur][f(j, k)] += nums[j]
                
                # Update maximum value seen so far
                if j and dp_prev_max[cur][f(j - 1, k)] > dp[cur][f(j, k)]:
                    dp_prev_max[cur][f(j, k)] = dp_prev_max[cur][f(j - 1, k)]
                else:
                    dp_prev_max[cur][f(j, k)] = dp[cur][f(j, k)]

    # Output the maximum score possible
    print(max(dp[cur]))
    return


t = 1
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/