# Contest 1545, Problem A: AquaMoon and Strange Sort
# URL: https://codeforces.com/contest/1545/problem/A

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = sorted(a)
    ans = "NO"
    if sorted(a[::2]) == b[::2]:
        ans = "YES"
    print(ans)
