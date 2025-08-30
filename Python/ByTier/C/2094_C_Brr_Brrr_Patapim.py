# Contest 2094, Problem C: Brr Brrr Patapim
# URL: https://codeforces.com/contest/2094/problem/C

t = int(input())

for _ in range(t):
    n = int(input())
    l = list(map(int, input().split()))
    for _ in range(n - 1):
        l.append(int(input().split()[-1]))
    missing = set(range(1, 2 * n + 1)) - set(l)
    l = list(missing) + l
    print(" ".join(map(str, l)))
