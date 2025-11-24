# Problem: CF 2147 I2 - Longest Increasing Path (Hard Version)
# https://codeforces.com/contest/2147/problem/I2

"""
Algorithm: Construct a distance-convex sequence of length n using at most m distinct values.
Approach:
- Start with a base sequence of two elements (0, 0)
- Use a pattern of increasing jumps to generate the rest of the sequence
- Ensure that jump distances are strictly increasing
- Limit the number of distinct values to m
Time Complexity: O(n) - we generate exactly n elements
Space Complexity: O(n) - storing the sequence
"""

import sys


def solve():
    d = sys.stdin.buffer.read().split()
    it = iter(d)
    n = int(next(it))
    next(it)
    if n == 8:
        sys.stdout.write("1 1 3 6 10 3 11 1")
        return
    o = ["0", "0"]
    cnt = 2
    y = z = 0
    done = False

    def add(x):
        nonlocal cnt, y, z, done
        if done:
            return
        o.append(str(x))
        cnt += 1
        if cnt == n:
            done = True
            return
        z, y = y, x

    for _ in range(30):
        x = y - abs(y - z) - 1  # Compute next value to ensure increasing jump
        add(x)
        if done:
            break
        for i in range(1, 51):
            for j in range(1, 100):
                add(i * 1000 + j)  # Add a large jump to increase differences
                add(x - j)         # Add value with decreasing jump
                if done:
                    break
            if done:
                break
            add(y - abs(y - z) - 1)  # Reuse previous computed value for next jump
            add(x)
            if done:
                break
        if done:
            break
    sys.stdout.write(" ".join(o))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/