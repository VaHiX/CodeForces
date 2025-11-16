# Problem: CF 1811 D - Umka and a Long Flight
# https://codeforces.com/contest/1811/problem/D

"""
Algorithm: Fibonacci Rectangle Tiling
Techniques: Simulation, Fibonacci Sequence, Greedy Approach

Time Complexity: O(n) per test case, where n <= 44
Space Complexity: O(1) - only using fixed-size arrays and variables

The problem involves determining whether a Fibonacci rectangle of order n can be tiled
into n+1 squares such that:
1. The painted cell lies in a unit square (side = 1)
2. At most one pair of squares have equal sides
3. All square sides are Fibonacci numbers

Approach:
- Precompute Fibonacci numbers up to F_44
- For each test case, simulate the tiling process by reducing the problem
  to smaller Fibonacci rectangles, tracking the position of the painted cell
  as it moves through each step of the decomposition
- At each step, check if the current position violates the constraints
"""

from sys import stdin

input = stdin.readline

fib = [1] * 46
for i in range(2, 46):
    fib[i] = fib[i - 1] + fib[i - 2]

for _ in range(int(input())):
    n, x, y = map(int, input().split())

    res = True
    for i in range(n, 1, -1):
        if (n - i) % 2 == 0:
            # Even steps: operate on y-coordinate (column)
            if y > fib[i]:
                y -= fib[i]
            elif y > fib[i - 1]:
                res = False
                break
        else:
            # Odd steps: operate on x-coordinate (row)
            if x > fib[i]:
                x -= fib[i]
            elif x > fib[i - 1]:
                res = False
                break

    print("YES" if res else "NO")


# https://github.com/VaHiX/CodeForces/