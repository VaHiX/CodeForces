# Contest 2035, Problem D: Yet Another Real Number Problem
# URL: https://codeforces.com/contest/2035/problem/D

from collections import deque

MOD = 10**9 + 7


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    pow2 = [1] * (4 * n + 1)
    for i in range(1, 4 * n + 1):
        pow2[i] = (pow2[i - 1] * 2) % MOD

    st = deque()
    ans = 0
    res = []

    for x in a:
        y = 0

        while x % 2 == 0:
            x //= 2
            y += 1

        while st and st[-1][0] < x * (1 << y):
            last_val, last_y = st.pop()
            ans = (ans - last_val * pow2[last_y] % MOD + last_val) % MOD
            y += last_y

        st.append((x, y))
        ans = (ans + x * pow2[y]) % MOD
        res.append(ans)

    print(*res)


for __ in range(int(input())):
    solve()
