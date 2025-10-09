# Problem: CF 2109 B - Slice to Survive
# https://codeforces.com/contest/2109/problem/B

# B. Slice to Survive
# Algorithm: This problem uses a greedy approach based on bit manipulation to determine the number of turns needed.
# Time Complexity: O(1) per test case, since all operations are constant time.
# Space Complexity: O(1), only a few variables are used.

f = lambda x, y: (x - 1).bit_length() - ~(y - 1).bit_length()
# The function f calculates the number of turns needed to reduce a grid of size x*y to 1*1,
# using bit operations for efficiency.
# (x - 1).bit_length() gives the number of bits needed to represent x-1 in binary.
# ~ (y - 1) is equivalent to -(y - 1) - 1 = -y, so its bit length is calculated as -(y - 1).bit_length().
# This approach avoids explicit logarithms and uses bit operations for performance.

for s in [*open(0)][1:]:
    n, m, a, b = map(int, s.split())
    # Read input: n rows, m columns, starting position (a, b)
    print(min(f(n - a + 1, m), f(a, m), f(n, m - b + 1), f(n, b)))
    # Compute the minimum number of turns for four possible strategies:
    # 1. Cut horizontally from top to current row (a) and keep bottom part.
    # 2. Cut horizontally from current row (a) to bottom and keep top part.
    # 3. Cut vertically from left to current column (b) and keep right part.
    # 4. Cut vertically from current column (b) to right and keep left part.


# https://github.com/VaHiX/codeForces/