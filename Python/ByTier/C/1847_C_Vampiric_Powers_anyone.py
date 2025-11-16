# Problem: CF 1847 C - Vampiric Powers, anyone?
# https://codeforces.com/contest/1847/problem/C

"""
Algorithm: Vampiric Powers
Purpose: To find the maximum possible strength of a Stand user that can be summoned
         by performing XOR operations on subsequences of the initial array.

Techniques used:
- Prefix XOR calculation to generate all possible XOR values of subarrays
- Set to store unique prefix XORs
- Brute-force comparison of all pairs of prefix XORs to find maximum XOR value

Time Complexity: O(n^2) in worst case due to nested loop for comparing all pairs
Space Complexity: O(n) for storing prefix XORs in a set and list

The key insight is that XOR of subarrays can be computed using prefix XORs:
If prefix_xor[i] = a[0] ^ a[1] ^ ... ^ a[i], then XOR of subarray from index l to r
is prefix_xor[r] ^ prefix_xor[l-1]. We use this idea to compute all possible
XOR values that can be created and find the maximum among them.
"""

import sys

input = sys.stdin.readline
f = lambda: map(int, input().split())

for _ in range(int(input())):
    n = int(input())
    A = list(f())
    temp = 0
    S = set()
    for i in range(n):
        temp ^= A[i]  # Compute prefix XOR
        S.add(temp)   # Add to set of unique prefix XORs
    S = list(S)
    l = len(S)
    ans = max(max(S), max(A))  # Initialize answer with max of original array and prefix XORs
    for i in range(l - 1):
        for j in range(i + 1, l):
            ans = max(ans, S[i] ^ S[j])  # Check all pairwise XORs of prefix XORs
    print(ans)


# https://github.com/VaHiX/CodeForces/