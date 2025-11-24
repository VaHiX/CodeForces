# Problem: CF 1800 E2 - Unforgivable Curse (hard version)
# https://codeforces.com/contest/1800/problem/E2

"""
Algorithm: 
- Check if it's possible to transform string 's' to string 't' using swaps at distance k or k+1.
- First, verify that both strings have the same character frequencies.
- Then, for each position in the string, determine if it's possible to place the required character at that position.
- If a position i has a character that doesn't match the target character, and it's not in a region that can be fixed via swaps, return "NO".

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) since the arrays used have fixed sizes (26 for lowercase letters).
"""
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

oa = ord("a")
m = ord("z") - oa + 1


def solve646():
    n, k = map(int, input().split())
    a = input().rstrip().decode()
    b = input().rstrip().decode()
    s = [0] * n
    ca = [0] * m
    cb = [0] * m
    for i in range(n):
        ca[ord(a[i]) - oa] += 1
        cb[ord(b[i]) - oa] += 1
        # Check if the current position can be affected by swaps of distance k or k+1
        if i >= k or i + k < n:
            s[i] = 1
        else:
            # If the current position is not reachable by swaps and characters don't match, impossible
            if a[i] != b[i]:
                return "NO"
    # If the character frequencies in the two strings do not match, transformation is impossible
    for i in range(m):
        if ca[i] != cb[i]:
            return "NO"
    return "YES"


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())

sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/CodeForces/