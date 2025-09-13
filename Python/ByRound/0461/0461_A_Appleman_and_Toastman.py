# Contest 461, Problem A: Appleman and Toastman
# URL: https://codeforces.com/contest/461/problem/A

n = int(input())
a = list(map(int, input().split()))
a.sort()

if n == 1:
    print(a[0])
else:
    s = a[-1] * n
    for i in range(n - 1):
        s += (i + 2) * a[i]
    print(s)
