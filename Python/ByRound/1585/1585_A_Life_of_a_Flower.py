# Contest 1585, Problem A: Life of a Flower
# URL: https://codeforces.com/contest/1585/problem/A

for _ in range(int(input())):
    n = int(input())
    x = list(map(int, input().split()))
    h = 1
    if x[0] == 1:
        h += 1
    for i in range(1, n):
        if x[i] == 1 and x[i - 1] == 1:
            h += 5
        elif x[i] == 1:
            h += 1
        elif x[i] != 1 and x[i - 1] != 1:
            h = -1
            break
    print(h)
