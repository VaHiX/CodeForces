# Problem: CF 2059 E1 - Stop Gaming (Easy Version)
# https://codeforces.com/contest/2059/problem/E1

"""
E1. Stop Gaming (Easy Version)

Algorithm:
- This problem involves transforming arrays using operations that insert elements at the beginning of arrays.
- The key insight is to use a greedy approach: for each element in the target array,
  determine whether it matches the current position in the original array, and if not,
  count how many elements would be "wasted" by shifting.
- We process elements in order from top to bottom, left to right. For each row:
    - Try to match elements with the original array.
    - If there's a mismatch, we must perform an operation on a previously processed array.
    - The number of operations is computed as: total elements - matched elements.

Time Complexity: O(n * m)
Space Complexity: O(1) - only using a few variables for tracking state.

"""
import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n, m = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(n)]
    b = [list(map(int, input().split())) for _ in range(n)]
    used = 0  # Count of matched elements
    ra, ca = 0, 0  # Row and column index in original array
    for rb in range(n):  # Iterate through rows of target array
        for cb in range(m):  # Iterate through columns of target array
            if b[rb][cb] == a[ra][ca]:  # If element matches current position
                used += 1  # Increment matched count
                ca += 1  # Move to next column in original array
                if ca == m:  # If we've reached end of row
                    ra += 1  # Move to next row
                    ca = 0  # Reset column index
            elif ra == rb:  # If mismatch and we're at same row as original
                used -= ca  # Subtract the number of elements we can't use from current row
                ca = 0  # Reset column index
    ans = n * m - used  # Total elements minus matched elements is the operations count
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/