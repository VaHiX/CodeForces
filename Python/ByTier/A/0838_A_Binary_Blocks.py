# Problem: CF 838 A - Binary Blocks
# https://codeforces.com/contest/838/problem/A

"""
Algorithm: Binary Blocks Compression
Approach:
- Use 2D prefix sums to quickly calculate the number of '1's in any rectangular block.
- For each possible value of k (from 2 to min(n, m)), pad the image to make it divisible by k.
- For each k x k block, compute the number of '1's and determine the minimum cost to make all pixels in the block uniform.
  - If there are more '1's than '0's, toggle the '0's; otherwise toggle the '1's.
- Return the minimum cost across all valid k values.

Time Complexity: O(min(n,m) * n * m)
Space Complexity: O(n * m)

Techniques:
- 2D prefix sum array for efficient range queries
- Iteration over all valid k values from 2 to min(n,m)
"""

import sys
from array import array


def solve() -> None:
    """Read input, compute the minimal number of toggles,
    and output the answer."""
    rd = sys.stdin.readline
    n, m = map(int, rd().split())

    # Initialize 2D prefix sum array with extra row and column for easier indexing
    S = [array("I", [0]) * (m + 1) for _ in range(n + 1)]
    for i in range(n):
        line = rd().strip()
        curr = S[i + 1]  # Current row in prefix sum array
        prev = S[i]      # Previous row in prefix sum array
        j0 = 0
        for ch in line:
            v = 1 if ch == "1" else 0
            # Update prefix sum: current = value + top + left - top-left
            curr[j0 + 1] = v + prev[j0 + 1] + curr[j0] - prev[j0]
            j0 += 1

    best = None
    max_k = min(n, m)

    # Try all possible k values from 2 to min(n, m)
    for k in range(2, max_k + 1):
        # Calculate padded dimensions so they are divisible by k
        N = ((n + k - 1) // k) * k
        M = ((m + k - 1) // k) * k
        block_sz = k * k

        cost = 0
        i = 0
        while i < N:
            r1 = i
            r2 = i + k - 1
            if r2 >= n:
                r2 = n - 1
            j = 0
            while j < M:
                c1 = j
                c2 = j + k - 1
                if c2 >= m:
                    c2 = m - 1

                if r1 <= r2 and c1 <= c2:
                    # Compute number of '1's in block [r1,c1] to [r2,c2]
                    ones = S[r2 + 1][c2 + 1] - S[r1][c2 + 1] - S[r2 + 1][c1] + S[r1][c1]

                    # Choose to toggle the smaller count (either 1s or 0s)
                    if ones <= block_sz - ones:
                        cost += ones
                    else:
                        cost += block_sz - ones

                j += k
            i += k

        # Update the minimum cost if current is better
        if best is None or cost < best:
            best = cost

    print(best)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/