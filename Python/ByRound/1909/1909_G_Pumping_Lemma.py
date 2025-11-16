# Problem: CF 1909 G - Pumping Lemma
# https://codeforces.com/contest/1909/problem/G

"""
Purpose: Count the number of valid triples (x, y, z) such that s = x + y + z and t = x + y^k + z for some k >= 0.
Algorithms/Techniques: 
- Two pointers to find matching prefix and suffix of s and t
- Iterate over possible lengths of repeated substring y and check compatibility
Time Complexity: O(n + m)
Space Complexity: O(1)

"""

import sys

n, m = map(int, sys.stdin.readline().split())
s = sys.stdin.readline().strip()
t = sys.stdin.readline().strip()

l = 0
r = 0
ans = 0

# Find the longest prefix of s that matches prefix of t
while l < n and s[l] == t[l]:
    l += 1

# Find the longest suffix of s that matches suffix of t
while r < n and s[n - 1 - r] == t[m - 1 - r]:
    r += 1

# Iterate through possible lengths of repeated substring y
# i represents the length of y
for i in range(1, l + r - n + 1):
    # Check if the remaining part of t after accounting for prefix and suffix can be split into k copies of y
    # and that the prefix and suffix parts match correctly
    if (m - n) % i == 0 and t[l - i : l] == t[l : l + i]:
        # Add the count of valid configurations for this length of y
        ans += l + r - n - i + 1

print(ans)


# https://github.com/VaHiX/CodeForces/