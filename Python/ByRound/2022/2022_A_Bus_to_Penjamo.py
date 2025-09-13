# Contest 2022, Problem A: Bus to Pénjamo
# URL: https://codeforces.com/contest/2022/problem/A

for _ in range(int(input())):
    n, r = map(int, input().split())
    *a, = map(int, input().split())
    ans = 0
    cm = 0
    for x in a:
        ans += (x//2)
        cm += x%2
    m = r-ans
    print(2*ans + min(2*m - cm, cm))