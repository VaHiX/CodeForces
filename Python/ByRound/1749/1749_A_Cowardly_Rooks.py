# Contest 1749, Problem A: Cowardly Rooks
# URL: https://codeforces.com/contest/1749/problem/A

for _ in range(int(input())):
    n, m = map(int, input().split())
    for _ in range(m):
        input()
    print("NO" if n == m else "YES")
