# Contest 1904, Problem A: Forked!
# URL: https://codeforces.com/contest/1904/problem/A

for _ in range(int(input())):
    a, b = map(int, input().split())
    xk, yk = map(int, input().split())
    xq, yq = map(int, input().split())
    l = [(a, b), (a, -b), (-a, b), (-a, -b), (b, a), (b, -a), (-b, a), (-b, -a)]
    K = set()
    Q = set()
    for x, y in l:
        K.add((x + xk, y + yk))
        Q.add((x + xq, y + yq))
    print(len(K.intersection(Q)))
