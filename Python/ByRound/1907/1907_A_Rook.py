# Problem: CF 1907 A - Rook
# https://codeforces.com/contest/1907/problem/A

"""
Code Purpose:
This code solves the problem of finding all possible moves for a rook on a chessboard.
The rook can move any number of squares horizontally or vertically, so we need to
generate all squares in the same row and column as the rook's current position,
excluding the square the rook is currently on.

Algorithms/Techniques:
- Set operations to efficiently compute possible moves
- String manipulation to generate chess notation

Time Complexity: O(1) - The number of moves is always constant (14 moves regardless of input)
Space Complexity: O(1) - The space used is constant, independent of input size

The solution computes:
- All squares in the same row (8 squares)
- All squares in the same column (8 squares)
- Excludes the current square (1 square)
- Total: 14 possible moves
"""

for x, y, _ in [*open(0)][1:]:  # Read input lines, skip first line (test cases count)
    print(*{u + y for u in "abcdefgh"} ^ {x + u for u in "12345678"})  # Generate and print all possible moves


# https://github.com/VaHiX/CodeForces/