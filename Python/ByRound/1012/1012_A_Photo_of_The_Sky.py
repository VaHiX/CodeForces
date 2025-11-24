# Problem: CF 1012 A - Photo of The Sky
# https://codeforces.com/contest/1012/problem/A

"""
Problem: Photo of The Sky

Given 2*n integers representing coordinates of n stars in a photo, determine the minimal area 
of a rectangle with sides parallel to axes that could contain all points.

Approach:
- Sort the coordinates to facilitate pairing
- Try all valid ways to split sorted coordinates into x and y components
- For each valid split, compute rectangle area and track minimum

Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) additional space (excluding input)
"""

import sys

input = sys.stdin.buffer.readline


def process(A):
    n = len(A)
    A.sort()
    # Take the first and last elements as x1, x2 and y1, y2 for initial case
    x1, x2, y1, y2 = A[0], A[n // 2 - 1], A[n // 2], A[n - 1]
    answer = (x2 - x1) * (y2 - y1)
    
    # Try different ways to pair coordinates into x and y values
    for i in range(n):
        # Ensure valid indices for pairing
        if 0 < i <= i + n // 2 - 1 < n - 1:
            x1 = A[0]
            x2 = A[n - 1]
            y1 = A[i]
            y2 = A[i + n // 2 - 1]
            # Compute area and update minimum
            answer = min(answer, (y2 - y1) * (x2 - x1))
    
    sys.stdout.write(f"{answer}\n")
    return


n = int(input())
A = [int(x) for x in input().split()]
process(A)


# https://github.com/VaHiX/codeForces/