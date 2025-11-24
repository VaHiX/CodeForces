# Problem: CF 1744 A - Number Replacement
# https://codeforces.com/contest/1744/problem/A

"""
A. Number Replacement
Algorithms/Techniques: Hashing, Simulation

Time Complexity: O(n^2) where n is the length of the array/string due to nested operations in worst case.
Space Complexity: O(1) as we use a fixed-size array of size 51 for mapping numbers to characters.

The solution works by:
1. Creating a mapping from numbers to characters based on the first occurrence in the array.
2. Verifying that each number's assigned character matches the corresponding character in the string.
3. If any mismatch is found, output "NO", otherwise "YES".
"""

import sys

ip = sys.stdin.readline
R = lambda: list(map(int, ip().split()))
for _ in range(int(ip())):
    n = int(ip())
    a = R()
    s = ip()
    res = [0] * (51)  # Array to store mapping from number to character, size 51 for numbers 1-50
    for i in range(n):
        if res[a[i]] == 0:  # If the number hasn't been mapped yet
            res[a[i]] = s[i]  # Map it to the corresponding character
    for i in range(n):
        if res[a[i]] != s[i]:  # Check if current mapping matches string character
            print("NO")
            break
    else:
        print("YES")


# https://github.com/VaHiX/codeForces/