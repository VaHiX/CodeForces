# Contest 418, Problem A: Football
# URL: https://codeforces.com/contest/418/problem/A

n, k = map(int, input().split())

a = [[0 for i in range(n)] for i in range(n)]

ne = False

br = 0
if n < k:
    print(-1)

else:

    for i in range(n):
        for j in range(i + 1, i + k + 1):
            if j >= n:
                s = j - n
                if a[i][s] == 1 or a[s][i] == 1:
                    ne = True
                    break
                else:
                    a[i][s] = 1
                    br += 1
            else:
                s = j
                if a[i][s] == 1 or a[s][i] == 1:
                    ne = True
                    break
                else:
                    a[i][s] = 1
                    br += 1

    if ne or n * k > n * (n - 1) // 2:
        print(-1)

    else:
        print(n * k)
        for i in range(n):
            for j in range(n):
                if a[i][j] == 1:
                    print(i + 1, j + 1)
