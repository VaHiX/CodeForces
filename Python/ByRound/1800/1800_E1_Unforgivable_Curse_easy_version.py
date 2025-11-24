# Problem: CF 1800 E1 - Unforgivable Curse (easy version)
# https://codeforces.com/contest/1800/problem/E1

"""
Purpose: Determine if spell s can be transformed into spell t using swaps at distances k or k+1.
Algorithm:
    1. For each position i, mark reachable positions (i+k and i+k+1) as part of the same component.
    2. For each connected component (positions reachable from each other), count character frequencies in s and t.
    3. If all character frequencies match for each component, return YES; otherwise, return NO.

Time Complexity: O(n) per test case, where n is the length of the strings.
Space Complexity: O(n) for the boolean array v and character frequency arrays.
"""

import sys

T = int(input())

for _ in range(T):
    n, k = map(int, sys.stdin.readline().split())
    s = sys.stdin.readline().rstrip()
    t = sys.stdin.readline().rstrip()
    flag = True

    # v[i] marks whether position i is part of a reachable component
    v = [False] * (n + 1)
    for i in range(n):
        # Mark positions reachable via distance k
        if k + i < n:
            v[k + i] = True
            v[i] = True
        # Mark positions reachable via distance k+1
        if k + i + 1 < n:
            v[k + i + 1] = True
            v[i] = True

    # Frequency arrays for characters in s and t
    alp = [0] * 26
    alp2 = [0] * 26
    for i in range(n):
        # If position i is part of a component, count characters
        if v[i]:
            alp[ord(s[i]) - 97] += 1
            alp2[ord(t[i]) - 97] += 1
        # If not part of a component, characters must match directly
        else:
            if s[i] != t[i]:
                flag = False
                break
    # Check if all character frequencies match
    for i in range(26):
        if alp[i] != alp2[i]:
            flag = False

    if flag:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/