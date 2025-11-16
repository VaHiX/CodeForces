# Problem: CF 1772 B - Matrix Rotation
# https://codeforces.com/contest/1772/problem/B

"""
Problem: Matrix Rotation
Algorithms/Techniques: Simulation, Permutations, Matrix Properties

Time Complexity: O(1) - Constant time operations (comparisons and checks)
Space Complexity: O(1) - Only using a fixed number of variables regardless of input size

The idea is to determine whether a 2x2 matrix can be made "beautiful" by rotating it 0, 1, 2, or 3 times.
A matrix is beautiful if:
- Each row has elements in increasing order (left < right)
- Each column has elements in increasing order (top < bottom)

Since there are only 4 elements in the matrix, we can analyze all 4 possible rotations.
However, we don't actually need to simulate rotations. Instead, we check all four possible
configurations where the minimum and maximum elements are in specific positions that would make
the matrix beautiful after some rotation.
"""

from sys import stdin

for _ in range(int(stdin.readline())):
    a, b = map(int, stdin.readline().split(" "))
    c, d = map(int, stdin.readline().split(" "))
    if min(a, b, c, d) == a and max(a, b, c, d) == d:
        print("YES")
    elif min(a, b, c, d) == b and max(a, b, c, d) == c:
        print("YES")
    elif min(a, b, c, d) == d and max(a, b, c, d) == a:
        print("YES")
    elif min(a, b, c, d) == c and max(a, b, c, d) == b:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/