# Problem: CF 2156 C - Maximum GCD on Whiteboard
# https://codeforces.com/contest/2156/problem/C

"""
Algorithm: Maximum GCD on Whiteboard
Approach:
- For each possible divisor d (from n down to 1), we check if we can make all numbers on the whiteboard divisible by d.
- To do this, we calculate how many numbers are divisible by d, 2*d, 3*d etc. and determine if we can reduce the count to <= k operations.
- We process numbers in reverse order to optimize the search and use prefix sums for efficient queries.

Time Complexity: O(n log n)
Space Complexity: O(n)
"""

import sys


def solve_all(data):
    it = iter(data)
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        n = int(next(it))
        k = int(next(it))
        f = [0] * (n + 1)

        # Count frequency of each number
        for _ in range(n):
            x = int(next(it))
            if 1 <= x <= n:
                f[x] += 1

        # Compute prefix sum for efficient range queries
        p = [0] * (n + 1)
        for i in range(1, n + 1):
            p[i] = p[i - 1] + f[i]

        ans = 1

        # Iterate from largest possible divisor down to 1
        for i in range(n, 0, -1):
            # Calculate upper bound for checking multiples of i
            x = min(n, 4 * i - 1)
            # Count all numbers in range [1, x]
            l = p[x]
            m = 0
            # Count how many numbers are multiples of i, 2*i, 3*i, etc. that we must not erase
            if i <= n:
                m += f[i]
            if 2 * i <= n:
                m += f[2 * i]
            if 3 * i <= n:
                m += f[3 * i]
            # If remaining numbers (l - m) is at most k, we can make all numbers divisible by i
            if l - m <= k:
                ans = i
                break
        out_lines.append(str(ans))
    return "\n".join(out_lines)


if __name__ == "__main__":
    data = sys.stdin.buffer.read().split()
    if not data:
        raise SystemExit
    print(solve_all(data))


# https://github.com/VaHiX/CodeForces/