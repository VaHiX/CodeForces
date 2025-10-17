# Problem: CF 2013 A - Zhan's Blender
# https://codeforces.com/contest/2013/problem/A

# flowerbox
"""
Algorithm: Simulation with Greedy Approach
Techniques: Mathematical calculation, greedy strategy

Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem simulates a blender that processes fruits in seconds. Each second:
- Zhan can add up to `y` fruits into the blender.
- The blender processes `min(x, current_count)` fruits per second.
- We want to compute the minimum time to process all `n` fruits.

Key observations:
1. If n is 0, time is 0.
2. Otherwise, we simulate the process using division and ceiling logic:
   - In each operation, we can add up to `y` fruits and blend up to `x` fruits.
   - The number of seconds needed is calculated based on how many full cycles of
     adding and blending are required, plus an additional second if there's a remainder.

The solution uses an optimized mathematical formula:
- If n <= y: 1 second suffices.
- Otherwise: The number of operations is ceil(n / y), but the actual time depends
  on how efficiently we can blend `x` fruits per second.
"""

I = input
for _ in [0] * int(I()):
    n = int(I())
    x, y = map(int, I().split())
    # Calculate minimum time using ceiling division to handle partial batches
    print(0 - -n // min(x, y))


# https://github.com/VaHiX/codeForces/