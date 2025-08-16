# Contest 2130, Problem C: Double Perspective
# URL: https://codeforces.com/contest/2130/problem/C

for t in range(int(input())):
    n = int(input())
    a = []
    for i in range(n):
        a.append(list(map(int, input().split())) + [i + 1])
    a.sort(key=lambda x: (x[0], -x[1]))
    p = 0
    r = []
    for i in a:
        if p < i[1]:
            p = i[1]
            r.append(i[2])
    print(len(r))
    print(*r)
