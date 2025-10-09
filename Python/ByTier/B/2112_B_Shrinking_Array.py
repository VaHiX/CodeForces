# Problem: CF 2112 B - Shrinking Array
# https://codeforces.com/contest/2112/problem/B

"""
B. Shrinking Array

Purpose:
This code determines the minimum number of operations required to make an array "beautiful".
An array is beautiful if it has at least two elements and there exists a position i such that |b[i] - b[i+1]| <= 1.

Algorithms/Techniques:
- Preprocessing differences between adjacent elements
- Checking conditions based on min/max of differences

Time Complexity: O(n), where n is the length of the array. We iterate through the array once to compute differences and check conditions.
Space Complexity: O(n), for storing the difference array d.

Input:
- t test cases
- For each test case:
  - n (size of array)
  - Array a of n integers

Output:
- Minimum operations to make array beautiful, or -1 if impossible.
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    d = [a[i] - a[i - 1] for i in range(1, n)]  # Compute differences between adjacent elements
    x, y = min(d), max(d)  # Find minimum and maximum of differences
    
    # If any difference is -1, 0, or 1, the array is already beautiful (0 operations)
    if -1 in d or 0 in d or 1 in d:
        print(0)
    # If all differences are either non-positive or non-negative, then it's impossible to make it beautiful
    elif x * y >= 0:
        print(-1)
    # Otherwise, one operation is sufficient to make it beautiful
    else:
        print(1)


# https://github.com/VaHiX/codeForces/