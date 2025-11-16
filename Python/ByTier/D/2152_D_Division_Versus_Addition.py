# Problem: CF 2152 D - Division Versus Addition
# https://codeforces.com/contest/2152/problem/D

"""
D. Division Versus Addition

Algorithm:
- For each element in the array, compute how many times it can be divided by 2 before reaching 1.
- The number of operations for one element equals the number of bits in its binary representation minus 1 (i.e., floor(log2(x))).
- We use prefix sums and a counter to efficiently answer range queries.

Time Complexity:
- Preprocessing: O(n) per test case
- Each query: O(1)

Space Complexity:
- O(n) for the auxiliary arrays

Techniques:
- Bit manipulation via logarithms
- Prefix sum technique
- Range query optimization

"""

t = int(input())
import math

for _ in range(t):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))

    def fun(n):
        if n == 2:
            return 1
        k = math.log2(n - 2)
        return math.floor(k) + 1

    # c[i] counts the number of elements from index 0 to i that have different values in fun(x) and fun(x+1)
    c = [0] * n
    if fun(a[0]) != fun(a[0] + 1):
        c[0] = 1
    else:
        c[0] = 0
    a[0] = fun(a[0])
    
    # Build prefix sum of transformed values and update counter array
    for i in range(1, n):
        c[i] = c[i - 1]
        if fun(a[i]) != fun(a[i] + 1):
            c[i] += 1
        a[i] = fun(a[i]) + a[i - 1]

    # Process queries
    for _ in range(q):
        l, r = map(int, input().split())
        l = l - 1
        r = r - 1
        if l == 0:
            print(a[r] + (c[r] // 2))
        else:
            print(a[r] - a[l - 1] + (c[r] - c[l - 1]) // 2)


# https://github.com/VaHiX/CodeForces/