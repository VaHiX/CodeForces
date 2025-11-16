# Problem: CF 1819 B - The Butcher
# https://codeforces.com/contest/1819/problem/B

"""
Code Purpose:
This code solves the problem of finding all possible original rectangle dimensions (h, w) 
from which a given set of n rectangles could have been obtained by a series of cuts. 
Each cut divides a rectangle either vertically or horizontally into two smaller rectangles with integer sides.

Algorithm:
1. For each test case, compute total area and maximum height/width.
2. Try two possibilities: 
   - Assume original rectangle has height = max_h and width = area / max_h
   - Assume original rectangle has width = max_w and height = area / max_w
3. For each possibility, perform a DFS simulation:
   - Start with the assumed original rectangle.
   - At each step, try to match one of the given rectangles in the list.
   - Cut the rectangle either vertically or horizontally based on matching criteria.
   - Continue until all rectangles are matched or invalid state is reached.
4. Add valid original dimensions to result set.

Time Complexity: O(n^2) in worst case due to nested loops in DFS and list operations, but often much better in practice.
Space Complexity: O(n) for storing rectangles and auxiliary data structures.
"""

import sys
from collections import defaultdict

MOD = 10**9 + 7

stdin = sys.stdin

ni = lambda: int(ns())
na = lambda: list(map(int, stdin.readline().split()))
ns = lambda: stdin.readline().rstrip()

t = int(input())


def solve():
    n = ni()
    area = 0
    max_h = 0
    max_w = 0
    AB = []
    H = defaultdict(list)  # Maps height to list of indices of rectangles with that height
    HH = defaultdict(list)  # Same as H, but for reverse use
    W = defaultdict(list)  # Maps width to list of indices of rectangles with that width
    WW = defaultdict(list)  # Same as W, but for reverse use
    for i in range(n):
        a, b = na()
        max_h = max(max_h, a)
        max_w = max(max_w, b)
        area += a * b
        H[a].append(i)
        HH[a].append(i)
        W[b].append(i)
        WW[b].append(i)
        AB.append((a, b))

    ans = set()

    def dfs(sh, sw, H, W):
        # Initialize DFS with starting rectangle dimensions sh x sw
        q = [(sh, sw)]
        seen = [False] * n  # Tracks which rectangles have been used
        used = 0  # Count of used rectangles
        while q:
            assert len(q) == 1  # Ensure only one item in queue at a time
            h, w = q.pop()

            if h < 0 or w < 0:  # Invalid dimension
                break
            if (h == 0 or w == 0) and used == n:  # All rectangles matched
                ans.add((sh, sw))
                break
            used += 1
            
            # Try to find a rectangle matching the current height h
            while H[h] and seen[H[h][-1]]:  # Skip already used rectangles
                H[h].pop()
            if H[h]:
                i = H[h].pop()  # Get index of matching rectangle
                seen[i] = True
                a, b = AB[i]
                q.append((h, w - b))  # Push the remaining part
                continue

            # Try to find a rectangle matching the current width w
            while W[w] and seen[W[w][-1]]:  # Skip already used rectangles
                W[w].pop()
            if W[w]:
                i = W[w].pop()  # Get index of matching rectangle
                seen[i] = True
                a, b = AB[i]
                q.append((h - a, w))  # Push the remaining part

    if area % max_h == 0:
        w = area // max_h
        dfs(max_h, w, H, W)
    if area % max_w == 0:
        h = area // max_w
        dfs(h, max_w, HH, WW)

    print(len(ans))
    for a, b in ans:
        print(a, b)


for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/