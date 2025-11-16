# Problem: CF 1737 C - Ela and Crickets
# https://codeforces.com/contest/1737/problem/C

"""
Problem: Determine if a cricket can reach a target square on an n x n chessboard,
         given that crickets are arranged in an "L" shape and can only jump over 
         adjacent crickets to land on the next square.

Algorithms/Techniques:
- The solution uses a mathematical approach to determine reachability based on 
  the configuration of the L-shaped crickets and the target square.
- It checks if the target is reachable by analyzing if it lies on the same row or 
  column as the middle cricket, or if it's reachable via a diagonal move that 
  preserves parity (even/odd) of coordinates relative to the middle cricket.

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant space usage
"""

for _ in range(int(input())):
    n = int(input())
    a1, b1, a2, b2, a3, b3 = map(int, input().split())
    x = sorted([a1, a2, a3])
    y = sorted([b1, b2, b3])
    x1, y1 = map(int, input().split())
    # Determine if the middle cricket (after sorting) is at a corner (1,1), (1,n), (n,1), or (n,n)
    if {x[1], y[1]} <= {1, n}:  # If the middle cricket is on a corner
        # Check if target is on same row or same column as the middle cricket
        print(["NO", "YES"][(x1 - x[1]) == 0 or (y1 - y[1]) == 0])
    else:
        # For non-corner positions, check parity of the move (diagonal reachability)
        print(["NO", "YES"][(x1 + x[1]) % 2 == 0 or (y1 + y[1]) % 2 == 0])


# https://github.com/VaHiX/CodeForces/