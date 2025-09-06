# Contest 2077, Problem B: Finding OR Sum
# URL: https://codeforces.com/contest/2077/problem/B

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")
#######################################################################
A = 0
B = 0
m = 30
for i in range(0, m, 2):
    A |= 1 << i
for i in range(1, m, 2):
    B |= 1 << i


def ask(x):
    print(x, flush=True)
    y = ni()
    return y


for _ in range(ni()):
    l = ask(A)
    r = ask(B)
    f = [0] * m
    for i in range(0, m, 2):
        l -= 2 << i
    for i in range(1, m, 2):
        r -= 2 << i
    # print(l, r)
    for i in range(1, m, 2):
        f[i] = l >> i & 3
    for i in range(0, m, 2):
        f[i] = r >> i & 3
    # print(f)
    print("!", flush=True)
    p = ni()

    ans = 0
    for i in range(m):
        if p >> i & 1:
            ans += 2 << i
        else:
            ans += f[i] << i

    print(ans, flush=True)
