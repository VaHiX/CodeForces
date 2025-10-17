# Contest 1575, Problem K: Knitting Batik
# URL: https://codeforces.com/contest/1575/problem/K

p = 10**9 + 7
n, m, k, r, c = [int(x) for x in input().split()]
ax, ay, bx, by = [int(x) for x in input().split()]
if [ax, ay] != [bx, by]:
    answer = pow(k, n * m - r * c, p)
else:
    answer = pow(k, n * m, p)
print(answer)
