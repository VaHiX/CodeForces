# Problem: CF 1739 A - Immobile Knight
# https://codeforces.com/contest/1739/problem/A

"""
Algorithm: Immobile Knight
Purpose: Find an isolated cell on an n x m chessboard where a knight cannot move to any other cell.
Techniques: 
- Mathematical observation based on knight movement patterns.
- If both n and m are greater than 2, a knight can always move from any cell; otherwise, there exists at least one isolated cell.

Time Complexity: O(1) - constant time for each test case.
Space Complexity: O(1) - constant space usage.

The solution uses a clever mathematical approach:
- For boards where both dimensions are > 2, there are no isolated cells.
- For boards where at least one dimension is <= 2, an isolated cell exists.
- The center of such a board (using integer division) always provides a valid isolated cell.
"""

for _ in range(int(input())):
    n, m = map(int, input().split())
    print(n // 2 + 1, m // 2 + 1)


# https://github.com/VaHiX/CodeForces/