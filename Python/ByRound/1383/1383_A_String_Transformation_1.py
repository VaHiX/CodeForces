# Contest 1383, Problem A: String Transformation 1
# URL: https://codeforces.com/contest/1383/problem/A

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    a = input()[:-1]
    b = input()[:-1]
    q = [set() for i in range(26)]
    for i in range(n):
        if a[i] > b[i]:
            print(-1)
            break
        elif b[i] > a[i]:
            q[ord(a[i]) - 97].add(ord(b[i]) - 97)
    else:
        c = 0
        i = 0
        while i < 26:
            if len(q[i]):
                x = min(q[i])
                q[i].remove(x)
                q[x] |= q[i]
                c += 1
            i += 1
        print(c)
