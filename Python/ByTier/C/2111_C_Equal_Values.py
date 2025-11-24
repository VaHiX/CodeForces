# Problem: CF 2111 C - Equal Values
# https://codeforces.com/contest/2111/problem/C

"""
C. Equal Values
Algorithms/Techniques: Two-pointer technique with prefix/suffix optimization

Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to make all elements of the array equal using two types of operations:
1. Set all elements to the left of index i equal to a[i], cost = (i-1)*a[i]
2. Set all elements to the right of index i equal to a[i], cost = (n-i)*a[i]

We use a two-pointer approach where we track the current segment of equal elements.
For each segment, we compute the minimum cost to make all elements equal to that value
by considering both left and right operations.

The key insight is to iterate from left to right and maintain a pointer l indicating 
the start of the current segment. When we encounter a different value at r, we update l.
We compute the minimal cost for making the entire array equal by considering:
- Cost if we merge everything to the left
- Cost if we merge everything to the right

This is optimized using the fact that when elements are equal, we can directly use 
a[i] * (n - r + l - 1) which effectively computes the cost of making all elements 
equal to a[l], using a sliding window and tracking segments.

"""

for _ in range(int(input())):
    n = int(input())
    arr = [int(x) for x in input().split()]
    res = float("inf")
    l = 0
    for r in range(n):
        # If current element is different from the start of segment,
        # update the start pointer to current position
        if arr[r] != arr[l]:
            l = r
        # Compute cost using formula derived from optimal merging strategy
        res = min(res, arr[l] * (n - r + l - 1))
    print(res)


# https://github.com/VaHiX/codeForces/