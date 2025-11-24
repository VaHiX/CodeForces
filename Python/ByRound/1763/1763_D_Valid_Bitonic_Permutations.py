# Problem: CF 1763 D - Valid Bitonic Permutations
# https://codeforces.com/contest/1763/problem/D

"""
Bitonic Permutation Counting with Constraints

This code counts the number of bitonic permutations of numbers 1 to n,
such that the i-th element is x and the j-th element is y.

Approach:
- Use dynamic programming with memoization.
- The state is defined by the range [l, r] of remaining elements to place
  and the current value being placed.
- For each recursive call, decide whether to place the current value at
  the left end or right end of the remaining range.
- A bitonic permutation means elements increase to a peak and then decrease.
- Use the constraint that positions i and j must have values x and y respectively.

Time Complexity: O(n^2)
Space Complexity: O(n^2)

The recursion explores placing the elements in a way that respects the bitonic
property, and the DP table caches results of subproblems.
"""

from sys import stdin

input = stdin.buffer.readline

MOD = 1_000_000_007


def main():

    def can(pos, val):
        # Check if the current value can be placed at the given position
        if pos == i:
            return val == x
        elif pos == j:
            return val == y
        return True

    def dfs(l, r, now):
        # Base case: if there is only one element left to place
        if dp[l][r] != -1:
            return dp[l][r]
        ans = 0
        if l == r:
            # Only valid if the element is not at the first or last position
            # and satisfies the constraint at position l
            ans = int(l != n and l != 1 and can(l, now))
        else:
            # Try placing the current value at the left or right end
            ans += int(can(l, now)) * dfs(l + 1, r, now + 1)
            ans += int(can(r, now)) * dfs(l, r - 1, now + 1)
        dp[l][r] = ans % MOD
        return dp[l][r]

    for _ in range(int(input())):
        n, i, j, x, y = map(int, input().split())
        dp = [[-1] * (n + 1) for _ in range(n + 1)]
        print(dfs(1, n, 1))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/