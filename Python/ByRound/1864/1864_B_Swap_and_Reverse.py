# Problem: CF 1864 B - Swap and Reverse
# https://codeforces.com/contest/1864/problem/B

"""
Algorithm: Swap and Reverse
Purpose: To find the lexicographically smallest string achievable by swapping elements at positions i and i+2, and reversing subarrays of length k.
Approach:
    - If k is even, we can rearrange the entire string freely, so sort the string.
    - If k is odd, we can only rearrange characters at even and odd indices separately due to the nature of the operations.
      Even indices can be swapped with other even indices and odd indices can be swapped with other odd indices.
      Then interleave the sorted even and odd indexed characters to form the result.
Time Complexity: O(n log n) due to sorting operations (in worst case)
Space Complexity: O(n) for storing the sorted parts and result
"""

from sys import stdin

input = stdin.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    s = input().strip()
    if k % 2 == 0:
        # If k is even, we can rearrange all characters to form the lexicographically smallest string.
        print("".join(sorted(s)))
    else:
        # If k is odd, we can only freely swap within even indices and odd indices.
        # So sort even and odd indexed characters separately, then interleave them.
        even = sorted(s[::2])  # Characters at even positions (0, 2, 4, ...)
        odd = sorted(s[1::2])  # Characters at odd positions (1, 3, 5, ...)
        s = []
        for i in range(len(odd)):
            s.append(even[i])  # Append character from even index
            s.append(odd[i])   # Append character from odd index
        if len(even) > len(odd):
            s.append(even[-1])  # If even list has extra element, append it at the end
        print("".join(s))


# https://github.com/VaHiX/CodeForces/