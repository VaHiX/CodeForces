# Problem: CF 690 B1 - Recover Polygon (easy)
# https://codeforces.com/contest/690/problem/B1

"""
Purpose: Determine if a given Zombie Contamination grid could be the result of a single non-zero area rectangular lair 
         with axis-parallel sides, where each cell's value represents the number of corners of that cell inside or on the 
         border of the rectangle.

Algorithms/Techniques:
- Brute-force search over all possible rectangles to validate if any produces the exact contamination levels.
- For each cell in the grid:
    - If the cell has contamination level > 0, we can determine if it's a corner or edge of the rectangle.
    - We calculate how many corners of the cell are inside or on the border of a potential rectangle based on its 
      neighbors.
    - Then we check if the actual level matches our computed one.

Time Complexity: O(N^4), where N is the grid size. In the worst case, we iterate through all possible rectangles (O(N^4)) 
                 and check each cell in the grid for consistency (O(1) per cell).

Space Complexity: O(N^2), for storing the input grid and the temporary field array.
"""

def check_cell(i, j, n):
    # Count how many of the 4 adjacent cells (up, down, left, right) are non-zero
    k = 0
    if i > 1 and field[i - 1][j]:  # Up
        k += 1
    if i < n - 1 and field[i + 1][j]:  # Down
        k += 1
    if j > 1 and field[i][j - 1]:  # Left
        k += 1
    if j < n - 1 and field[i][j + 1]:  # Right
        k += 1
    # Based on the number of adjacent non-zero cells, compute expected contamination level
    if k < 2:
        return 0
    elif k < 4:
        return k - 1
    else:
        return 4


n = int(input())
field = []
for i in range(n):
    temp = [int(x) for x in input()]  # Read grid row by row
    field.append(temp)


def main():
    # Iterate over every cell to check consistency
    for i in range(n):
        for j in range(n):
            if field[i][j] and not field[i][j] == check_cell(i, j, n):
                print("No")
                return 0
    print("Yes")


main()


# https://github.com/VaHiX/CodeForces/