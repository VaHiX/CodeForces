# Problem: CF 1976 A - Verify Password
# https://codeforces.com/contest/1976/problem/A

"""
Password Verification Algorithm

Algorithm/Techniques:
- The solution checks if the password satisfies the conditions of a strong password.
- It verifies that all letters and digits are sorted in non-decreasing order.
- The core idea is to ensure that the password is sorted globally, meaning that
  the sequence of characters is non-decreasing overall.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the characters in a list

This approach works because if we sort the password and it matches the original,
then all characters are in non-decreasing order, which satisfies both:
1. All digits are sorted in non-decreasing order
2. All letters are sorted in non-decreasing order
3. No digit comes after a letter (because sorting enforces this)
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def solution(n, a):
    # Check if the password is sorted in non-decreasing order
    return "YES" if sorted(a) == a else "NO"


ans = []
for _ in range(int(input())):
    n = int(input())
    # Read the password as a list of characters
    a = [i for i in input().rstrip()]
    ans.append(solution(n, a))
# Output all results at once
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/