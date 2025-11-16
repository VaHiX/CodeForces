# Problem: CF 1684 D - Traps
# https://codeforces.com/contest/1684/problem/D

"""
D. Traps
Algorithm: Greedy with sorting and prefix sum optimization
Time Complexity: O(n log n) per test case due to sorting step
Space Complexity: O(n) for storing trap damages and auxiliary arrays

The problem involves choosing at most k traps to skip such that the total damage is minimized.
When a trap is skipped, all subsequent traps get +1 bonus damage.
This is solved by:
1. For each possible number of jumps (0 to k), compute the minimum damage
2. To optimize, we can sort the damages and greedily choose which traps to skip
3. The key insight is that skipping a trap at position i adds bonus damage to all traps after it
4. We calculate a cost for each trap to be skipped: it's the sum of bonus damages (i+1, i+2, ..., n-1) = (n-i-1)*(n-i)/2
5. We then greedily select the k cheapest skips from all possible skips.

The code uses:
- Sorting to order traps by their base damage values
- Prefix sums to calculate cumulative bonus damage efficiently
"""

for _ in range(int(input())):
    print(
        [
            # Calculate the minimum damage for a given number of jumps (k)
            sum(sorted([u[1][i] + i for i in range(u[0][0])])[: u[0][0] - u[0][1]])
            - ((u[0][0] - u[0][1]) * ((u[0][0] - u[0][1]) - 1)) // 2
            for u in [
                [list(map(int, input().split())), list(map(int, input().split()))]
            ]
        ][0]
    )


# https://github.com/VaHiX/codeForces/