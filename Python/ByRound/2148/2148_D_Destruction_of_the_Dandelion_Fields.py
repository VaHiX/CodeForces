# Problem: CF 2148 D - Destruction of the Dandelion Fields
# https://codeforces.com/contest/2148/problem/D

"""
D. Destruction of the Dandelion Fields

Purpose:
This code solves the problem of maximizing the number of dandelions Farmer John can cut by optimally ordering his visits to fields. 
The lawnmower toggles its state when entering a field with an odd number of dandelions, and only cuts dandelions if it's on.

Algorithm:
1. Separate odd and even numbers from input.
2. All even numbers are added to the result immediately (they do not affect lawnmower state).
3. If there are no odd numbers, return 0 since lawnmower never turns on.
4. For odd numbers:
   - Sort them in descending order.
   - Take the first ceil(len(odd)/2) elements (these must be cut to maximize total count).
   - Add this sum to the even-numbered fields' sum.

Time Complexity: O(n log n) due to sorting the odd numbers.
Space Complexity: O(n) for storing odd numbers and input array.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ans = 0
    b = []
    for j in range(n):
        if a[j] % 2:  # If the number of dandelions is odd
            b.append(a[j])
        else:         # If even, cut them immediately (lawnmower state doesn't matter)
            ans += a[j]
    if not (b):       # No odd numbers means lawnmower never turns on
        print(0)
    else:
        b.sort(reverse=True)  # Sort odds in descending order for optimal selection
        ans += sum(b[: len(b) // 2 + len(b) % 2])  # Select ceiling(n/2) largest odds
        print(ans)


# https://github.com/VaHiX/codeForces/