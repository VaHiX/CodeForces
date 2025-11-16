# Problem: CF 1838 C - No Prime Differences
# https://codeforces.com/contest/1838/problem/C

"""
Algorithm: Grid Filling with Non-Prime Differences
Techniques: 
- Pattern-based arrangement to avoid prime differences
- Utilizes a specific order of row filling to distribute numbers
- Uses a zigzag-like pattern in row selection to ensure adjacent differences are not prime

Time Complexity: O(n * m) per test case
Space Complexity: O(n * m) for output grid

The approach fills the grid in a specific order:
1. First, rows are selected in a pattern: all odd-indexed rows from bottom to top, then all even-indexed rows from bottom to top.
2. For each selected row, fill the values in increasing order from left to right.
This method ensures that adjacent cells have differences that are always composite (non-prime) numbers.

Sample Output Pattern:
For a 4x4 grid:
16  7  1  9
12  8  2  3
13  4 10 11
14  5  6 15
"""

print(
    "\n".join(
        [
            "\n".join(
                [
                    " ".join([str(m * i + j) for j in range(1, m + 1)])
                    for i in [*range(n - 2, -1, -2)] + [*range(n - 1, -1, -2)]
                ]
            )
            for [n, m] in map(lambda x: map(int, x.split()), [*open(0)][1::])
        ]
    )
)


# https://github.com/VaHiX/CodeForces/