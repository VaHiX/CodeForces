# Contest 2118, Problem D1: Red Light, Green Light (Easy version)
# URL: https://codeforces.com/contest/2118/problem/D1


for t in range(int(input())):
    n, k = map(int, input().split())
    p = list(map(int, input().split()))
    d = list(map(int, input().split()))
    e = [[-1, -1] for i in range(n)]
    for i in range(n):
        for j in range(i - 1, -1, -1):
            if (d[j] - d[i] + p[j] - p[i]) % k == 0:
                e[i][0] = j
                break
        for j in range(i + 1, n):
            if (d[j] - d[i] - p[j] + p[i]) % k == 0:
                e[i][1] = j
                break
    q = []

    q1 = int(input())
    q = list(map(int, input().split()))
    for i in range(len(q)):
        te = -1
        for j in range(n):
            if p[j] >= q[i] and (p[j] - q[i]) % k == d[j]:
                te = j
                break
        if te == -1:
            print("YES")
        else:
            tr = 1

            cur = e[te][0]
            fl = 0
            cov = 1

            while cov < (2 * n + 1) and cur != te or tr == 1:

                nx = e[cur][tr]
                if nx == -1:
                    fl = 1
                    break
                else:
                    cur = nx
                    tr = (tr + 1) % 2
                    cov += 1
            if fl == 1:
                print("YES")
            else:
                print("NO")
