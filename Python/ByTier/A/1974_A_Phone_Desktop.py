# Problem: CF 1974 A - Phone Desktop
# https://codeforces.com/contest/1974/problem/A

"""
Algorithm: Greedy approach to minimize the number of 5x3 screens needed.
Each screen has 15 cells (5 * 3).

Approach:
1. First, place all 2x2 icons optimally. Since each 2x2 icon occupies 4 cells and a screen has 15 cells,
   we can fit at most 3 such icons per screen, but actually, we can place up to 4 (2x2) icons on a 
   screen if they're arranged in a pattern like a 4x4 square, which doesn't fit in 5x3. 
   So the optimal approach is to pack them as efficiently as possible.

2. However, a better method:
   - Try to fit the 2x2 icons first.
   - For y 2x2 icons, we need at least ceil(y / 2) screens because 
     each screen can hold at most 2 such icons (since 2*2 = 4 and 4 <= 15).
   - Then, calculate how many 1x1 icons remain after placing 2x2 icons.
   - For remaining 1x1 icons, pack them greedily, using full rows or partial rows on the remaining screens.

3. A much simpler greedy idea:
   - Start by calculating how many screens are needed just for 2x2 icons.
   - Place them greedily.
   - Count how many 1x1 icons are leftover after placing 2x2 icons.
   - Allocate extra screens as needed.

But the current algorithm is:
- Calculate a = ceil(y / 2)
- Try to place remaining 1x1 icons after assigning one 2x2 icon per screen.
- Then greedily allocate leftover 1x1 on top of existing or new screens.

Time Complexity: O(1) - only basic arithmetic operations.
Space Complexity: O(1) - only a fixed number of variables used.
"""

import sys

input = lambda: sys.stdin.readline().strip()
printerr = lambda *args, **kwargs: print(
    "\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs
)


def main():
    x, y = map(int, input().split()) # x = 1x1 apps, y = 2x2 apps
    a = (y + 1) // 2  # Estimate of minimum screens for 2x2 apps (at most 2 per screen)
    x -= 4 * (y % 2)  # Remove space used by 2x2 icons (each requires a fixed amount)  
    x -= a * 7        # Deduct capacity of 1x1 icons for current number of screens, assuming 7 cells left per screen
    a += max((x + 14) // 15, 0)  # Add more screens needed for leftover 1x1 apps
    print(a)


tcs = int(input())
for tc in range(tcs):
    main()


# https://github.com/VaHiX/CodeForces/