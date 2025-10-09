# Problem: CF 2108 F - Fallen Towers
# https://codeforces.com/contest/2108/problem/F

"""
F. Fallen Towers
Algorithm: Binary search on answer + greedy validation using a difference array
Time Complexity: O(n * log n) per test case
Space Complexity: O(n) for the difference array and auxiliary structures

The problem involves rearranging tower heights by knocking them down in a specific order,
ensuring the final array is non-decreasing, and maximizing the MEX (smallest missing non-negative integer).

Approach:
- Binary search on the answer (the maximum MEX we can achieve)
- For each candidate MEX value, validate if it's possible to reach such a configuration
- Use a greedy strategy: at each step, determine whether we can place the next tower without violating order
- A difference array is used to efficiently manage the "addition of 1" operations across ranges

This solution uses a combination of:
1. Binary Search on the result (log n steps)
2. Greedy validation with difference array technique (O(n) per validation)

Key idea:
If we want to achieve a MEX of k, then in the final array, all values from 0 to k-1 must occur at least once,
and k must not occur.

We simulate the process in reverse: starting from the desired end state and trying to build backward.
"""

import sys


def solve():
    t = int(sys.stdin.readline())
    ans_list = []
    for _ in range(t):
        size = int(sys.stdin.readline())
        towers = list(map(int, sys.stdin.readline().split()))
        expires = [0] * size

        def feasible(goal):
            # Reset the expires array for each test
            for j in range(size):
                expires[j] = 0
            active = 0
            for i in range(size):
                # Subtract the number of towers that stop "growing" at position i
                active -= expires[i]
                # Calculate how many blocks are needed so that tower i is >= goal - (size - i)
                req = i - (size - goal)
                if req < 0:
                    req = 0
                # If we don't have enough "active" blocks, this goal is impossible
                if active < req:
                    return False
                prev = active
                # Calculate how far this tower can affect the future
                lim = i + towers[i] + prev - req + 1
                # Increase the "active" count by one since we're placing a block here
                active = prev + 1
                # Mark where the effect ends (for difference array)
                if lim < size:
                    expires[lim] += 1
            return True

        lo, hi = 1, size + 1
        while hi - lo > 1:
            mid = (lo + hi) // 2
            if feasible(mid):
                lo = mid
            else:
                hi = mid
        ans_list.append(str(lo))
    sys.stdout.write("\n".join(ans_list))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/