# Problem: CF 2046 B - Move Back at a Cost
# https://codeforces.com/contest/2046/problem/B

"""
B. Move Back at a Cost
Algorithm:Greedy with preprocessing
Time Complexity: O(n log n) due to sorting the P array
Space Complexity: O(n) for storing SUFMIN, P, and N arrays

The problem asks to find the lexicographically smallest array by performing operations:
- Choose an element, increment it by 1, and move it to the back.
This simulates a greedy process where we want to push larger elements towards the end 
to minimize the prefix of the final result.

Approach:
1. Preprocess suffix minimums to know the smallest value from each index to the end.
2. Greedily decide whether to increment and move an element or keep it.
3. Use two lists P (elements to be incremented and moved) and N (elements to be kept).
4. Sort P in ascending order, then append it to N to form the final array.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    A = list(map(int, input().split()))
    A.reverse()  # Reverse to process from right to left
    SUFMIN = [int(1e10)]  # Suffix minimum array initialized with large value
    for i in range(n):
        SUFMIN.append(min(SUFMIN[-1], A[i]))  # Build suffix minimums
    P = []  # Elements to be incremented and moved to back
    N = []  # Elements to be kept in place
    omi = int(1e10)  # Holds the minimum of incremented values so far that are pushed back
    for i in range(n - 1, -1, -1):  # Traverse from right to left
        if A[i] > SUFMIN[i] or A[i] > omi:  # If current element is greater than suffix min or pushed-back value
            omi = min(omi, A[i] + 1)  # Update the minimum of future elements that will be pushed_back
            P.append(A[i] + 1)  # Increment and push to back (to P)
        else:
            N.append(A[i])  # Keep in place (to N)
    P.sort()  # Sort increment operations to get lexicographically minimal result
    N += P  # Append sorted P to N
    print(*N)


# https://github.com/VaHiX/codeForces/