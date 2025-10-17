# Problem: CF 1990 D - Grid Puzzle
# https://codeforces.com/contest/1990/problem/D

"""
Grid Puzzle - Minimum Operations to Make All Cells White

Algorithms/Techniques: Greedy approach with state tracking
Time Complexity: O(n) where n is the size of the array
Space Complexity: O(1) - only using a few variables for tracking

The problem involves an n x n grid where each row has a certain number of black cells
at the beginning. We can perform two operations:
1. Dye a 2x2 subgrid white
2. Dye an entire row white

The goal is to find the minimum number of operations to make all cells white.

The approach uses greedy strategy with state tracking:
- We track if we're in a state where we can cover a 2x2 subgrid (b1, b2)
- We process rows from top to bottom
- For each row, we decide whether to use row-dyeing or 2x2 subgrid operations
  based on how many black cells are present and our current state
"""

MOD = 1000000007
MODD = 998244353


def bigmod(a, b):
    ans = 1
    powa = a
    while b > 0:
        if b % 2 == 1:
            ans = (ans * powa) % MOD
        powa = (powa * powa) % MOD
        b //= 2
    return ans


def func():
    n = int(input())
    arr = list(map(int, input().split()))
    b1, b2 = False, False  # State variables to track if we can form a 2x2 block
    ans = 0
    for i in range(n):
        if not b1 and not b2:  # No pending 2x2 subgrid action
            if arr[i] == 0:  # No black cells in this row
                continue
            ans += 1  # Use a row-dyeing operation
            if arr[i] <= 2:  # If less than or equal to 2 black cells,
                b1 = True  # we might be able to form a 2x2 block next
        elif b1:  # We have a pending 2x2 block from previous row
            b1 = False  # Reset state
            if arr[i] <= 2:  # If current row has <= 2 black cells
                continue  # Skip (as we have already covered it in 2x2)
            ans += 1  # Need to dye another row
            if arr[i] <= 4:  # If it's small enough to fit in 2x2
                b2 = True  # Next block may be covered by 2x2
        else:  # b2 is true (we're in a 2x2 state of the row above)
            b2 = False  # Reset state
            if arr[i] == 0:  # Current row is all white
                continue
            ans += 1  # Need to dye a row
            if arr[i] <= 4:  # If current black count is small enough
                b1 = True  # Set up for 2x2 operation in next step
    print(ans)


def main():
    t = int(input())
    for _ in range(t):
        func()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/