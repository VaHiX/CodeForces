# Problem: CF 2074 C - XOR and Triangle
# https://codeforces.com/contest/2074/problem/C

# C. XOR and Triangle
# Given an integer x >= 2, find a positive integer y < x such that:
#   - The side lengths x, y, x^y form a non-degenerate triangle.
#   - A triangle is non-degenerate if the sum of any two sides is greater than the third.
#
# Algorithm:
#   - For each x, we iterate through possible y values in a smart way using bit manipulation.
#   - The key insight: for valid y, we want x, y, and x^y to form a triangle.
#     This means all three triangle inequalities must hold:
#       1. x + y > x^y
#       2. x + x^y > y
#       3. y + x^y > x
#   - A pattern emerges from trial and error: if we compute b = (x & -x) | (~x & -~x),
#     then we can determine if there's a valid y quickly.
#     We try values near the pattern derived from bit manipulation and check triangle inequality.
#
# Time Complexity: O(1) per test case, since we're using bit manipulation
# Space Complexity: O(1)

for x in [*map(int, open(0))][1:]:
    print((-1, b := x & -x | ~x & -~x)[b < x])


# https://github.com/VaHiX/codeForces/