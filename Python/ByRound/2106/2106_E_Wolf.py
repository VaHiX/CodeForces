# Contest 2106, Problem E: Wolf
# URL: https://codeforces.com/contest/2106/problem/E

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n, q = map(int, input().split())
    p = list(map(int, input().split()))
    pos = [0] * (n + 1)
    for i, v in enumerate(p):
        pos[v] = i + 1

    ans = []
    for _ in range(q):
        l, r, x = map(int, input().split())
        px = pos[x]
        if px < l or px > r:
            ans.append(-1)
            continue

        low, high = l, r
        badL = badR = 0
        cntL = cntR = 0
        while low <= high:
            mid = (low + high) // 2
            if mid == px:
                break
            if mid < px:
                cntL += 1
                if p[mid - 1] > x:
                    badL += 1
                low = mid + 1
            else:
                cntR += 1
                if p[mid - 1] < x:
                    badR += 1
                high = mid - 1

        if cntL > x - 1 or cntR > n - x:
            ans.append(-1)
        else:
            ans.append(2 * max(badL, badR))

    print(" ".join(map(str, ans)))
