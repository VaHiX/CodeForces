# Problem: CF 2163 D1 - Diadrash (Easy Version)
# https://codeforces.com/contest/2163/problem/D1

"""
Interactive problem to find the maximum MEX among q given ranges in a hidden permutation.

Algorithm:
1. Build a mapping of intervals where each start point maps to the maximum end point
2. For each position, compute the maximum end point reachable from that position
3. Find the position where MEX starts to be 0 using binary search
4. Check for valid MEX values using the good function with binary search

Time Complexity: O(n * log(n) * log(n))
Space Complexity: O(n)

The solution uses binary search to efficiently locate the position where MEX becomes 0,
then uses another binary search to find the maximum valid MEX value.
"""

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
mod = pow(10, 9) + 7


def imap():
    return map(int, input().split())


def ilist():
    return list(map(int, input().split()))


def query(l, r):
    # Check if result already computed
    if d.get((l, r), -1) != -1:
        return d[(l, r)]

    # Make query to the judge
    print(f"? {l } {r }")
    sys.stdout.flush()
    x = int(input())
    d[(l, r)] = x
    return x


def good(x, zero, maximums):
    # Binary search for left boundary where MEX >= x
    left = 1
    right = zero
    while left <= right:
        mid = (left + right) // 2
        if query(mid, n) >= x:
            left = mid + 1
        else:
            right = mid - 1
    l = right

    # Binary search for right boundary where MEX >= x
    left = zero
    right = n

    while left <= right:
        mid = (left + right) // 2
        if query(l, mid) >= x:
            right = mid - 1
        else:
            left = mid + 1
    r = left

    # Check consistency
    return maximums[l] >= r


t = int(input())
for _ in range(t):
    n, q = imap()
    d = {}
    intervals = [0 for i in range(n + 1)]
    maximums = [0 for i in range(n + 1)]
    
    # Process all the intervals
    for i in range(q):
        l, r = imap()
        intervals[l] = max(intervals[l], r)

    # Compute maximum end points
    for i in range(1, n + 1):
        maximums[i] = max(intervals[i], maximums[i - 1])

    # Find the position where MEX first becomes 0
    left = 1
    right = n
    while left <= right:
        mid = (left + right) // 2
        if left == right:
            break

        if query(left, mid):
            right = mid
        else:
            left = mid + 1

    zero = left

    # Binary search for the maximum valid MEX
    left = 0
    right = n

    while left <= right:
        mid = (left + right) // 2
        if good(mid, zero, maximums):
            left = mid + 1
        else:
            right = mid - 1

    # Output the maximum MEX
    print(f"! {max (0 ,right )}")
    sys.stdout.flush()


# https://github.com/VaHiX/CodeForces/