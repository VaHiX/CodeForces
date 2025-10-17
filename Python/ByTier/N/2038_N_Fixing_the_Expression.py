# Contest 2038, Problem N: Fixing the Expression
# URL: https://codeforces.com/contest/2038/problem/N

t = int(input())
for i in range(t):
    x = input()
    if x[0] > x[2]:
        print(x[0] + ">" + x[2])
    elif x[0] < x[2]:
        print(x[0] + "<" + x[2])
    else:
        print(x[0] + "=" + x[2])
