# Problem: CF 1765 B - Broken Keyboard
# https://codeforces.com/contest/1765/problem/B

"""
Algorithm: Broken Keyboard
Technique: String manipulation and pattern matching

Time Complexity: O(n), where n is the length of the string s. We perform a constant number of operations per test case.
Space Complexity: O(1), as we use only a constant amount of extra space regardless of input size.

The approach is based on observing the keyboard pattern:
- Presses alternate between 1 and 2 letters.
- The pattern repeats every 3 presses: 1, 2, 1, 2, ...
- For a valid string, if we split the string into groups of 3 characters,
  the second and third characters of each group must be the same.
  Also, the length of the input string cannot be 2 modulo 3.
"""

for _ in range(int(input())):
    n, s = int(input()), input()
    # Check if the length is valid (not 2 mod 3) and if the pattern holds
    # s[1::3] gets every 3rd character starting from index 1
    # s[2::3] gets every 3rd character starting from index 2
    # If they are equal, the pattern is consistent
    print("YES" if n % 3 != 2 and s[1::3] == s[2::3] else "NO")


# https://github.com/VaHiX/CodeForces/