# Contest 2061, Problem B: Kevin and Geometry
# URL: https://codeforces.com/contest/2061/problem/B

for t in range(int(input())):
    n = int(input())
    l = [int(x) for x in input().split()]
    l.sort()
    c = 0
    for i in range(n - 1):
        if l[i] == l[i + 1]:
            c = l[i]
            break
    if c == 0:
        print(-1)
        continue
    l.remove(c)
    l.remove(c)
    # n-1 me se 2 elemtn hataye n-1-2=n-3 elemtns remain
    check = False
    for i in range(n - 3):
        if l[i] + 2 * c > l[i + 1]:
            print(c, c, l[i], l[i + 1])
            check = True
            break
    if not check:
        print(-1)
