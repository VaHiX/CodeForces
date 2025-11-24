# Problem: CF 2049 A - MEX Destruction
# https://codeforces.com/contest/2049/problem/A

"""
Problem: A. MEX Destruction

Purpose:
This code solves the problem of finding the minimum number of operations to reduce an array of non-negative integers to all zeros using MEX operations on subarrays.

Algorithms/Techniques:
- Greedy approach based on identifying segments of the array that need to be processed.
- The MEX operation replaces a subarray with the smallest non-negative integer not present in that subarray.
- Key insight: Each contiguous segment of unique elements (starting from 0) needs at least one operation unless it's already all zeros.

Time Complexity:
O(n) per test case, where n is the length of the array. We process each element once in the main loop.

Space Complexity:
O(1) extra space excluding input storage.

"""

t = int(input())
for _ in range(t):
    num, arr = int(input()), input().strip("0 ").split()
    if "0" in arr:  # If any zero exists in the array
        print(2)   # At least 2 operations needed to get all zeros
    elif arr:      # If no zero but array is not empty
        print(1)   # One operation to make whole array zero (e.g., [1,2,3] -> [0])
    else:          # Empty array means already all zeros
        print(0)


# https://github.com/VaHiX/codeForces/