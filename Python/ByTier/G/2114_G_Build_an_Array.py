# Problem: CF 2114 G - Build an Array
# https://codeforces.com/contest/2114/problem/G

"""
G. Build an Array

Problem Description:
Given a final array of length n and k operations, determine whether it's possible to construct the array by repeatedly adding elements and merging adjacent equal elements (which sum up). The key insight is that elements that are merged are powers of 2, and their contribution to the total number of operations can be tracked.

Approach:
- For each element in the array, decompose it into its odd part and power-of-2 factor.
- Use prefix and suffix arrays to track how many operations would be needed if we start/stop merging at certain indices.
- The maximum possible contribution of an element to the total count is calculated by considering the best prefix and suffix combinations.
- Time and Space Complexity:
    - Time: O(n) per test case, where n is the length of the array.
    - Space: O(n) for storing auxiliary arrays.

Algorithm:
1. Decompose each number into a power-of-2 factor (b) and an odd part (a).
2. Use two passes to compute prefix (l) and suffix (r) contributions of operations needed for merging.
3. For each element, calculate how it can contribute to total operations in the best way.
4. Compare with k to decide YES or NO.

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n, k = map(int, input().split())
    w = list(map(int, input().split()))
    
    # a stores odd parts of numbers; b stores powers of 2
    a = []
    b = []
    for i in range(n):
        c, x = 0, w[i]
        while x % 2 == 0:
            x //= 2
            c += 1
        a.append(x)
        b.append(2**c)
    
    # l[i] stores prefix sum of operation counts from left
    l = [0] * (n + 1)
    # r[i] stores suffix sum of operation counts from right
    r = [0] * (n + 1)
    
    x, c = a[0], 0
    
    # Compute prefix contribution
    for i in range(n):
        l1 = b[i]
        if a[i] == x and i > 0 and b[i - 1] < b[i]:
            l1 -= 2 * b[i - 1] - 1  # Adjust when merging happens
        if a[i] != x:
            x = a[i]
        l[i] += l[i - 1] + l1
    
    l[n] = l[n - 1]  # Set l[n] to last valid value
    
    x = a[-1]
    
    # Compute suffix contribution
    for i in range(n - 1, -1, -1):
        r1 = b[i]
        if a[i] == x and i < n - 1 and b[i] > b[i + 1]:
            r1 -= 2 * b[i + 1] - 1  # Adjust when merging happens
        if a[i] != x:
            x = a[i]
        r[i] += r[i + 1] + r1
    
    r[-1] = r[0]  # Set r[-1] to first value for correct calculation
    
    # Final check: find maximum possible total contribution of any element
    for i in range(n):
        c = max(c, l[n] - l[i] + r[-1] - r[i] + b[i])
    
    print(["NO", "YES"][c >= k])


# https://github.com/VaHiX/codeForces/