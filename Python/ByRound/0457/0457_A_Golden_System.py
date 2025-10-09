# Contest 457, Problem A: Golden System
# URL: https://codeforces.com/contest/457/problem/A

import sys

input = sys.stdin.readline


a = input()[:-1]
b = input()[:-1]
n = max(len(a), len(b))
a = list(map(int, a.rjust(n, "0")))
b = list(map(int, b.rjust(n, "0")))
i = 0
while i < n:
    if abs(a[i] - b[i]) == 1:
        if i >= n - 2:
            if a[i] > b[i]:
                print(">")
            else:
                print("<")
            exit()
        if a[i] > b[i]:
            for i1 in range(i, min(i + 3, n)):
                a[i1] += 1
        else:
            for i1 in range(i, min(i + 3, n)):
                b[i1] += 1
    elif a[i] > b[i]:
        print(">")
        exit()
    elif a[i] < b[i]:
        print("<")
        exit()
    i += 1
print("=")
