# Problem: CF 1841 E - Fill the Matrix
# https://codeforces.com/contest/1841/problem/E

"""
Algorithm: Dynamic Programming + Stack + Greedy
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves placing integers in a matrix such that:
- Black cells are not filled
- Each row has at most one integer
- Beauty = count of consecutive integers in same row

Approach:
1. For each column i, a[i] black cells (from top) and (n - a[i]) white cells
2. Use a stack-based method to compute how many valid placements are possible
   by processing columns and calculating the 'gap' between black cell heights
3. Precompute possible beauty contributions for each gap size
4. Greedily assign integers to maximize beauty

The code computes the maximum possible beauty by:
1. Processing columns from left to right using a stack
2. For each such column, calculating how many integers can be placed in
   a given row to get a "jump" of a certain size (beauty value)
3. Using reverse processing also to handle transitions from right to left
4. Finally assigning the integers greedily based on precomputed values
"""

import sys
from array import array

input = lambda: sys.stdin.buffer.readline().decode().rstrip()
inp = lambda dtype: [dtype(x) for x in input().split()]
debug = lambda *x: print(*x, file=sys.stderr)
sum_n = lambda n: (n * (n + 1)) // 2
get_bit = lambda x, i: (x >> i) & 1
ceil_ = lambda a, b: a // b if (a >= 0) ^ (b > 0) else (abs(a) + abs(b) - 1) // abs(b)
Mint, Mlong, out = 2**30 - 1, 2**62 - 1, []


def solve(a, eq):
    stk = array("i") # Stack to keep track of column indices

    for i in range(n):
        ma = 0
        # While stack is not empty and current height is greater than stack top
        while stk and a[i] > a[stk[-1]]:
            ma = max(ma, a[stk.pop()]) # Update max height seen in popped elements

        # If stack is not empty and we're not dealing with equal heights (if eq == 0)
        # Or if there's an actual inequality in heights
        if stk and (a[i] != a[stk[-1]] or eq == 0):
            val = max(i - stk[-1] - 2, 0) # Calculate gap
            # Add contribution to number of possible placements
            mem[val] += (a[i] - ma) * val
        elif not stk and i: # If stack is empty and not the first column
            mem[i - 1] += (a[i] - ma) * (i - 1)

        stk.append(i) # Push the column index onto the stack


for _ in range(1, int(input()) + 1):
    n = int(input())
    a = array("i", inp(int))
    m, ans = int(input()), 0
    mem = [0] * n # Array to store how many placements give a certain beauty
    mem[n - 1] = (n - max(a)) * (n - 1) # Base case initialization
    
    solve(a, 0) # Forward pass
    solve(a[::-1], 1) # Reverse pass to handle other directions

    # Greedily assign integers to maximize beauty
    for i in range(n - 1, 0, -1):
        mi = min(m, mem[i] + ceil_(mem[i], i))
        m -= mi
        div, mod = divmod(mi, i + 1)
        ans += div * i + max(0, mod - 1)

    out.append(ans)

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/