# Problem: CF 1971 E - Find the Car
# https://codeforces.com/contest/1971/problem/E

"""
Algorithm: Binary Search + Linear Interpolation

Purpose: 
This program processes multiple test cases to determine the time taken for a car 
to reach a specific point on a number line, given known positions and times at 
intermediate checkpoints. The car moves at a constant speed between consecutive points.

Approach:
1. For each query (point d), find the interval [a[l], a[l+1]] that contains d using binary search.
2. Compute the time to reach d using linear interpolation:
   - Time to reach a[l] is b[l]
   - Speed between a[l] and a[l+1] is (b[l+1] - b[l]) / (a[l+1] - a[l])
   - Time to travel from a[l] to d is (d - a[l]) * speed
   - Total time = b[l] + (d - a[l]) * (b[l+1] - b[l]) / (a[l+1] - a[l])

Time Complexity: O(q * log k) per test case
Space Complexity: O(k) per test case for storing a and b arrays

"""
import sys

input = sys.stdin.readline

ints = lambda: list(map(int, input().split()))

t = int(input())
for _ in range(t):
    n, k, q = ints()
    a = ints()
    b = ints()
    a = [0] + a  # Prepend 0 to a and b for easier index handling
    b = [0] + b

    for _ in range(q):
        d = int(input())

        # Binary search to find the largest index l such that a[l] <= d
        l = 0
        r = len(a) - 1

        while l <= r:
            m = (l + r) // 2
            if a[m] > d:
                r = m - 1
            else:
                l = m + 1
        l -= 1  # l is now the largest index with a[l] <= d

        # Calculate time to reach point d
        ans = b[l]  # Time to reach a[l]
        if l < len(a) - 1:  # If not at the final point
            # Add time to travel from a[l] to d using linear interpolation
            ans += ((d - a[l]) * (b[l + 1] - b[l])) // (a[l + 1] - a[l])
        ans = int(ans)
        print(ans, end=" ", flush=False)
    print()


# https://github.com/VaHiX/CodeForces/