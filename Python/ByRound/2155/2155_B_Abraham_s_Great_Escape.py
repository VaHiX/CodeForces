# Problem: CF 2155 B - Abraham's Great Escape
# https://codeforces.com/contest/2155/problem/B

# * B. Abraham's Great Escape
# *
# * Problem Description:
# * Given an n x n grid and a number k, construct a grid where exactly k starting cells allow Abraham to escape.
# * An arrow in each cell forces movement in that direction. If movement leads outside the grid, he escapes.
# *
# * Algorithm/Approach:
# * - The solution builds a pattern that controls how many cells lead to escape.
# * - First, handle impossible cases: if k = n² - 1, it's impossible because we need at least one cell
# *   that cannot escape (i.e., leads into a loop or another valid escape).
# * - Build a grid with specific arrow patterns:
# *   - Start by placing 'U' in all cells.
# *   - If k > 0 and there are remaining cells to mark for escape, use 'U' moves to create 
# *     paths leading out (by moving up from lower rows).
# *   - Then alternate between 'R' and 'L' or 'D' for other rows to control how many escape.
# *   - Special handling of row n-1 to ensure proper escaping and non-looping behavior.
# *
# * Time Complexity: O(n²) per test case — we iterate through the grid once to place arrows.
# * Space Complexity: O(n²) — used to store the output grid as strings.

from typing import List


def function(n: int, k: int) -> List[str]:
    res = []
    if k == n**2 - 1:
        return ["No"]
    res.append("Yes")
    lines = k // n  # Number of full rows of 'U' arrows
    extra = k % n   # Extra cells in the last row
    for i in range(lines):
        temp = "U" * n  # Fill full rows with 'U' (up)
        res.append(temp)
    if extra:
        if lines != n - 1:  # If not the last row
            # Fill the partial row with 'U' for 'extra' cells and 'D' for remaining
            temp = "U" * extra + "D" * (n - extra)
            res.append(temp)
            lines += 1
        else:
            # Last row case: use 'U' and 'R'/'L' to ensure correct escaping
            temp = "U" * extra + "R" * (n - extra - 1) + "L"
            res.append(temp)
            lines += 1
    for i in range(n - lines):  # Fill remaining rows with 'R' and 'L'
        temp = "R" * (n - 1) + "L"
        res.append(temp)
    return res


if __name__ == "__main__":
    t = int(input().strip())
    for _ in range(t):
        n, k = [int(x) for x in input().split()]
        for x in function(n, k):
            print(x)


# https://github.com/VaHiX/CodeForces/