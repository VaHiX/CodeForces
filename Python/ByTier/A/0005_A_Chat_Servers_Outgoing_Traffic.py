# Contest 5, Problem A: Chat Servers Outgoing Traffic
# URL: https://codeforces.com/contest/5/problem/A

import sys

a, b = 0, 0
for i in sys.stdin:
    if i[0] == "+":
        a += 1
    elif i[0] == "-":
        a -= 1
    else:
        b += a * (len(i) - i.find(":") - 2)
print(b)
