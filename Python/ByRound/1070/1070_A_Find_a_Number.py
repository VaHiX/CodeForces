# Contest 1070, Problem A: Find a Number
# URL: https://codeforces.com/contest/1070/problem/A

from collections import deque
from sys import exit

d, s = map(int, input().split())
p = d * (s + 1) * [None]
q = deque([0])
p[0] = -1
while q:
    x, z = divmod(q.popleft(), d)
    if x == s and not z:
        y = x * d + z
        ans = ""
        while p[y] != -1:
            ans += str(p[y][0])
            y = p[y][1]
        print(ans[::-1])
        exit(0)
    for i in range(10):
        nx_digits = x + i
        nx_modulo = (10 * z + i) % d
        nx = nx_digits * d + nx_modulo
        if nx_digits <= s and not p[nx]:
            p[nx] = (i, x * d + z)
            q.append(nx)
print(-1)
