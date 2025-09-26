# Contest 929, Problem A: Прокат велосипедов
# URL: https://codeforces.com/contest/929/problem/A

n, k = map(int, input().split())
a = list(map(int, input().split()))
cur_k = k
ans = 0
flg = True
if len(a) == 2:
    if a[-1] - a[0] > k:
        flg = False
else:
    for i in range(1, n - 1):
        if a[i] - a[i - 1] > k:
            flg = False
            break
        if a[i + 1] - a[i - 1] <= cur_k:
            cur_k -= a[i] - a[i - 1]
        else:
            cur_k = k
            ans += 1

if flg:
    print(ans + 1)
else:
    print(-1)
