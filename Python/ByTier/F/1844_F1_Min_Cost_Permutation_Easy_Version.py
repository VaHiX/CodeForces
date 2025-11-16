# Problem: CF 1844 F1 - Min Cost Permutation (Easy Version)
# https://codeforces.com/contest/1844/problem/F1

"""
Algorithm: Min Cost Permutation (Easy Version)
Techniques: Sorting, Greedy, Simulation

Time Complexity: O(n^2) in worst case due to nested loops and popping from list
Space Complexity: O(n) for storing the solution array and input array

Approach:
- If c >= 0, sort the array in ascending order to minimize the cost.
- If c < 0, sort in descending order and attempt to construct a permutation
  that minimizes the sum of absolute differences. The construction is done
  greedily by choosing elements that reduce the cost at each step.

The code uses a greedy approach to build the result array, trying to place
elements in a way that minimizes the total cost function. It performs a
backtracking-style selection in some cases to find the optimal order.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, c = map(int, input().split())
    a = list(map(int, input().split()))
    if c >= 0:
        a.sort()
        print(*a)
    else:
        a.sort(reverse=True)
        if n <= 2:
            print(*a)
            continue
        SOL = [0 for _ in range(n)]
        SOL[0] = a.pop(0)  # Place the first element
        SOL[-1] = a[-1]    # Place the last element
        for i in range(1, n - 2):  # Fill middle positions
            for k in range(len(a) - 2, 0, -1):  # Try from end to start for greedy choice
                # Calculate cost before placing element at position k
                before = (
                    abs(a[k + 1] - a[k] - c)
                    + abs(a[k] - a[k - 1] - c)
                    + abs(a[0] - SOL[i - 1] - c)
                )
                # Calculate cost after placing element at position k
                after = (
                    abs(a[k + 1] - a[k - 1] - c)
                    + abs(a[k] - SOL[i - 1] - c)
                    + abs(a[0] - a[k] - c)
                )
                if before == after:
                    SOL[i] = a.pop(k)  # Select this element
                    break
            else:
                SOL[i] = a.pop(0)  # Default selection if no better match
        SOL[-2] = a[0]  # Place the final remaining element
        print(*SOL)


# https://github.com/VaHiX/CodeForces/