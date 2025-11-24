# Problem: CF 2090 E1 - Canteen (Easy Version)
# https://codeforces.com/contest/2090/problem/E1

"""
E1. Canteen (Easy Version)

Algorithm: 
- Simulate the process of rounds until all elements in 'a' become 0.
- Use a sliding window technique with a stack to efficiently compute the maximum consecutive rounds possible.
- Time complexity: O(n) per test case, where n is the length of arrays a and b.
- Space complexity: O(n), for storing extended arrays and the stack.

The solution uses a modified algorithm that simulates rounds of operations.
It extends arrays 'a' and 'b' to double their size to handle circular nature (for shift operation).
A sliding window approach with a stack stores deficits in 'b[i] - a[i]' to compute how many rounds can be skipped.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def solve646():
    n, k = map(int, input().split())  # Read n and k, k is always 0 in this version
    a = list(map(int, input().split()))  # Read array a
    b = list(map(int, input().split()))  # Read array b
    a = a + a  # Extend a to handle circular shifts
    b = b + b  # Extend b to handle circular shifts
    i = res = 0  # i is the current index, res stores maximum rounds
    while i < n:
        if a[i] > b[i]:   # If a[i] > b[i], we start a new potential round sequence
            s = []  # Stack to store deficits (b[j] - a[j])
            c, j = 0, i  # c accumulates deficit, j is the current index in extended arrays
            while j < 2 * n:  # Go through the extended arrays
                c = b[j] - a[j]  # Compute deficit or surplus
                if c < 0:
                    s.append(c)  # Store deficits
                else:
                    # Try to consume previous deficits with current surplus
                    while s and c + s[-1] >= 0:
                        c += s.pop()
                    if not s:  # If no more deficits to consume, break
                        break
                    s[-1] += c  # Add current surplus to last deficit
                j += 1  # Move to next element
            res = max(res, j - i)  # Update maximum rounds
            i = j  # Skip processed elements
        else:
            i += 1  # Move to next element if a[i] <= b[i]
    return res + 1  # Return total rounds (add 1 because we start counting from 0)


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/codeForces/