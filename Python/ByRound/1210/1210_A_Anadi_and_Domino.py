# Contest 1210, Problem A: Anadi and Domino
# URL: https://codeforces.com/contest/1210/problem/A

# https://codeforces.com/problemset/problem/1210/A


def solve(n, e, one):
    v = list(range(2, n + 1))
    for i in one:
        v.insert(
            i,
        )


n, m = map(int, input().split())
if n <= 6:
    print(m)
else:
    e = []
    for _ in range(m):
        a, b = map(int, input().split())
        e.append((a - 1, b - 1))
    maxe = 0
    for i in range(n - 1):
        for j in range(i + 1, n):
            one = {i, j}
            dist = set()
            ecnt = 0
            for ee in e:
                if ee[0] in one:
                    dist.add(ee[1])
                elif ee[1] in one:
                    dist.add(ee[0])
                else:
                    ecnt = ecnt + 1
            ecnt = ecnt + len(dist)
            maxe = max(maxe, ecnt)
    print(maxe)
