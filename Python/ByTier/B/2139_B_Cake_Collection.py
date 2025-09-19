# Contest 2139, Problem B: Cake Collection
# URL: https://codeforces.com/contest/2139/problem/B

for _ in range(int(input())):
    n, m = map(int, input().split())
    arr = sorted(map(int, input().split()), reverse=True)
    ans = 0
    for i in range(min(n, m)):
        ans += arr[i] * (m - i)
    print(ans)
