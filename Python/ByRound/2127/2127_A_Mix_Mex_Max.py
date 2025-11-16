# Problem: CF 2127 A - Mix Mex Max
# https://codeforces.com/contest/2127/problem/A

"""
Problem: A. Mix Mex Max

Purpose:
This code determines whether an array of non-negative integers (with some -1 representing missing values) 
can be made "good" by replacing -1s with non-negative integers. An array is good if for every triplet 
of consecutive elements, the MEX of the triplet equals the difference between the maximum and minimum 
of the triplet.

Algorithms/Techniques:
- Set operations to identify unique values
- MEX calculation (minimum excluded non-negative integer)
- Logic checking based on constraints

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) due to storing set of unique elements.

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: length of array n (3 <= n <= 100)
  - Second line: n integers, each in range [-1, 100]

Output Format:
- "YES" if the array can be made good, otherwise "NO"
"""

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    s = list(set(a))  # Get unique values from the array
    if -1 in s:
        s.remove(-1)  # Remove -1 since it's a placeholder for missing value
    
    # If there are multiple distinct values or zero is present,
    # then it's impossible to make all triplets satisfy the condition
    if 0 in s or len(s) > 1:
        print("No")
    else:
        print("Yes")


# https://github.com/VaHiX/codeForces/