# Problem: CF 1987 B - K-Sort
# https://codeforces.com/contest/1987/problem/B

"""
Algorithm: Greedy with Prefix Tracking
Purpose: Minimize the number of coins to make array non-decreasing by incrementing k elements at a cost of k+1 coins.
Approach:
    - Use a greedy method to track prefix maximum and compute required increments.
    - For each element, calculate how much it needs to be increased to be at least the current prefix maximum.
    - Keep track of total increments (T) and the maximum increment in a single step (M).
    - The final result uses a formula involving total increments and the optimal k value.

Time Complexity: O(n) per test case
Space Complexity: O(1) (only using a few variables)
"""

import sys

input = sys.stdin.readline


def solve():
    t = int(input())
    for _ in range(t):
        n = int(input())
        a = list(map(int, input().split()))
        pref = a[0]  # Prefix maximum so far
        T = 0  # Total increments needed
        M = 0  # Maximum increments in any single step
        for x in a:
            if x > pref:
                pref = x
            inc = pref - x  # How much we need to increase x
            T += inc
            if inc > M:
                M = inc
        # Compute the minimal additional cost based on optimal k choice
        m = max(M, (T + n - 1) // n)
        print(T + m)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/