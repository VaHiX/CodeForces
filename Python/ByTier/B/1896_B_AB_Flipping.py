# Problem: CF 1896 B - AB Flipping
# https://codeforces.com/contest/1896/problem/B

"""
Algorithm/Technique: String manipulation and counting
Time Complexity: O(n), where n is the length of the string s
Space Complexity: O(n), due to string operations like lstrip and rstrip

The solution works by:
1. Stripping all leading 'B's from the string.
2. Stripping all trailing 'A's from the remaining string.
3. Counting the number of characters between these stripped parts.
4. Subtracting 1 to get the maximum number of operations possible.

This approach effectively counts the number of 'A' characters that can be "moved" to the right
and 'B' characters that can be "moved" to the left, as long as they are not at the ends.
"""

for s in [*open(0)][2::2]:
    print(len(s.lstrip("B").rstrip("A\n") or "*") - 1)


# https://github.com/VaHiX/CodeForces/