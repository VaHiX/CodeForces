# Contest 2044, Problem E: Insane Problem
# URL: https://codeforces.com/contest/2044/problem/E

t = int(input())
for _ in range(t):
    k, l1, r1, l2, r2 = map(int, input().strip().split())
    n = 1
    ans = 0
    while (r2) // n >= l1:
        ans += max(0, 1 + min((r2) // n, r1) - max((l2 + n - 1) // n, l1))
        n *= k
    print(ans)
