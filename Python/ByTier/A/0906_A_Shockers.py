# Contest 906, Problem A: Shockers
# URL: https://codeforces.com/contest/906/problem/A

import sys

input = sys.stdin.readline

n = int(input())
q = {chr(i) for i in range(97, 123)}
c = 0
t = "0"
for i in range(n - 1):
    s = input()[:-1]
    if t == "0":
        if s[0] == "!":
            s = set(s[2:])
            q &= s
        else:
            for j in set(s[2:]):
                if j in q:
                    q.remove(j)
        if len(q) == 1:
            t = q.pop()
    else:
        if s[0] in "!?":
            c += 1
print(c)
