# Problem: CF 2057 C - Trip to the Olympiad
# https://codeforces.com/contest/2057/problem/C

"""
Purpose: To find three distinct integers a, b, c in range [l, r] that maximize the expression (a⊕b)+(b⊕c)+(a⊕c),
where ⊕ is the XOR operation.

Algorithm:
- The key idea is to maximize XOR values between pairs of numbers.
- We determine the highest bit position where l and r differ.
- Using this bit position, we construct three numbers such that their pairwise XORs are maximized.
- The construction involves:
    1. Finding a number `a` that is just below or equal to `r` but with the highest possible differing bits set.
    2. Setting `b` as `a + 1`.
    3. Setting `c` as either `l` or `r`, depending on whether `a` or `b` equals `r`.

Time Complexity: O(1) - Constant time due to fixed bit-length operations.
Space Complexity: O(1) - Only using a constant amount of extra space.
"""

from sys import stdin, stdout

input = stdin.readline

for _ in range(int(input())):
    l, r = map(int, input().split())
    # Determine the bit position where l and r first differ, starting from the highest bit.
    k = (l ^ r).bit_length() - 1
    # Construct 'a' by setting all bits up to k to 1, starting from l
    a = l | ((1 << k) - 1)
    # Increment a to get b (this ensures b differs from a at the k-th bit)
    b = a + 1
    # Choose c such that it's either l or r, avoiding conflict if a or b is r
    c = l if a == r or b == r else r
    stdout.write(f"{a } {b } {c } \n")


# https://github.com/VaHiX/CodeForces/