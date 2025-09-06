# Contest 657, Problem A: Bear and Forgotten Tree 3
# URL: https://codeforces.com/contest/657/problem/A

n, h, d = map(int, input().split())
if h < d or n < h + 1 or h > 2 * d or h == d == 1 and n > 2:
    print(-1)
else:
    for i in range(1, d + 1):
        print(i, i + 1)
    if h > d:
        print(1, d + 2)
        for i in range(d + 2, h + 1):
            print(i, i + 1)
        for i in range(h + 2, n + 1):
            print(1, i)
    else:
        for i in range(d + 2, n + 1):
            print(i, 2)
                
            