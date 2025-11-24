# Problem: CF 1396 A - Multiples of Length
# https://codeforces.com/contest/1396/problem/A

"""
Algorithm/Technique: 
The problem requires making all elements of an array zero using exactly three operations. Each operation selects a segment and adds multiples of the segment's length to each element in the segment. 

The approach:
1. First, we make the first element zero by adding -a[0] to it.
2. Then, we process the rest of the array from index 1 to n-1. For each element, we compute a value based on modulo n and the previous computations to ensure that when added, it aligns with the segment operations.
3. Then we process the entire array to make everything zero using two more operations.

Time Complexity: O(n)
Space Complexity: O(n)

This solution uses a greedy approach to compute the necessary additions for each element to ensure that the cumulative effect of operations results in all zeros.
"""

import sys

input = sys.stdin.readline
n = int(input())
w = list(map(int, input().split()))
print(1, 1)
print(w[0] * -1)
if n == 1:
    for i in range(2):
        print(1, 1)
        print(0)
else:
    print(2, n)
    d1 = []
    d2 = [0]
    for i in range(1, n):
        a = w[i] % n  # Compute modulo to determine the adjustment needed
        d1.append((n - 1) * a)  # Store the adjustment for the segment
        d2.append((w[i] + d1[-1]) * -1)  # Compute second adjustment for cumulative effect
    print(" ".join(map(str, d1)))
    print(1, n)
    print(" ".join(map(str, d2)))


# https://github.com/VaHiX/CodeForces/