# Contest 1924, Problem A: Did We Get Everything Covered?
# URL: https://codeforces.com/contest/1924/problem/A

import sys

input = lambda: sys.stdin.readline()

t = int(input())
for _ in range(t):
    n, k, m = map(int, input().split())
    s = input().rstrip()
    cnt = [0] * k
    cnti = 0
    cnts = 0
    ans = []
    for i in range(m):
        ix = ord(s[i]) - ord("a")
        if cnt[ix] == 0:
            cnt[ix] = 1
            cnts += 1
        if cnts == k:
            cnts = 0
            cnti += 1
            ans.append(chr(ord("a") + ix))
            for j in range(k):
                cnt[j] = 0

    if cnti >= n:
        print("YES")
    else:
        print("NO")
        for ii in range(k):
            if cnt[ii] == 0:
                ans.append(chr(ii + ord("a")))
                break
        ans = ans + ["a"] * (n - len(ans))
        print("".join(ans))
