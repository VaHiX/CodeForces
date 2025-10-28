# Problem: CF 2023 B - Skipping
# https://codeforces.com/contest/2023/problem/B

"""
Algorithm: Segment Tree with Dynamic Programming
Approach:
- We use a segment tree to efficiently query and update the minimum values of scores in a range.
- For each problem, we compute the minimum score that can be obtained before submitting it.
- The problem is modeled as a decision process where at each step we decide whether to skip or submit a problem.
- The key insight is that when we skip a problem i, the next problem comes from indices j <= b[i], and we need to track the best possible score to reach those.

Time Complexity: O(n log n)
Space Complexity: O(n)
"""

import sys

input = lambda: sys.stdin.readline().strip()
p = 10**18
T = int(input())
for _ in range(T):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    k = 1
    while k < n:
        k *= 2
    d = [p] * (2 * k)
    if b[0] > 1:
        j = k + b[0] - 1
        while j > 0:
            d[j] = a[0]
            j //= 2
    for i in range(1, n):
        if b[i] > i + 1:
            l = i + k
            r = n + k - 1
            h = p
            while r >= l:
                if l % 2 == 1:
                    h = min(h, d[l])
                if r % 2 == 0:
                    h = min(h, d[r])
                l = (l + 1) // 2
                r = (r - 1) // 2
            if h < p:
                h += a[i]
                j = k + b[i] - 1
                while j > 0:
                    d[j] = min(d[j], h)
                    j //= 2
    ans = a[0]
    s = a[0]
    for i in range(1, n):
        s += a[i]
        if d[i + k] < p:
            ans = max(ans, s - d[i + k])
    print(ans)


# https://github.com/VaHiX/CodeForces/