# Problem: CF 1852 A - Ntarsis' Set
# https://codeforces.com/contest/1852/problem/A

"""
Problem: Ntarsis' Set
Purpose: Given a set S initially containing integers 1, 2, ..., 10^1000 in sorted order,
         and an array 'a' of n distinct indices, each day we remove the a1-th, a2-th, ..., an-th smallest elements.
         After k days, find the smallest remaining element in S.

Algorithms/Techniques:
- Simulation with two pointers and incremental updates
- Greedy approach to determine which elements are skipped or removed

Time Complexity: O(n + k)
Space Complexity: O(1)

Approach:
- We simulate the process step by step.
- Start with ans = 1, and use increaser to track how many elements were skipped in previous steps.
- For each of the k days, update the answer by adding increaser (number of elements skipped).
- Use a pointer (curr_idx) to track which element from array 'a' is being processed next.
- If the current position in array 'a' can be handled (i.e., does not exceed the count of elements), increment the increaser and move the pointer.
- Otherwise, proceed with increasing the answer.

"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    arr = tuple(map(int, input().split()))
    if arr[0] != 1:
        print(1)
        continue
    ans = 1
    increaser = 1
    curr_idx = 1
    while k > 0:
        # If index is valid and the current element can be skipped without going beyond what's available
        if (curr_idx) < n and (ans + increaser >= arr[curr_idx]):
            increaser += 1
            curr_idx += 1
            continue
        ans += increaser
        k -= 1
    print(ans)


# https://github.com/VaHiX/codeForces/