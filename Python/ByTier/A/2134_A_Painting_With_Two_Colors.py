# Problem: CF 2134 A - Painting With Two Colors
# https://codeforces.com/contest/2134/problem/A

# Problem: Determine if a symmetric painting with two colors is possible.
# Algorithm/Technique: Mathematical analysis and bitwise operations.
# Time Complexity: O(1) per test case.
# Space Complexity: O(1).

for s in [*open(0)][1:]:
    n, a, b = map(int, s.split())
    # The logic checks if there exist valid x and y such that coloring is symmetric.
    # We use bitwise operations to determine the result efficiently:
    # - (n + b) & 1 checks parity of (n + b)
    # - (n + a) & 1 checks parity of (n + a)
    # - The condition ensures valid symmetric arrangements.
    print("YNEOS"[n + b & 1 or n + a & 1 and a > b :: 2])


# https://github.com/VaHiX/codeForces/