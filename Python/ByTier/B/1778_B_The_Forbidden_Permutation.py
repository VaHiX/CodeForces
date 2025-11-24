# Problem: CF 1778 B - The Forbidden Permutation
# https://codeforces.com/contest/1778/problem/B

"""
Code Purpose:
This code solves the problem of finding the minimum number of adjacent swaps needed to make a given array 'a' good with respect to a permutation 'p' and a distance parameter 'd'. An array is considered good if for all consecutive elements in 'a', the position of the second element in 'p' is either:
1. Greater than the position of the first element, OR
2. Within 'd' positions of the first element (but not less than it).

Key Algorithm Techniques:
- Preprocessing: Store positions of elements in permutation 'p' in an array 'ixs'.
- Check Condition: For each pair of consecutive elements in 'a', verify whether they satisfy the "good" condition.
- Optimization: Compute the minimum number of swaps needed based on how far apart positions are in 'p'.

Time Complexity: O(n + m) per test case, where n is the length of permutation and m is the length of array 'a'.
Space Complexity: O(n) for storing the position array 'ixs' and input arrays.

"""

import sys
from array import array

input = lambda: sys.stdin.buffer.readline().decode().strip()
inp = lambda dtype: [dtype(x) for x in input().split()]
debug = lambda *x: print(*x, file=sys.stderr)
ceil1 = lambda a, b: (a + b - 1) // b
Mint, Mlong, out = 2**31 - 1, 2**63 - 1, []


def check():
    ans = Mint
    # Iterate through consecutive pairs in array 'a'
    for i in range(m - 1):
        # Check if current pair satisfies the "good" condition
        if not ixs[a[i]] < ixs[a[i + 1]] <= ixs[a[i]] + d:
            return 0
        # Calculate the distance between two positions in permutation
        diff = ixs[a[i + 1]] - ixs[a[i]]
        # Track the minimum distance (used to compute minimum swaps)
        ans = min(ans, diff)
        # Also consider the case where we need to move elements towards each other
        if n - 1 > d:
            ans = min(ans, d - diff + 1)

    return ans


for _ in range(int(input())):
    n, m, d = inp(int)
    p = array("i", inp(int))
    a = array("i", inp(int))
    ixs = array("i", [0] * (n + 1))  # pos of each element in permutation

    # Store positions of elements in permutation
    for i in range(n):
        ixs[p[i]] = i
    out.append(check())

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/