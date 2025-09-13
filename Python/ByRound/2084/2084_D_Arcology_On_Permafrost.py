# Contest 2084, Problem D: Arcology On Permafrost
# URL: https://codeforces.com/contest/2084/problem/D

t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    max_ = 0
    for i in range(k, n):
        if n // i >= m + 1:
            max_ = i
    max_ = max(k, max_)
    for i in range(n):
        print(i % max_, end=" ")
    print()
