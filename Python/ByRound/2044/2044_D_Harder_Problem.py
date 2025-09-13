# Contest 2044, Problem D: Harder Problem
# URL: https://codeforces.com/contest/2044/problem/D

for _ in range(int(input())):
    n = int(input())
    m = list(map(int, input().split()))
    c = []
    s = set(range(1, n + 1))

    for i in m:
        if i in s:
            c.append(i)
            s.remove(i)
    print(*(c + list(s)))
