# Problem: CF 1817 D - Toy Machine
# https://codeforces.com/contest/1817/problem/D

"""
Algorithm: Toy Machine Solver
Techniques: Simulation, String Construction

Time Complexity: O(n)
Space Complexity: O(n)

The problem involves moving a specific toy to the leftmost position in the top row of a grid.
Toys are placed in the top row (excluding corners) and the bottom row has blocked cells.
The solution constructs a sequence of moves to position the k-th toy at the leftmost cell.

Approach:
- If k is in the left half (k < n/2), we move the toy right first, then use LDRU pattern to push it to the left.
- If k is in the right half (k >= n/2), we move the toy left first, then use RDLU and LDLU patterns to bring it to the left.
- The number of repetitions of these patterns is calculated based on the distance to the target position.
"""

n, k = map(int, input().split())
if k < n / 2:
    # For toys in the left half, move right first, then use LDRU pattern
    print("LDRU" * (k - 1) + "L")
else:
    # For toys in the right half, move left first, then use RDLU and LDLU patterns
    print("RDLU" * (n - k - 2) + "LDLU" * (n // 2) + "RDL")


# https://github.com/VaHiX/CodeForces/