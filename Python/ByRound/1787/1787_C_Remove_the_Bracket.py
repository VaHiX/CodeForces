# Problem: CF 1787 C - Remove the Bracket
# https://codeforces.com/contest/1787/problem/C

"""
Problem: Remove the Bracket
Algorithm: Dynamic Programming with Optimized State Transition
Time Complexity: O(n), where n is the length of the array
Space Complexity: O(n), for storing the transformed array and dp states

Approach:
- For each element a[i] in the middle of the array (from index 1 to n-2), we choose x[i] and y[i]
  such that x[i] + y[i] = a[i] and (x[i] - s)*(y[i] - s) >= 0.
- The constraint (x[i] - s)*(y[i] - s) >= 0 means that both x[i] and y[i] are either 
  both >= s or both <= s.
- We transform the problem into a decision on how to assign x[i] and y[i] to minimize F.
- The key insight is that we can decide optimally for each a[i] based on whether it's 
  greater than or equal to 2*s or less than 2*s, and we precompute x[i] and y[i].
- Then we use dynamic programming with two states to avoid checking all combinations,
  minimizing the total cost by choosing the optimal assignment at each step.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def printd(*args, **kwargs):
    print(*args, **kwargs)


def get_str():
    return input().decode().strip()


def rint():
    return map(int, input().split())


def oint():
    return int(input())


def solve(iter, cnt):
    for c in range(cnt):
        iter()


def solve_iter():
    n, s = rint()
    a = list(rint())

    # Transformed array to represent x[i] and y[i] values
    l = [0] * ((n - 1) * 2 + 1)
    l[0] = a[0]
    for i in range(1, n - 1):
        if a[i] >= s * 2:  # If a[i] >= 2*s, then both x[i] and y[i] are >= s
            l[2 * i - 1] = s
            l[2 * i] = a[i] - s
        elif s <= a[i] < s * 2:  # If s <= a[i] < 2*s, we still want both x[i] and y[i] >= s or <= s 
            l[2 * i - 1] = s
            l[2 * i] = a[i] - s
        elif a[i] < s:  # If a[i] < s, both x[i] and y[i] must be <= s
            l[2 * i - 1] = 0
            l[2 * i] = a[i]
    l[2 * n - 3] = a[n - 1]
    l[2 * n - 2] = a[n - 1]

    # Initialize DP states for current and next steps
    cur_tot = [l[0] * l[1], l[0] * l[2]]
    for i in range(1, n - 1):
        ii = 2 * i
        # Update dp state by comparing choices: taking l[ii] or l[ii-1] with future l[ii+1] or l[ii+2]
        cur_tot = [
            min(cur_tot[0] + l[ii] * l[ii + 1], cur_tot[1] + l[ii - 1] * l[ii + 1]),
            min(cur_tot[0] + l[ii] * l[ii + 2], cur_tot[1] + l[ii - 1] * l[ii + 2]),
        ]
    print(cur_tot[0])


solve(solve_iter, oint())


# https://github.com/VaHiX/CodeForces/