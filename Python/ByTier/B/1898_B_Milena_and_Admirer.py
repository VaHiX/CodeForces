# Problem: CF 1898 B - Milena and Admirer
# https://codeforces.com/contest/1898/problem/B

"""
Purpose: 
This code solves the problem of making an array non-decreasing by splitting elements into smaller parts.
The operation allows splitting an element a[i] into x and a[i]-x, where 1 <= x < a[i].
The goal is to find the minimum number of such operations needed.

Algorithm:
- Process the array from right to left.
- Keep track of the current minimum element seen so far (curr).
- If the current element A[i] is greater than curr, we must split it.
- When splitting, we determine how many sub-elements are needed to make A[i] <= curr.
- If A[i] is divisible by curr, then we split it into (A[i] // curr) elements, requiring (A[i] // curr - 1) operations.
- Otherwise, we split it into (A[i] // curr + 1) parts, requiring (A[i] // curr) operations.
- Adjust the curr value after splitting to reflect the new effective minimum.

Time Complexity: O(n) where n is the length of the array.
Space Complexity: O(1) excluding the input storage.
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    A = list(map(int, input().split()))
    ans = 0
    curr = A[-1]  # Start from the last element as the initial reference
    for i in range(n - 2, -1, -1):  # Traverse from right to left
        if A[i] <= curr:
            # If current element is already less than or equal to curr, update curr
            curr = A[i]
        else:
            # When A[i] > curr, we must split it
            q, r = divmod(A[i], curr)
            if r == 0:
                # If A[i] is divisible by curr, we need (q - 1) operations
                ans += q - 1
            else:
                # If not divisible, we need q operations, and adjust curr
                ans += q
                curr = A[i] // (q + 1)
    return ans


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/