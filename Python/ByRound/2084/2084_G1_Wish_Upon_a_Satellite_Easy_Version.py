# Problem: CF 2084 G1 - Wish Upon a Satellite (Easy Version)
# https://codeforces.com/contest/2084/problem/G1

"""
Problem: G1. Wish Upon a Satellite (Easy Version)

This problem involves maximizing the "beauty" of a permutation where:
- Beauty is defined as sum of f(c) over all subsegments c of the permutation.
- f(c) represents the final value of the first element after an optimal game between Turtle and Piggy.
- Turtle tries to maximize f(c), Piggy tries to minimize it.
- Some elements in input are missing (represented by 0) and must be filled.

Algorithm:
This solution uses dynamic programming with state tracking. For each position and number of "Turtle" moves,
we compute the maximum possible contribution to the total beauty.

Time Complexity: O(n^3)
Space Complexity: O(n^2)

The key idea is to simulate the process of computing f(c) via optimal play and count all subsegments
to accumulate the beauty value.
"""

INF = int(1e18)


def chmax(a, b):
    return max(a, b)


def solve():
    n = int(input())
    f = [-1] * n
    x_values = list(map(int, input().split()))
    for i in range(n):
        # Map 1-indexed to 0-indexed
        x = x_values[i] - 1
        if x >= 0:
            f[x] = i % 2  # Assigns whether this position would be chosen by Turtle (0) or Piggy (1)
    
    n0 = (n + 1) // 2  # Half the size, rounded up for Turtle's turns
    n1 = n // 2        # Half the size, rounded down for Piggy's turns
    
    dp = [-INF] * (n1 + 1)  # DP table: max beauty for b moves (Piggy's turns)
    dp[0] = 0               # Base case: no moves taken yet
    
    for x in range(n):      # Iterate through positions
        # Traverse backwards to avoid recomputation issues
        for b in range(min(x, n1), -1, -1):
            a = x - b       # Number of Turtle moves up to x (sum of both types)
            
            if b < n1 and f[x] != 0:  # If there's room for more moves and not Turtle's pick
                # Update potential state with contribution from current element
                dp[b + 1] = chmax(dp[b + 1], dp[b] + (x + 1) * (n0 - a + b + 1))
            
            if f[x] != 1:      # If it's Piggy's turn or free slot
                # Increment current value with contribution from element
                dp[b] += (x + 1) * (n1 - b + a + 1)
            else:
                # If it's Turtle's move here, invalidating state (no valid assignment)
                dp[b] = -INF
    
    print(dp[n1])  # Return the best cumulative beauty value


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/