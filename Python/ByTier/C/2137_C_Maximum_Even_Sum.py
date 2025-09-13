# Contest 2137, Problem C: Maximum Even Sum
# URL: https://codeforces.com/contest/2137/problem/C

t = int(input())
l = []
for i in range(t):
    a, b = map(int, input().split())
    if b % 2 == 0:
        k = b // 2
    else:
        k = b
    if (a * k + b // k) % 2 != 0:
        l.append(-1)
    else:
        l.append(a * k + b // k)
for i in range(len(l)):
    print(l[i])
