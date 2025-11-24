# Problem: CF 2162 D - Beautiful Permutation
# https://codeforces.com/contest/2162/problem/D

"""
Algorithm: Binary Search on the modification range
Time Complexity: O(log n) per test case
Space Complexity: O(1)

The problem asks us to find a range [l, r] that was incremented by 1 in a permutation.
We use two types of queries:
- Type 1: Get sum of original permutation in range [l, r]
- Type 2: Get sum of modified array in range [l, r]

The key insight is that if we query both sums over a range, we can determine
how many elements in that range were incremented (i.e., how many elements were in [l, r]).
We can then binary search for the left boundary of this range.
"""

import gc
from sys import stdin

gc.disable()
_readline = stdin.readline
fprint = lambda *args, **kwargs: print(*args, flush=True, **kwargs)
input = lambda: _readline().rstrip("\r\n")
read = input
read_int = lambda: int(input())
read_ints = lambda: [int(_) for _ in input().split()]

CLEAR = 1
DIRTY = 2


def ask(mode, l, r):
    # Query the sum of either the original permutation or modified array in range [l, r]
    fprint(f"{mode } {l +1 } {r +1 }")
    return read_int()


def ans(l, r):
    # Output the found range [l, r]
    fprint(f"! {l +1 } {r +1 }")


def solve():
    n = read_int()

    # Compute the sum of original permutation (1 to n)
    real = ((1 + n) * n) // 2
    # Get the total sum of modified array
    curr = ask(DIRTY, 0, n - 1)

    # Difference gives the number of elements that were incremented
    sz = curr - real

    l = -1
    r = n - 1

    # Binary search to find left boundary of the modified range
    while r - l > 1:
        m = (l + r) // 2

        # Query sums of original and modified arrays up to position m
        x = ask(CLEAR, 0, m)
        y = ask(DIRTY, 0, m)

        # If both sums are equal, the modification range starts after m
        if x == y:
            l = m
        else:
            # Otherwise, the modification range includes m, so reduce search space
            r = m

    # Output the result: [l+1, l+sz] (1-indexed)
    ans(l + 1, l + sz)


if __name__ == "__main__":
    for _ in range(read_int()):
        solve()


# https://github.com/VaHiX/CodeForces/