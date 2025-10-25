# Problem: CF 1957 C - How Does the Rook Move?
# https://codeforces.com/contest/1957/problem/C

"""
Purpose: 
This code solves the problem of counting the number of different final configurations 
possible in a game where white and black rooks are placed on an n×n chessboard. 
The game alternates between the player (who places white rooks) and the computer 
(who places black rooks). When a player places a rook at (r, c), the computer mirrors 
it to (c, r), unless r == c, in which case the computer skips its turn. 
The goal is to count how many distinct final configurations are possible after 
k moves by the player (with the computer mirroring them), assuming optimal play.

The solution involves:
- Tracking the number of unused rows and columns after k moves.
- Using dynamic programming to compute the number of valid configurations 
  that can be made in the remaining squares, based on a recurrence relation.

Key Algorithm/Techniques:
- Dynamic Programming with the recurrence:
    dp[i] = dp[i - 1] + 2 * (i - 1) * dp[i - 2], where dp[i] represents the number
    of configurations for i unused rows/columns.
- Efficient precomputation of dp values for all relevant inputs to handle multiple test cases.

Time Complexity: O(n) - since we precompute dp values up to max n in the input.
Space Complexity: O(n) - to store the dp array of size up to 3 * 10^5.

"""

MOD = 10**9 + 7


def compute_dp(m):
    # Precompute dp array for configurations with m unused rows/columns
    if m < 0:
        return [0]
    dp = [0] * (m + 1)
    if m >= 0:
        dp[0] = 1  # Base case: 0 unused rows/columns => 1 way (empty)
    if m >= 1:
        dp[1] = 1  # Base case: 1 unused row/column => 1 way
    for i in range(2, m + 1):
        # dp[i] = dp[i - 1] + 2 * (i - 1) * dp[i - 2]
        # We can either place 1 rook in the new row/column (dp[i - 1])
        # or place 2 rooks (one in new, one in prev) in 2 * (i - 1) ways
        dp[i] = (dp[i - 1] + 2 * (i - 1) * dp[i - 2]) % MOD
    return dp


def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    index = 0
    t = int(data[index])
    index += 1
    results = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2
        used = 0  # Count of rows/columns already used (with both rooks if mirrored)
        for _ in range(k):
            r = int(data[index])
            c = int(data[index + 1])
            index += 2
            # Add 2 if r != c (both rooks placed), 1 otherwise (only player's rook)
            used += 2 - (r == c)
        m = n - used  # Number of remaining rows/columns (used by player only)
        if m < 0:
            results.append(0)
        else:
            dp = compute_dp(m)
            results.append(dp[m])
    print("\n".join(map(str, results)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/