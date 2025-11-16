# Problem: CF 1835 B - Lottery
# https://codeforces.com/contest/1835/problem/B

"""
Algorithm: Lottery Problem

This problem involves finding the optimal value for Bytek to choose on his lottery ticket 
to maximize his chance of winning. The lottery selects a target number uniformly from 0 to m, 
and the k closest numbers to the target win. If there's a tie in distance, the person with 
the smaller index wins.

The approach uses binary search and sliding window techniques to determine:
1. The number of target values for which Bytek wins given his optimal choice.
2. The value Bytek should pick to maximize this chance.

Time Complexity: O(n log n + n * max_val) where max_val is bounded by m
Space Complexity: O(1) excluding the input array storage

Techniques:
- Sorting the array of existing ticket values
- Sliding window to identify valid ranges for optimal value selection
- Binary search-like traversal to check all possible values efficiently
"""

import sys

readint = lambda: int(sys.stdin.readline())
readints = lambda: map(int, sys.stdin.readline().split())
readar = lambda: list(map(int, sys.stdin.readline().split()))
flush = lambda: sys.stdout.flush()


def f(n, m, k, ar, x, bl, bh):
    """
    Calculates the number of possible target values for which Bytek wins 
    when choosing value x, given the current sliding window [bl, bh).
    """
    minc = 0
    if bh >= k:
        lim = ar[bh - k]  # Get the k-th closest element to the left of x
        dist = x - lim
        req = (dist // 2) + 1
        minc = lim + req

    maxc = m
    ll = bl + k - 1
    if ll < n:
        lim = ar[ll]  # Get the k-th closest element to the right of x
        dist = lim - x
        req = dist // 2
        maxc = x + req
        if dist % 2 == 0:
            maxc -= 1  # Adjust if the distance is even to avoid over-counting

    return maxc - minc + 1


def solve(n, m, k, ar):
    """
    Main solution function that finds the maximum number of winning targets 
    and the value Bytek should pick to achieve it.
    """
    if k > n:
        # If k exceeds number of participants, all targets are winners
        return m + 1, 0
    
    ans = 0
    lr = 0
    hr = ar.count(0)  # Number of zeros in the sorted array
    best = f(n, m, k, ar, 0, lr, hr)
    x = max(ar[0] - 2, 0)  # Start with a reasonable guess
    
    for i in range(n):
        x = max(x, ar[i] - 2)
        while x <= m:
            # Adjust the left and right pointers according to current candidate x
            while lr != n:
                if x > ar[lr]:
                    lr += 1
                else:
                    break
            while hr != n:
                if x >= ar[hr]:
                    hr += 1
                else:
                    break
            c = f(n, m, k, ar, x, lr, hr)
            if c > best:
                best = c
                ans = x
            if ar[i] + 2 == x:
                break
            x += 1
    return best, ans


# Read input
n, m, k = readints()
ar = readar()
ar.sort()  # Sort the ticket values for efficient processing

# Solve and output result
a, b = solve(n, m, k, ar)
if a >= 0:
    print(a, b)
else:
    print(0, 0)


# https://github.com/VaHiX/CodeForces/