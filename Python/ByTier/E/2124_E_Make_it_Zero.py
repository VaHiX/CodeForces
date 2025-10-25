# Problem: CF 2124 E - Make it Zero
# https://codeforces.com/contest/2124/problem/E

"""
E. Make it Zero

Purpose:
This code solves the problem of reducing an array of positive integers to all zeros using a specific operation:
- Select an array b such that 0 <= b[i] <= a[i] for all i,
- There exists an index i < n such that sum(b[0..i]) == sum(b[i+1..n]).
- Subtract b[i] from a[i] for all i.

The algorithm finds the minimum number of operations (at most 17) required to make all elements zero, or returns -1 if impossible.

Algorithms/Techniques:
Greedy approach with prefix sums to find valid splits.
Key observation: if total sum is odd, impossible. Also, if max element exceeds half the sum, also impossible.
The solution explores splitting the array into two parts where the left part's sum equals the right part's sum, or adjusts the split accordingly.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays and temporary variables
"""

import sys

input = sys.stdin.readline
out = []
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    tot = sum(a)
    if tot % 2 or 2 * max(a) > tot:
        out.append("-1")
        continue
    i = 0
    left = 0
    # Find the largest prefix such that its sum is <= total_sum / 2
    while 2 * (left + a[i]) <= tot:
        left += a[i]
        i += 1
    if 2 * left == tot:
        # If prefix sum equals half of total sum, we can just use one operation
        out.append("1")
        out.append(" ".join(map(str, a)))
        continue
    # Else, we need two operations
    b = [0] * n
    # Amount to take from a[i] to balance the left side
    b[i] = (tot - left - left) // 2
    rem = b[i]
    # Distribute remaining amount across right elements
    for j in range(i + 1, n):
        z = min(rem, a[j])
        b[j] = z
        rem -= z
    assert rem == 0
    # Adjust original array after subtracting b
    for j in range(n):
        a[j] -= b[j]
    assert min(a) >= 0
    assert min(b) >= 0
    assert sum(a[:i]) == sum(a[i:])
    out.append("2")
    out.append(" ".join(map(str, a)))
    out.append(" ".join(map(str, b)))
print("\n".join(out))


# https://github.com/VaHiX/codeForces/