# Problem: CF 1641 A - Great Sequence
# https://codeforces.com/contest/1641/problem/A

"""
Problem: Make a sequence "great" for a given integer x by adding minimum numbers.
A sequence is great if it can be split into pairs where first * x = second.
Algorithm:
    - Count frequency of each number.
    - For each number z, check if z*x exists in the map.
    - If both exist, form min(freq[z], freq[z*x]) pairs, reduce counts.
    - The answer is total elements minus twice the number of pairs formed.

Time Complexity: O(n * log n) due to sorting and hashmap operations
Space Complexity: O(n) for storing frequencies
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, x = list(map(int, input().split()))
    a = list(map(int, input().split()))
    d = {}
    a.sort()  # Sort to process elements in order (not strictly necessary but helps)
    c = 0
    for el in a:
        if el not in d:
            d[el] = 1
        else:
            d[el] += 1
    for z in d:
        if z * x in d:
            p, q = d[z], d[z * x]
            c += min(p, q)
            d[z] -= min(p, q)
            d[z * x] -= min(p, q)
    print(n - (c * 2))


# https://github.com/VaHiX/codeForces/