# Problem: CF 1479 A - Searching Local Minimum
# https://codeforces.com/contest/1479/problem/A

"""
Algorithm: Binary Search for Local Minimum
Purpose: Find any index k in a permutation array such that a[k] is a local minimum,
         i.e., a[k] < min(a[k-1], a[k+1]), where out-of-bounds elements are considered +∞.

Techniques:
- Binary search on the array indices to efficiently locate a local minimum.
- At each step, query two adjacent elements and compare them to decide which half to explore next.

Time Complexity: O(log n) - Binary search over n elements.
Space Complexity: O(1) - Only using a constant amount of extra space (variables l, r, m).

Note: This approach relies on the fact that in any permutation, there must exist at least one local minimum.
The key insight is that we can use the comparison of adjacent elements to determine which side of the array
to continue searching for a local minimum.
"""

n = int(input())
t = [0] * n
l, r = 0, n
while r - l > 1:
    m = (l + r) // 2
    print("?", m)
    x = int(input())
    print("?", m + 1)
    y = int(input())
    if x < y:  # If left element is smaller than right, a local minimum lies to the left (including m)
        r = m
    else:      # Else, the local minimum lies to the right (including m + 1)
        l = m
print("!", r)  # r now points to a local minimum index


# https://github.com/VaHiX/CodeForces/