# Problem: CF 2120 A - Square of Rectangles
# https://codeforces.com/contest/2120/problem/A

# ******************************************************************************
# Problem: Arrange three rectangles to form a square
# Algorithms/Techniques: Sorting, Set operations, Greedy arrangement
# Time Complexity: O(1) - Fixed number of operations (3 rectangles)
# Space Complexity: O(1) - Only using fixed-size variables and sets
# ******************************************************************************
for s in [*open(0)][1:]:  # Read all lines except first (number of test cases)
    a = (*map(int, s.split()),)  # Convert input line to tuple of integers
    # Split into two rectangles: (l1, b1) and (l2, b2), then sort by l
    (a, b, c), (d, e, f) = sorted((a[::2], a[1::2]))  # a,b,c are first rect; d,e,f are second
    # Check if the rectangles can form a square:
    # Compare two conditions using set operations:
    # 1. Sum of heights from both rectangles == width of largest rectangle (i.e., a)
    # 2. The set of all three widths must equal the set of sums of pairs
    print("YNEOS"[{e, f, a + b + c} != {d} != {e + f, a + b, a + c} :: 2])


# https://github.com/VaHiX/codeForces/