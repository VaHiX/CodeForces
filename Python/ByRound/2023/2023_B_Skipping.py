# Contest 2023, Problem B: Skipping
# URL: https://codeforces.com/contest/2023/problem/B

import sys
 
input = lambda: sys.stdin.readline().strip()
 

p = 10 ** 18






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