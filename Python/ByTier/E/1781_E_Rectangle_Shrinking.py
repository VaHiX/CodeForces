# Problem: CF 1781 E - Rectangle Shrinking
# https://codeforces.com/contest/1781/problem/E

"""
Algorithm: Rectangle Shrinking
Purpose: Given a set of rectangles on a 2x10^9 grid, we need to either remove or shrink each rectangle such that no two remaining rectangles overlap and the total area covered is maximized.

Approach:
1. Separate rectangles into two groups:
   - Group 1: Rectangles occupying only one row (u == d)
   - Group 2: Rectangles occupying two rows (u < d)
2. For each group in Group 1, we greedily merge overlapping rectangles.
3. For Group 2 rectangles, we also greedily resolve overlaps.
4. Then, for each rectangle in Group 2:
   - Check if it overlaps with any rectangles in Group 1.
   - If yes, and there's a gap, we potentially split or shrink rectangles.
5. Finally, compute the total area and output result.

Time Complexity: O(n log n) per test case due to sorting operations
Space Complexity: O(n) for storing rectangles and processing
"""

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n = int(input())
    rec = [list(map(int, input().split())) for _ in range(n)]

    rec1 = [[], []]  # rectangles with width 1 (only one row)
    rec2 = []  # rectangles with width 2 (two rows)

    for i, re in enumerate(rec):
        u, l, d, r = re
        if u == d:
            rec1[u - 1].append([l, r, i])  # 0-indexed row
        else:
            rec2.append((l, r, i))

    # Process rectangles in each row of rec1
    for i in range(2):
        remove = [0] * len(rec1[i])
        rec1[i].sort()
        e = 0
        for j in range(len(rec1[i])):
            l, r, idx = rec1[i][j]
            if l <= e:
                if r > e:
                    rec1[i][j][0] = e + 1  # Adjust left boundary
                    rec[idx][1] = e + 1    # Adjust left boundary in original
                else:
                    remove[j] = 1          # Mark for removal
                    rec[idx] = [0] * 4     # Remove rectangle
            e = max(e, r)
        rec1[i] = [rec1[i][j] for j in range(len(rec1[i])) if not remove[j]]

    # Process rectangles in rec2 (two-row rectangles)
    rec2.sort()
    e = 0
    for l, r, i in rec2:
        if l <= e:
            if r > e:
                rec[i][1] = e + 1      # Adjust left boundary in original
            else:
                rec[i] = [0] * 4       # Remove rectangle
        e = max(e, r)

    # For each rectangle in rec2, resolve overlap with rec1
    for i in range(2):
        if not rec1[i]:
            continue

        s = 0
        for _, _, idx in rec2:
            if rec[idx] != [0] * 4:
                u, l, d, r = rec[idx]

                # Find first rectangle in rec1[i] that could overlap
                while s + 1 < len(rec1[i]) and rec1[i][s][1] < l:
                    s += 1

                if rec1[i][s][1] < l:
                    break

                gap = False
                e = s

                # Check if any gap between consecutive intervals in rec1[i]
                while e + 1 < len(rec1[i]) and rec1[i][e][1] < r:
                    if rec1[i][e][1] + 1 != rec1[i][e + 1][0]:
                        gap = True
                    e += 1

                # Check if entire range spans correctly
                if rec1[i][s][0] > l or rec1[i][e][1] < r:
                    gap = True

                if gap:
                    # There's a gap, so we need to adjust rectangles
                    for j in range(s, e + 1):
                        l2, r2, idx2 = rec1[i][j]
                        # If current rectangle completely contains the part in rec2
                        if l <= l2 and r2 <= r:
                            rec[idx2] = [0] * 4   # Remove rectangle
                        else:
                            # If not completely contained, shrink bounds
                            if l2 < l:
                                rec[idx2][3] = l - 1  # Shrink right
                            elif l2 <= r < r2:
                                rec1[i][j][0] = r + 1  # Shrink left
                                rec[idx2][1] = r + 1   # Shrink left in original
                else:
                    # No gap - we can merge or adjust one row
                    if i == 0:
                        rec[idx][0] += 1      # Shrink top row
                    else:
                        rec[idx][2] -= 1      # Shrink bottom row
                        if rec[idx][0] > rec[idx][2]:
                            rec[idx] = [0] * 4 # Remove if invalid after shrinking

                s = e

    area = 0
    for u, l, d, r in rec:
        if u:
            area += (d - u + 1) * (r - l + 1)
    print(area)
    for re in rec:
        sys.stdout.write(" ".join(map(str, re)) + "\n")


# https://github.com/VaHiX/CodeForces/