# Problem: CF 2164 A - Sequence Game
# https://codeforces.com/contest/2164/problem/A

"""
Algorithm: Sequence Game
Purpose: Determine if a target value x can be obtained by merging adjacent elements in a sequence,
         where each merge replaces two adjacent elements with a value within their range.

Techniques:
- Range validation: The final value x must lie within the minimum and maximum values of the initial sequence.
  This is because every operation preserves the range of values that can be achieved.

Time Complexity: O(n) per test case, where n is the length of the array. This is due to computing min and max.
Space Complexity: O(1) additional space, excluding input storage.

The key insight is that regardless of how we merge elements, the final value must always be in the range
[min(arr), max(arr)], since merging operations can only produce values within the bounds of the original elements.
"""

import sys


def solve():
    it = iter(sys.stdin.read().strip().split())
    t = int(next(it))  # Read number of test cases
    out = []
    for _ in range(t):
        n = int(next(it))  # Read sequence length
        arr = [int(next(it)) for _ in range(n)]  # Read the sequence
        x = int(next(it))  # Read target value
        # Check if x is within the range of the array
        out.append("YES" if min(arr) <= x <= max(arr) else "NO")
    print("\n".join(out))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/