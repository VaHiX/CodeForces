# Contest 113, Problem A: Grammar Lessons
# URL: https://codeforces.com/contest/113/problem/A

import sys

input = sys.stdin.readline

s = input()[:-1].split()
ew = 0
q = []
d = {"lios": 1, "etr": 2, "initis": 3, "liala": 4, "etra": 5, "inites": 6}
for i in s:
    for j in range(3, 7):
        if len(i) >= j and i[-j:] in d:
            q.append(d[i[-j:]])
            break
    else:
        ew = 2
        break

a = q.count(1)
b = q.count(2)
c = q.count(3)
if a + b + c not in [0, len(s)]:
    ew = 2
if ew == 2:
    print("NO")
else:
    if a + b + c == 0:
        a, b, c = q.count(4), q.count(5), q.count(6)
    if (q == sorted(q) and b == 1) or len(q) == 1:
        print("YES")
    else:
        print("NO")
