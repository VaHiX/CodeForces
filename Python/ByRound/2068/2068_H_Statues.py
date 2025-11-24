# Problem: CF 2068 H - Statues
# https://codeforces.com/contest/2068/problem/H

"""
H. Statues
Algorithm: Dynamic Programming with Coordinate Validation
Time Complexity: O(n * d_max) where d_max is the maximum distance
Space Complexity: O(n)

The problem requires placing n statues along a path from (0,0) to (a,b), where each step has a known Manhattan distance.
This solution uses dynamic programming to track valid ranges of possible y-coordinates at each step,
based on the constraints imposed by Manhattan distance.

Key Techniques:
- Dynamic Programming with state tracking: For each step i, maintain min and max possible y-values
  for a given x-coordinate range.
- Constraint validation using parity and bounds check.
- Reverse reconstruction to generate actual path coordinates.
"""

import sys

inp = lambda: sys.stdin.readline().rstrip()
Inp = lambda: [*map(int, sys.stdin.readline().split())]
(n,) = Inp()
x, y = Inp()
A = Inp()
X = [(0, 0)]
for a in A:
    x1, x2 = X[-1]  # previous range of possible y values
    y2 = x2 + a     # upper bound on current y after move of length a
    if x1 - a <= 0 <= x2 - a:  # 0 is reachable
        y1 = (x2 - a) % 2      # parity based shift
    else:
        y1 = min(abs(x2 - a), abs(x1 - a))  # minimum distance to 0
    X.append((min(y1, y2), max(y1, y2)))   # update range for next step

x1, x2 = X[-1]  # final range after all moves
# Check if the destination (x,y) is reachable using parity and bounds
if not (x1 <= abs(x) + abs(y) <= x2 and (x + y) % 2 == x1 % 2):
    print("NO")
else:
    print("YES")
    Ans = [(x, y)]
    p = abs(x) + abs(y)
    for i, (p1, p2) in enumerate(X[:-1][::-1]):   # process backwards
        a = A[~i]     # get step size from reverse order
        q2 = p + a    # upper bound estimate
        q1 = abs(p - a)  # lower bound estimate
        q = min(p2, max(q1, q2))  # adjust based on valid range
        for b1, c1 in (-1, q), (1, -q), (1, q), (-1, -q):  # try different combinations
            for b2, c2 in (
                (-1, x + a + y),
                (1, -x - a + y),
                (1, -x + a + y),
                (-1, x - a + y),
            ):
                if b1 == b2:  # matched sign
                    if c1 == c2:
                        (x1, y1) = (x, y)
                    else:
                        continue  # skip invalid combinations
                else:  # different signs
                    if b1 == 1:
                        x1 = (c2 - c1) // 2   # compute x coordinate
                        y1 = x1 + c1          # compute y coordinate from x and offset
                    else:
                        x1 = (c1 - c2) // 2   # same idea but reversed signs
                        y1 = x1 + c2
                # Check if current candidate satisfies both Manhattan distance and position constraints
                if abs(x1) + abs(y1) == q and abs(x1 - x) + abs(y1 - y) == a:
                    x, y = x1, y1    # update position
                    break
            else:
                continue  # inner loop failed, continue to next i
            break      # found match, exit inner loops
        else:
            raise      # no valid solution found - should not happen if earlier checks pass
        p = q          # prepare for next step
        Ans.append((x, y))  # store path
    for x, y in Ans[::-1]:  # output reversed path to get correct order
        print(x, y)


# https://github.com/VaHiX/codeForces/