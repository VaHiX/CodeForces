# Problem: CF 1776 I - Spinach Pizza
# https://codeforces.com/contest/1776/problem/I

"""
Algorithm: Game Theory on Convex Polygon Triangulation
Techniques: Minimax, Greedy Strategy

Time Complexity: O(n^2) due to nested loops for computing triangle areas and finding minimum
Space Complexity: O(n) for storing vertex coordinates and the list of remaining vertices

This problem is about a game played on a convex polygon where two players take turns
removing a triangle formed by three consecutive vertices. Each player wants to minimize
the total area they eat, with the goal being to eat at most half the pizza. The key insight
is that the last player to move (depending on n) can always force a win or at least tie.

The approach is based on parity:
- If n is odd, Beatrice moves first and can always ensure she eats at most half.
- If n is even, Alberto moves first and can always ensure he eats at most half.

In each turn, the current player chooses the triangle with the smallest area to minimize
their loss. The judge will choose greedily.
"""

import sys

input = sys.stdin.buffer.readline
n = int(input())
x = [0] * (n + 1)
y = [0] * (n + 1)
z = list(range(1, n + 1))  # List of remaining vertices
for i in range(1, n + 1):
    x[i], y[i] = map(int, input().split())

turn = 0
# Determine who starts based on parity of n
if n % 2:
    print("Beatrice")
    turn = 1
else:
    print("Alberto")
sys.stdout.flush()

# Play the game for n-2 turns
for i in range(n - 2):
    if i % 2 == turn:
        # Current player's turn: choose triangle with minimum area
        ans = [0] * len(z)
        for j in range(len(z)):
            a = z[(j + len(z) - 1) % len(z)]  # Previous vertex
            b = z[j]                         # Current vertex
            c = z[(j + 1) % len(z)]          # Next vertex
            # Compute area of triangle (a,b,c) using cross product
            xb = x[b] - x[a]
            xc = x[c] - x[a]
            yb = y[b] - y[a]
            yc = y[c] - y[a]
            ans[j] = abs(xb * yc - xc * yb)
        p = ans.index(min(ans))  # Choose triangle with minimum area
        p = z[p]
        print(p)
        z.remove(p)
        sys.stdout.flush()
    else:
        # Opponent's turn: read what they choose
        q = int(input())
        z.remove(q)


# https://github.com/VaHiX/CodeForces/