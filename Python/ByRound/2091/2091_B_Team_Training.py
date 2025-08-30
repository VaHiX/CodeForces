# Contest 2091, Problem B: Team Training
# URL: https://codeforces.com/contest/2091/problem/B

for t in range(int(input())):
    n, x = map(int, input().split())
    arr = list(map(int, input().split()))
    arr.sort(reverse=True)
    count = 0
    m = 0
    for i in arr:
        m += 1
        if i * m >= x:
            count += 1
            m = 0
    print(count)
