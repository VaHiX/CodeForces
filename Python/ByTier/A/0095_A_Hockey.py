# Contest 95, Problem A: Hockey
# URL: https://codeforces.com/contest/95/problem/A

import sys

input = sys.stdin.readline

n = int(input())
d = [[] for i in range(26)]
e = set()
for _ in range(n):
    s = input()[:-1]
    if s[0].isupper():
        d[ord(s[0]) - 65].append((s.lower(), len(s)))
    else:
        d[ord(s[0]) - 97].append((s.lower(), len(s)))

for i in d:
    i.sort(key=lambda x: -x[1])
w = input()[:-1]
x = ord(input()[:-1]) - 97
i = 0
while i < len(w):
    if w[i].isupper():
        t = 65
    else:
        t = 97
    for i1, i2 in d[ord(w[i]) - t]:
        if w[i : i + i2].lower() == i1:
            for i3 in range(i, i + i2):
                e.add(i3)
            break
    i += 1
w = list(w)
for i in e:
    if w[i].isupper():
        t = 65
    else:
        t = 97
    if ord(w[i]) - t != x:
        w[i] = chr(x + t)
    elif x != 0:
        w[i] = chr(0 + t)
    else:
        w[i] = chr(1 + t)
print("".join(w))
