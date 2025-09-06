# Contest 2120, Problem B: Square Pool
# URL: https://codeforces.com/contest/2120/problem/B

for _ in range(int(input())):
    n, s = map(int, input().split())
    ans = 0
    for _ in range(n):
        dx, dy, x, y = map(int, input().split())
        if (x + y == s and dx + dy == 0) or (x == y and dx == dy):
            ans += 1
    print(ans)
