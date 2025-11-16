# Problem: CF 1869 A - Make It Zero
# https://codeforces.com/contest/1869/problem/A

"""
Code Purpose:
This solution addresses the problem of making all elements of an array equal to zero using at most 8 operations. 
Each operation selects a subarray and replaces all its elements with the XOR of the elements in that subarray.
The approach is based on the observation that:
- If the array length n is even, two operations suffice: one to XOR the entire array, and another to XOR the entire array again.
- If the array length n is odd, we use 4 operations:
    1. XOR from index 1 to n-1
    2. XOR from index 1 to n-1 again
    3. XOR from index 2 to n
    4. XOR from index 2 to n again

Algorithms/Techniques:
- Bitwise XOR operation
- Observation-based greedy approach

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1) excluding the input storage.
"""

from sys import stdin

input = stdin.readline
for _ in range(int(input())):
    n = int(input())
    b = input()
    if n % 2:
        print(4)  # For odd n, 4 operations are needed
        print(1, n - 1)  # First operation on all elements except last
        print(1, n - 1)  # Second operation on all elements except last
        print(2, n)      # Third operation on all elements except first
        print(2, n)      # Fourth operation on all elements except first
    else:
        print(2)  # For even n, 2 operations are sufficient
        print(1, n)  # Operation on entire array
        print(1, n)  # Operation on entire array again


# https://github.com/VaHiX/CodeForces/