# Problem: CF 872 A - Search for Pretty Integers
# https://codeforces.com/contest/872/problem/A

"""
Problem: Search for Pretty Integers

Algorithm/Techniques:
- Find the minimum digit from each list.
- Generate the two possible smallest numbers by concatenating these digits in both orders.
- Check for any digit that appears in both lists.
- Return the minimum among the smallest concatenated number and the common digit.

Time Complexity: O(n + m) where n and m are the sizes of the two input lists.
Space Complexity: O(1) as we use a fixed-size array of size 10 to store digit frequencies.
"""

import sys

sc = sys.stdin.readline
out = sys.stdout.write
n, x = map(int, sc().rstrip().split())  # Read n and m
arr = list(map(int, sc().rstrip().split()))  # Read first list of digits
arr1 = list(map(int, sc().rstrip().split()))  # Read second list of digits

a = min(arr)  # Find minimum digit in first list
aa = min(arr1)  # Find minimum digit in second list

# Create two concatenations of the minimum digits
s = str(a) + "" + str(aa)  # First order: a then aa
ss = str(aa) + "" + str(a)  # Second order: aa then a
sss = min(int(s), int(ss))  # Minimum of the two possible numbers

# Initialize frequency array for digits 0-9
m = [0] * 10
o = 100000  # Initialize with a large value to find minimum common digit

# Count occurrences of digits in first list
for e in range(n):
    m[arr[e]] += 1

# Count occurrences of digits in second list
for e in range(x):
    m[arr1[e]] += 1

# Check for any digit that exists in both lists (frequency > 1)
for e in range(10):
    if m[e] > 1:
        o = e  # Found a common digit
        break

# Output the smaller of the common digit and the smallest concatenated number
out(str(min(o, sss)))


# https://github.com/VaHiX/CodeForces/