# Contest 2065, Problem C1: Skibidus and Fanum Tax (easy version)
# URL: https://codeforces.com/contest/2065/problem/C1

# UwU ^_^
for t in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = int(input())
    p = -100000000
    for i in range(n):
        if min(a[i], b - a[i]) >= p:
            p = min(a[i], b - a[i])
        elif max(a[i], b - a[i]) >= p:
            p = max(a[i], b - a[i])
        else:
            print("NO")
            break
    else:
        print("YES")
