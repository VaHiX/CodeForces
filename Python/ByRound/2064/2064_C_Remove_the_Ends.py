# Contest 2064, Problem C: Remove the Ends
# URL: https://codeforces.com/contest/2064/problem/C

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    c1 = 0
    c2 = 0
    for i in range(n):
        if a[i] < 0:
            c1 += abs(a[i])
        else:
            c2 += a[i]
        c1 = max(c1, c2)
    print(c1)
