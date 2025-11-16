# Problem: CF 1603 A - Di-visible Confusion
# https://codeforces.com/contest/1603/problem/A

"""
Problem: Di-visible Confusion

Purpose:
This code determines whether a given sequence can be completely erased by repeatedly removing elements that are not divisible by their 1-indexed position + 1.

Algorithm:
- Precompute a sequence f where each element is the LCM of all previous elements and (i+3), starting with f[0] = 2.
- For each test case, check if any element in the input array is divisible by its corresponding precomputed value in f.
- If any such element exists, the sequence cannot be completely erased.

Time Complexity: O(1) for precomputation + O(n) for each query, where n is the length of the input sequence.
Space Complexity: O(1) for precomputation + O(n) for input storage.

Techniques:
- Precomputed LCM sequence generation
- Modular arithmetic checking
"""

import sys

input = sys.stdin.buffer.readline
from math import gcd


def lcm(x, y):
    return x * y // gcd(x, y)


f = [2]  # Precompute LCMs; f[i] is the LCM of (2, 3, ..., i+2)
for i in range(30):  # Generate up to 30 elements for sufficiently large values
    if f[-1] > 10**9:
        break
    f.append(lcm(f[-1], i + 3))  # Build next LCM with (i + 3)

for _ in range(int(input())):  # Process test cases
    n = int(input())  # Read sequence length
    a = list(map(int, input().split()))  # Read sequence elements
    ok = True  # Flag to determine if sequence can be erased
    for i in range(min(n, len(f))):  # Check first min(n, len(f)) elements
        if a[i] % f[i] == 0:  # If divisible by precomputed value
            ok = False  # Sequence cannot be erased
    print("YES" if ok else "NO")  # Output result


# https://github.com/VaHiX/codeForces/