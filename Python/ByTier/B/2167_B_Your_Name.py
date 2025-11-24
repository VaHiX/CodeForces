# Problem: CF 2167 B - Your Name
# https://codeforces.com/contest/2167/problem/B

"""
Problem: Check if string s can be rearranged to form string t.
Algorithm/Technique: Sorting
Time Complexity: O(n log n) per test case, where n is the length of the strings.
Space Complexity: O(n) for storing the sorted characters.

The approach is to sort both strings and compare them. If sorted versions are equal,
then the strings are anagrams of each other, meaning one can be rearranged to form the other.
"""

import sys

data = sys.stdin.read().strip().split()
tests = int(data[0])
index = 1
answers = []

for _ in range(tests):
    n = int(data[index])  # Read the length of the strings
    index += 1
    s, t = data[index], data[index + 1]  # Extract the two strings
    index += 2
    # Compare sorted versions of s and t
    answers.append("YES" if sorted(s) == sorted(t) else "NO")

print("\n".join(answers))


# https://github.com/VaHiX/CodeForces/