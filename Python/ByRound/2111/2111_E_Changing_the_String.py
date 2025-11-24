# Problem: CF 2111 E - Changing the String
# https://codeforces.com/contest/2111/problem/E

"""
E. Changing the String

Problem Summary:
Given a string s of length n consisting only of 'a', 'b', 'c', and q operations,
each operation specifies that we can change all occurrences of character x to y (if x exists).
Goal is to make the resulting string lexicographically minimal.
We process operations in order, applying them where beneficial to minimize result.

Approach:
- Use greedy strategy with precomputed counts of possible transitions
- Maintain counters for key pairs: s10, s20, s12, s21, s120, s210
- Process string left-to-right and apply operations greedily to reduce characters to earlier letters in alphabet
- Time Complexity: O(n + q)
  Each character is processed once, operations are handled in constant time per pair.
Space Complexity: O(1)
  Only a fixed-size array of counters is used regardless of input size.

Algorithms/Techniques:
Greedy algorithm with precomputed transition counts; string manipulation and character mapping
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
oa = ord("a")


def solve646():
    n, k = map(int, input().split())
    a = [ord(x) - oa for x in input()]  # Convert to 0-based index for 'a','b','c'
    s20, s12, s21, s10 = [0] * 4  # Counters for transitions: 2->0, 1->2, 2->1, 1->0
    s120 = s210 = 0  # Special counters tracking sequences of 1->2->0 or 2->1->0
    for i in range(k):
        x, y = input().split()
        x, y = ord(x) - oa, ord(y) - oa  # Convert chars to indices
        if x == y or x == 0:
            continue  # Skip if no change needed or x is 'a'
        if x == 1 and y == 0:
            s10 += 1  # Record transition 1->0
            s210 = min(s210 + 1, s21)  # Adjust if we can form a 2->1->0 sequence
        if x == 2 and y == 0:
            s20 += 1  # Record transition 2->0
            s120 = min(s120 + 1, s12)  # Adjust if we can form a 1->2->0 sequence
        if x == 1 and y == 2:
            s12 += 1  # Record transition 1->2
        if x == 2 and y == 1:
            s21 += 1  # Record transition 2->1
    for i, x in enumerate(a):
        if x == 0:
            continue  # Already 'a'
        if x == 1:
            if s10:  # Prefer direct 1->0 if available
                s10 -= 1
                a[i] = 0
            elif s120 and s20 and s12:  # Use 1->2->0 path if possible
                s120 -= 1
                s20 -= 1
                s12 -= 1
                a[i] = 0
            continue
        if s20:  # Try to convert 2->0 directly
            s20 -= 1
            a[i] = 0
            continue
        if s21:  # Convert 2->1, then possibly 1->0 if possible later
            s21 -= 1
            a[i] = 1
            if s210 and s10:
                s10 -= 1
                s210 -= 1
                a[i] = 0
    b = [chr(x + oa) for x in a]  # Convert back to characters
    return "".join(b)


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(res_test))


# https://github.com/VaHiX/codeForces/