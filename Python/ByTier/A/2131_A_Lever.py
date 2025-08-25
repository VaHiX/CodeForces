# Contest 2131, Problem A: Lever
# URL: https://codeforces.com/contest/2131/problem/A

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    ans = 1
    for i in range(n):
        ans += max(0, a[i] - b[i])
    print(ans)
