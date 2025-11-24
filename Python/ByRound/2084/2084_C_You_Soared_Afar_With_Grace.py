# Problem: CF 2084 C - You Soared Afar With Grace
# https://codeforces.com/contest/2084/problem/C

"""
C. You Soared Afar With Grace

Given two permutations a and b of length n, determine whether we can make a and b 
reverse each other (i.e., a[i] == b[n-1-i]) using at most n swaps of elements in both arrays.

We can swap any two indices i and j in both arrays simultaneously:
a[i] <-> a[j], b[i] <-> b[j].

Approach:
1. If n is odd, check if any index has a[i] == b[i]. If so, we must ensure it's at center (n//2),
   otherwise impossible.
2. Otherwise, process pairs and attempt to align elements such that result becomes reverse.
3. Use position tracking for faster lookup during swaps.

Time Complexity: O(n) amortized over all test cases due to total sum of n being bounded.
Space Complexity: O(n) for storing positions and answer list.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n = int(input())
    a = list(map(lambda x: int(x) - 1, input().split()))  # Convert to 0-based indexing
    b = list(map(lambda x: int(x) - 1, input().split()))
    ans = []
    
    # Handle odd length case
    if n & 1:
        i = next((i for i in range(n) if a[i] == b[i]), None)
        if i is None:
            print(-1)
            return
        j = n // 2
        if i != j:
            # Swap elements at positions i and j to get the matching element to center
            a[i], a[j] = a[j], a[i]
            b[i], b[j] = b[j], b[i]
            ans += [(i + 1, j + 1)]  # Convert back to 1-based indexing

    # Position array to quickly find index of each value in 'a'
    pos = [0] * n
    for i, x in enumerate(a):
        pos[x] = i
    
    # Process pairs from outside in
    for k in range(n // 2):
        if a[k] == b[k]:
            print(-1)
            return
        i = pos[b[k]]
        # Check if current alignment is valid for reversal condition
        if b[i] != a[k]:
            print(-1)
            return
        j = n - 1 - k
        if i == j:
            continue
        # Perform the required swap on both arrays and update position tracking
        pos[a[i]], pos[a[j]] = j, i
        a[i], a[j] = a[j], a[i]
        b[i], b[j] = b[j], b[i]
        ans += [(i + 1, j + 1)]

    print(len(ans))
    for swap in ans:
        print(f"{swap[0]} {swap[1]}")


for _ in range(int(input())):
    solve_case()


# https://github.com/VaHiX/codeForces/