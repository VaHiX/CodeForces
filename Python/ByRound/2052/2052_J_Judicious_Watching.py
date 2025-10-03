# Contest 2052, Problem J: Judicious Watching
# URL: https://codeforces.com/contest/2052/problem/J

II = lambda: int(input())
MII = lambda: map(int, input().split())
LII = lambda: list(MII())
from bisect import bisect_right

results = []
tests = II()
for _ in range(tests):
    n, m, q = MII()
    a = LII()
    d = LII()
    l = LII()
    q = LII()
    tasks = [(a[i], d[i]) for i in range(n)]
    tasks.sort(key=lambda el: el[1])
    a = [i[0] for i in tasks]
    d = [i[1] for i in tasks]
    total_time = [a[0]] * n
    for i in range(1, n):
        total_time[i] = a[i] + total_time[i - 1]
    headway = [0] * n
    headway[-1] = d[-1] - total_time[-1]
    for i in range(n - 2, -1, -1):
        headway[i] = min(headway[i + 1], d[i] - total_time[i])
    finish_time = []
    series_ptr = 0
    time_spent = 0
    total_time.append(0)
    for i in range(n):
        while series_ptr < m and headway[i] - time_spent >= l[series_ptr]:
            time_spent += l[series_ptr]
            finish_time.append(total_time[i - 1] + time_spent)
            series_ptr += 1
    while series_ptr < m:
        time_spent += l[series_ptr]
        finish_time.append(total_time[-2] + time_spent)
        series_ptr += 1
    ans = []
    for i in q:
        ans.append(bisect_right(finish_time, i))
    results.append(" ".join(map(str, ans)))

print("\n".join(map(str, results)))
