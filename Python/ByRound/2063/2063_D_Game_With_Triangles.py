# Contest 2063, Problem D: Game With Triangles
# URL: https://codeforces.com/contest/2063/problem/D

from sys import stdin

inp = stdin.readline

t = int(inp())

for _ in range(t):
    n, m = map(int, inp().split())
    a = [int(x) for x in inp().split()]
    b = [int(x) for x in inp().split()]
    a.sort()
    b.sort()
    a_l = [a[-1 - i] - a[i] for i in range(n // 2)]
    b_l = [b[-1 - i] - b[i] for i in range(m // 2)]

    k_max = min((n + m) // 3, n, m)
    print(k_max)
    k = []
    count_a = 0
    count_b = 0
    ans = 0
    for i in range(1, k_max + 1):
        if count_a > n - i:
            ans += b_l[count_b]
            count_b += 1
            count_a -= 1
            ans -= a_l[count_a]
        if count_b > m - i:
            ans += a_l[count_a]
            count_a += 1
            count_b -= 1
            ans -= b_l[count_b]

        if count_a == n - i:
            ans += b_l[count_b]
            count_b += 1
        elif count_b == m - i:
            ans += a_l[count_a]
            count_a += 1

        elif a_l[count_a] > b_l[count_b]:
            ans += a_l[count_a]
            count_a += 1
        else:
            ans += b_l[count_b]
            count_b += 1

        k.append(ans)

    if k_max > 0:
        print(*k)
