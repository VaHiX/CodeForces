# Problem: CF 1698 D - Fixed Point Guessing
# https://codeforces.com/contest/1698/problem/D

"""
Algorithm: Binary Search on the position of the fixed point
Time Complexity: O(log n) per test case, since we perform binary search on the array indices and each query takes O(n) time to process (but the number of queries is bounded by log n).
Space Complexity: O(1), only using a few variables for tracking indices and processing input/output.

The problem involves finding a fixed point in an array where half of the elements have been swapped in pairs,
and exactly one element remains in its original position. The key insight is that we can use binary search
to locate this fixed point by querying subarrays and checking how many elements of the left half are present.

We maintain a range [l, r] and at each step query the left half of the range. If the count of elements from the left half
in the sorted subarray is odd, the fixed point lies to the left (including mid). Otherwise, it lies to the right.
"""

for t in range(int(input())):
    n = int(input())
    l = 1
    r = n
    while l < r:
        m = l + (r - l) // 2  # Midpoint of the current search range
        print("?", l, m, flush=True)  # Query the left half of the current range
        # Read the sorted subarray and count how many elements are in [l, m]
        sorted_subarray = [int(x) for x in input().split()]
        count = sum(l <= i <= m for i in sorted_subarray)
        if count % 2:  # If count is odd, fixed point is in the left half
            r = m
        else:  # If count is even, fixed point is in the right half
            l = m + 1
    print("!", l, flush=True)  # Output the fixed point


# https://github.com/VaHiX/CodeForces/