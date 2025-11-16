# Problem: CF 1844 F2 - Min Cost Permutation (Hard Version)
# https://codeforces.com/contest/1844/problem/F2

"""
Algorithm: Min Cost Permutation (Hard Version)
Approach:
- The problem involves finding a permutation of an array such that the sum of absolute differences (with a constant offset) is minimized.
- The key insight is to sort the array first but also consider a reversed version depending on the sign of `c`.
- If `c >= 0`, the optimal arrangement is just the sorted array.
- If `c < 0`, the code performs a more complex reordering to minimize cost, using a greedy or heuristic-like approach, involving segments and greedy selection based on cost constraints.

Time Complexity: O(n log n) due to sorting operations and linear traversal
Space Complexity: O(n) for storing the array, auxiliary arrays, and result
"""

for _ in range(int(input())):
    n, c = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort()
    if c >= 0:
        print(*a)
        continue
    a.reverse()
    l1 = [0]
    c *= -1
    for i in range(n - 2):
        if a[i] - a[i + 2] > c:
            l1.append(i + 1)
    l1.append(n - 1)
    ans = [a[0]]
    visited = [0] * n
    for i in range(len(l1) - 1):
        x = l1[i]
        y = l1[i + 1]
        if x == y:
            continue
        a1 = [a[x]]
        visited[x] = 1
        visited[y] = 1
        for j in range(x, y):
            if a[j] + c < a1[-1]:
                a1.append(a[j - 1])
                visited[j - 1] = 1
        a2 = [a[y]]
        for j in range(y, x, -1):
            if a2[-1] + c < a[j] and j <= y - 2:
                if visited[j + 1] == 0:
                    a2.append(a[j + 1])
                    visited[j + 1] = 1
                elif visited[j + 2] == 0:
                    a2.append(a[j + 2])
                    visited[j + 2] = 1
        ans.pop()
        ans += a1
        for j in range(y, x, -1):
            if visited[j] == 0:
                ans.append(a[j])
        a2.reverse()
        ans += a2
    print(*ans)


# https://github.com/VaHiX/CodeForces/