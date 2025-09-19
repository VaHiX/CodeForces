# Contest 2060, Problem G: Bugged Sort
# URL: https://codeforces.com/contest/2060/problem/G

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    arr = [0 for _ in range(2 * n)]
    couple = [0 for _ in range(2 * n)]
    visited = [0 for _ in range(2 * n)]
    a = [*map(lambda x: int(x) - 1, input().split())]
    b = [*map(lambda x: int(x) - 1, input().split())]
    for i in range(n):
        arr[a[i]] = 0
        arr[b[i]] = 1
        couple[a[i]] = b[i]
        couple[b[i]] = a[i]
    cnt = 0
    end = 0
    Q = []
    ansa, ansb = [], []
    for i in range(2 * n):
        if visited[i]:
            continue
        visited[i] = 1
        visited[couple[i]] = 1
        if not ansa:
            ansa.append(i)
            ansb.append(couple[i])
            if arr[i] == 1:
                cnt += 1
        elif ansa[-1] < ansb[-1]:
            if ansb[-1] < i:
                Q.append(len(ansa))
            if arr[i] == 1:
                cnt += 1
            ansa.append(i)
            if ansb[-1] < couple[i]:
                ansb.append(couple[i])
            else:
                end = 1
                print("NO")
                break
        else:
            if ansa[-1] < i:
                Q.append(len(ansa))
            if arr[i] == 0:
                cnt += 1
            ansb.append(i)
            if ansa[-1] < couple[i]:
                ansa.append(couple[i])
            else:
                end = 1
                print("NO")
                break
    if not end:
        if n % 2:
            print("YES")
        else:
            if cnt % 2 == 0:
                print("YES")
            else:
                check = 0
                for val in Q:
                    if val % 2:
                        check = 1
                if check:
                    print("YES")
                else:
                    print("NO")
