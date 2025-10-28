# Problem: CF 1881 C - Perfect Square
# https://codeforces.com/contest/1881/problem/C

"""
Problem: Perfect Square
Purpose: Transform an n x n matrix (n is even) into a perfect square by rotating 90 degrees,
         where the matrix remains unchanged after one 90-degree clockwise rotation.
         Each cell can be incremented to the next character in the alphabet (with 'z' wrapping to 'z').

Algorithm:
- For each group of 4 symmetric positions in the matrix, we determine the maximum character
  among those 4 positions. Then, we compute how many operations are needed to bring all
  4 elements to that maximum character, which minimizes total operations.

Time Complexity: O(n^2)
Space Complexity: O(1)

Techniques:
- Matrix rotation symmetry: 4 cells form a group that must be equal after 90-degree rotation.
- Greedy approach: for each group, choose the maximum character as target to minimize moves.
"""

def solve():
    t = int(input().strip())
    for _ in range(t):
        n = int(input().strip())
        grid = []
        for i in range(n):
            grid.append(input().strip())
        total_ops = 0
        # Iterate through the top-left quadrant of the matrix
        for i in range(n // 2):
            for j in range(n // 2):
                # Get the four symmetric positions
                a = grid[i][j]  # Top-left
                b = grid[j][n - 1 - i]  # Top-right
                c = grid[n - 1 - i][n - 1 - j]  # Bottom-right
                d = grid[n - 1 - j][i]  # Bottom-left
                
                # Determine the maximum character among the four
                max_char = max(a, b, c, d)
                
                # Calculate operations needed to make all 4 equal to max_char
                total_ops += (
                    (ord(max_char) - ord(a))  # Convert to ASCII and compute difference
                    + (ord(max_char) - ord(b))
                    + (ord(max_char) - ord(c))
                    + (ord(max_char) - ord(d))
                )
        print(total_ops)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/