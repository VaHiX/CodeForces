# Problem: CF 2081 B - Balancing
# https://codeforces.com/contest/2081/problem/B

"""
B. Balancing
Algorithms/Techniques: Greedy, Segment Analysis

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1) excluding input storage.

The problem asks to make an array strictly increasing with minimum operations.
Each operation allows replacing a contiguous subarray with any values maintaining
the relative order (i.e., if original was increasing, replacement must also be increasing,
and similarly for decreasing). 

This is solved by:
1. Identifying all decreasing segments.
2. Counting how many operations are needed to fix these segments,
   considering that some adjustments can be made in one operation if they
   connect well.

The approach tracks the first and last positions of decreasing segments,
and calculates minimal operations accordingly.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main():
    n = int(input())
    arr = list(map(int, input().split()))
    dec = 0  # Count of decreasing transitions
    first = -1  # First index of a decreasing segment
    last = -1  # Last index of a decreasing segment
    for i in range(n - 1):
        if arr[i] > arr[i + 1]:  # If current element is greater than next
            dec += 1  # Increment decreasing count
            if first < 0:
                first = i  # Mark the start of the segment
            last = i + 1  # Update end index of the segment
    if dec == 0:  # No decreasing transitions, already strictly increasing
        print(0)
        return
    ans = 0
    # Check if the range [first, last] can be fixed with one operation
    # If the difference between values is smaller than the length of subarray,
    # we can reduce the number of operations needed.
    if arr[last] - arr[first] < last - first:
        ans += 1  # We use one operation for this specific case
        dec -= 1  # Reduce count since it's absorbed into one operation
    # Add remaining operations required (greedily grouped)
    ans += (dec - 1) // 2 + 1
    print(ans)


T = int(input())
t = 1
while t <= T:
    main()
    t += 1


# https://github.com/VaHiX/codeForces/