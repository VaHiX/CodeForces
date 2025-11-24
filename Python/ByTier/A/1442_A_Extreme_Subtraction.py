# Problem: CF 1442 A - Extreme Subtraction
# https://codeforces.com/contest/1442/problem/A

"""
Problem: Extreme Subtraction
Algorithm: Greedy approach with simulation
Time Complexity: O(n) per test case
Space Complexity: O(n) for the array copies and auxiliary arrays

The problem allows decrementing k first elements or k last elements of the array.
We simulate the process by maintaining a "cur" value representing the minimum
value we can subtract from current elements without violating constraints.
If at any point we cannot maintain the non-decreasing property (or exceed original values),
we output "NO".
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    N = int(input())
    A = list(map(int, input().split()))
    B = A[::]  # Copy of original array for comparison
    ans = "YES"
    a1, a2 = [0] * N, [0] * N
    cur = A[0]
    for i in range(N):
        cur = min(cur, A[i])
        A[i] -= cur  # Subtract the minimum so far from current element
        if i - 1 >= 0 and A[i] < A[i - 1]:
            cur -= A[i - 1] - A[i]  # Adjust cur based on previous element
            A[i] = A[i - 1]  # Update current element to match previous
            if A[i] > B[i]:  # If it exceeds original value, impossible
                ans = "NO"
    cur = A[-1]
    while A:
        if cur < A[-1]:  # If we see a decrease in order, impossible
            ans = "NO"
            break
        cur = A.pop()
    print(ans)


# https://github.com/VaHiX/codeForces/