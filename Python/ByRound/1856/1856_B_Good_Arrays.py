# Problem: CF 1856 B - Good Arrays
# https://codeforces.com/contest/1856/problem/B

"""
Code Purpose:
This code determines whether a "good array" exists for a given array of positive integers.
A good array is defined as:
1. Each element in the good array is not equal to the corresponding element in the input array.
2. The sum of elements in the good array equals the sum of elements in the input array.

Algorithm:
1. For each test case, read the input array.
2. Calculate the total sum of the input array.
3. Determine if we can construct a good array by:
   - Counting the number of 1s in the input array.
   - Checking if the total sum is greater than the count of 1s.
   - If so, a good array can be constructed; otherwise, it cannot.

Time Complexity: O(n) where n is the length of the input array (for each test case).
Space Complexity: O(1) excluding input storage, as we only use a constant amount of extra space.

Techniques:
- Efficient use of string operations to read input and compare arrays.
- Mathematical analysis to determine existence of good array.
"""

for s in [*open(0)][2::2]:
    print("NYOE S"[1 < len(a := s.split()) <= sum(map(int, a)) - a.count("1") :: 2])


# https://github.com/VaHiX/CodeForces/