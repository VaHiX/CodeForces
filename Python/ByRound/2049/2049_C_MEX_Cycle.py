# Problem: CF 2049 C - MEX Cycle
# https://codeforces.com/contest/2049/problem/C

"""
Algorithm: MEX Cycle
Approach:
- Construct an assignment of values to dragons such that each dragon's value is the MEX of its friends' values.
- Use a cyclic pattern: assign values 0, 1, 0, 1, ... to dragons in a cycle starting from x.
- Adjust the value at x if needed to ensure the constraint is satisfied.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the output array

Techniques:
- Modular arithmetic to handle circular indexing
- Greedy assignment with adjustment for special cases
"""

import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    for _ in range(t):
        n = int(data[idx])
        x = int(data[idx + 1]) - 1  # Convert to 0-based indexing
        y = int(data[idx + 2]) - 1  # Convert to 0-based indexing
        idx += 3
        ans = [0] * n
        # Fill the array with alternating 0 and 1 values starting from x
        for i in range(n):
            pos = (x + i) % n
            ans[pos] = i % 2
        # If n is even and the difference between x and y is even,
        # we need to adjust the value at x to 2 to avoid conflicts
        if n % 2 or (x - y) % 2 == 0:
            ans[x] = 2
        print(" ".join(map(str, ans)))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/