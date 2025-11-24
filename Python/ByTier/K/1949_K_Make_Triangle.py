# Problem: CF 1949 K - Make Triangle
# https://codeforces.com/contest/1949/problem/K

"""
Algorithm: Greedy with Prefix Sum
Time Complexity: O(N log N) due to sorting, where N is the number of elements
Space Complexity: O(N) for storing the input array and prefix sums

This solution attempts to distribute elements into three groups such that their sums can form a triangle.
It uses a greedy approach where elements are sorted in descending order, and for each element,
we try to place it in a group that still has capacity and results in a valid triangle sum.
A valid triangle satisfies the triangle inequality: for sides a, b, c, we need a + b > c, a + c > b, b + c > a.
We use prefix sums to efficiently check if placing the current element would lead to a sum that can participate in a valid triangle.
"""

import sys

input = lambda: sys.stdin.readline().strip()
t = int(input())
for _ in range(t):
    N, *n = map(int, input().split())
    a = [*map(int, input().split())]
    group = [[n[i], 0] for i in range(3)]
    ans = [[] for i in range(3)]
    a.sort()
    p = a[:] + [0, 0, 0]
    for i in range(1, N):
        p[i] += p[i - 1]
    S = (sum(a) + 1) // 2
    check = True
    for i in range(N - 1, -1, -1):
        tmp = False
        for j in range(3):
            if group[j][0] == 0:
                continue
            if group[j][1] + a[i] + p[group[j][0] - 2] >= S:
                continue
            group[j][0] -= 1
            group[j][1] += a[i]
            ans[j].append(a[i])
            tmp = True
            break
        if not tmp:
            check = False
            break
    if check:
        print("YES")
        for i in range(3):
            print(*ans[i])
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/