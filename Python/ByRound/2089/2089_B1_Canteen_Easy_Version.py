# Problem: CF 2089 B1 - Canteen (Easy Version)
# https://codeforces.com/contest/2089/problem/B1

"""
B1. Canteen (Easy Version)
Algorithms: Greedy, Sliding Window, Simulation
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

This problem involves simulating a process where elements of two arrays 'a' and 'b' are 
modified in rounds until all elements in array 'a' become zero. In each round:
1. Each element min(a[i], b[i]) is subtracted from both a[i] and b[i].
2. Each element of 'a' is shifted left (c[i] = a[(i-1) % n]).
3. The shifted values are assigned back to 'a'.

The solution uses preprocessing:
- Compute prefix sums of (a[i] - b[i]) to find the optimal rotation point.
- Then simulate rounds using a sliding window approach to efficiently determine 
  maximum number of rounds possible before the process terminates.

Since k=0, no changes can be made to array 'a'.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def solve646():
    n, k = map(int, input().split())  # Read n (size) and k (changes allowed)
    a = list(map(int, input().split()))  # Read array 'a'
    b = list(map(int, input().split()))  # Read array 'b'

    # Compute prefix sums of (a[i] - b[i]) to find where the minimum occurs
    ps = [0] * (n + 1)
    j = 0  # Index of minimum prefix sum
    for i in range(n):
        ps[i] = ps[i - 1] + a[i] - b[i]  # Calculate cumulative difference
        if ps[i] < ps[j]:  # Update index of minimal prefix sum
            j = i

    # Rotate arrays to make minimum prefix sum occur at index 0
    j += 1  # Adjust for 1-based indexing
    a = a[j:] + a[:j]
    b = b[j:] + b[:j]

    i = res = 0  # Initialize pointers and result tracker
    while i < n:
        if a[i] > b[i]:  # If current element in 'a' is greater than in 'b'
            s = []  # Stack for tracking deficits
            c, j = 0, i  # Local variables to track current deficit and position

            # Process elements starting from 'i'
            while j < n:
                c = b[j] - a[j]  # Calculate how much we can take from 'b' vs 'a'

                if c < 0:  # If 'b' has less than 'a', this leads to deficit
                    s.append(c)  # Push deficit onto stack
                else:
                    # If sufficient 'b' exists, try to consume deficits
                    while s and c + s[-1] >= 0:
                        c += s.pop()  # Resolve deficit with current surplus
                    if not s:  # No more deficits to resolve, move on
                        break
                    s[-1] += c  # Add remaining 'c' to last deficit

                j += 1  # Move to next position

            res = max(res, j - i)  # Update the maximum number of steps taken
            i = j  # Jump ahead to avoid recomputation
        else:
            i += 1  # Move to next element if no deficit buildup

    return res + 1  # Return result with one more round for initial state


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/codeForces/