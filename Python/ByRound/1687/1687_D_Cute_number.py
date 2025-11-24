# Problem: CF 1687 D - Cute number
# https://codeforces.com/contest/1687/problem/D

"""
Algorithm: 
- The problem involves finding the smallest non-negative integer k such that for all elements in the array a, a[i] + k is a "cute" number.
- A number x is cute if: x - g(x) < f(x) - x, where:
  - f(x): minimal square number strictly greater than x
  - g(x): maximal square number less than or equal to x
- Key idea:
  - Preprocess the input array to compute differences and group indices by difference values.
  - Use binary search or iteration to find the minimal k such that all transformed elements are cute.
  - For each candidate k, evaluate the constraints using square roots and check validity.
  - Maintain linked lists to efficiently track segments of the array.

Time Complexity: O(n * sqrt(max_a)) where max_a is the maximum value in array a.
Space Complexity: O(n) for storing the array and auxiliary structures.
"""

from collections import defaultdict
from math import ceil, sqrt


def run():
    n = int(input())
    a = [int(x) for x in input().split()]

    # Group indices by difference between consecutive elements
    d = defaultdict(list)
    for i in range(1, n):
        d[a[i] - a[i - 1]].append(i)

    # Initialize linked list structures for tracking segments
    h = [i - 1 for i in range(n + 1)]  # head pointers
    t = [i + 1 for i in range(n + 1)]  # tail pointers

    # Update function to merge segments
    def update(i):
        for j in d[i]:
            t[h[j]] = t[j]  # Update tail of previous segment
            h[t[j]] = h[j]  # Update head of next segment

    i = 0
    while True:
        update(i)
        s = i * i - a[0]  # Compute shift amount based on current square i*i
        x = 0
        y = s + i
        l = 0
        while l < n:
            # Calculate approximate j such that j(j+1) >= 2*(a[l] + s)
            j = ceil((-1 + sqrt(1 + 4 * (a[l] + s))) / 2)
            # Update x and y to track bounds for validity
            x = max(x, j * j - a[l])
            y = min(y, j * (j + 1) - a[t[l] - 1])
            if y < x:
                break  # Invalid condition, break inner loop
            l = t[l]  # Move to next segment
        else:
            break  # Successfully validated k
        i += 1  # Try next possible square
    print(x)  # Output the minimal k


run()


# https://github.com/VaHiX/CodeForces/