# Problem: CF 1882 B - Sets and Union
# https://codeforces.com/contest/1882/problem/B

"""
Purpose: This program finds the maximum number of elements in an attainable set S such that S is not equal to the union of all given sets S1, S2, ..., Sn.

Algorithm:
- For each element in the universal set (union of all sets), determine how many sets do NOT contain this element.
- Compute the union of all sets that do not contain the current element.
- The size of this union represents a possible attainable set that excludes at least one element from the total union.
- The maximum such size is the answer.

Time Complexity: O(n * m) where n is number of sets and m is average size of each set.
Space Complexity: O(m) where m is the total number of unique elements across all sets.

Note: A key insight is that we're looking for the maximum size of a union of subsets that is strictly less than the full union.
"""

n = int(input())
for _ in range(n):
    nn = int(input())
    k = [0] * nn
    s = [0 for __ in range(nn)]
    sall = set()  # Union of all sets
    for i in range(nn):
        k_l = list(map(int, input().split()))
        k[i] = k_l[0]
        s[i] = set(k_l[1:])
        sall = sall.union(s[i])
    lenall = len(sall)
    ans = 0
    fp = 0
    for x in sall:
        temps = set()  # Union of all sets that do NOT contain x
        for xs in s:
            if x not in xs:
                temps = temps.union(xs)
        lentemp = len(temps)
        if lentemp == lenall - 1:
            print(lenall - 1)
            fp = 1
            break
        ans = max(ans, lentemp)
    if fp == 0:
        print(ans)


# https://github.com/VaHiX/CodeForces/