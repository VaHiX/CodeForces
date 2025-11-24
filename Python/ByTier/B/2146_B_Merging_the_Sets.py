# Problem: CF 2146 B - Merging the Sets
# https://codeforces.com/contest/2146/problem/B

"""
B. Merging the Sets

Purpose:
This code determines whether there exist at least three different ways to choose subsets from a given collection of sets such that every integer from 1 to m is covered by at least one chosen set.

Algorithm:
1. For each test case, we maintain a count array `cnt` to track how many sets contain each element.
2. We then iterate through all sets and for each set, check if removing it still leaves enough coverage of elements.
3. The core idea uses inclusion-exclusion principles implicitly: for each set, we temporarily remove it from counting,
   compute whether all elements are still covered, then add the set back.
4. If a set can be removed without losing coverage (good = true), we increment ans.
5. Finally, if ans > 1, we return YES; else NO.
   
Time Complexity: O(n * m + L) where L is the total number of elements across all sets.
Space Complexity: O(m + n)

Techniques:
- Two-pass counting
- Greedy-like validation
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n, m = map(int, input().split())
    cnt = [0] * (m + 1)
    sets = []
    for _ in range(n):
        _, *s = map(int, input().split())
        sets.append(s)
        for x in s:
            cnt[x] += 1
    if 0 in cnt[1:]:  # If any element is not covered by any set
        print("NO")
        continue
    ans = 0
    for i in range(n):
        good = True
        for x in sets[i]:
            cnt[x] -= 1  # Temporarily remove the current set's elements
            good &= cnt[x] > 0  # Check if all elements are still covered
        for x in sets[i]:
            cnt[x] += 1  # Restore counts
        ans += good  # If removing this set preserves full coverage, increment counter
    print("YES" if ans > 1 else "NO")


# https://github.com/VaHiX/CodeForces/