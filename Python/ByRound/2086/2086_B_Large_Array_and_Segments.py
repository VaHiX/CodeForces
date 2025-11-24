# Problem: CF 2086 B - Large Array and Segments
# https://codeforces.com/contest/2086/problem/B

"""
B. Large Array and Segments

Purpose:
This code computes the number of starting positions l in the repeated array b (formed by repeating array a k times)
such that there exists a position r >= l where the sum of elements from l to r is at least x.

Algorithm:
- Use prefix sums and sliding window technique.
- First, compute how many full cycles of the array contribute to the result, then process remaining elements.
- For each element in reverse order, subtract it from x until x becomes non-positive.
- Calculate the maximum number of positions satisfying the condition using arithmetic operations.

Time Complexity: O(n) per test case
Space Complexity: O(1) (excluding input storage)

Techniques:
- Prefix sum optimization
- Sliding window idea with backward iteration
- Modular arithmetic and greedy approach

"""

import sys

input = sys.stdin.readline
t = int(input())
for tests in range(t):
    n, k, x = map(int, input().split())
    A = list(map(int, input().split()))
    S = sum(A)  # Total sum of array A
    ko = x // S * n  # Number of full cycles that can be used
    x %= S  # Remaining amount after full cycles
    for i in range(n - 1, -1, -1):  # Iterate from last to first element
        if x <= 0:  # If remaining x is non-positive, stop
            break
        x -= A[i]  # Reduce x by current element
        ko += 1  # Increment count of elements needed
    print(max(0, n * k - ko + 1))  # Final answer calculation


# https://github.com/VaHiX/codeForces/