# Contest 2138, Problem E1: Determinant Construction (Easy Version)
# URL: https://codeforces.com/contest/2138/problem/E1


def construct_cf_matrix(x):
    if x == 0:
        return [[0]]

    k = x.bit_length()
    n = 3 * k + 1
    M = [[0] * n for _ in range(n)]

    for i in range(k):
        r = 2 * i
        c = 2 * i
        M[r][c] = 1
        M[r][c + 1] = -1
        M[r + 1][c] = 1
        M[r + 1][c + 1] = 1
        M[r + 2][c + 1] = 1

        if (x >> i) & 1:
            M[2 * i + 1][2 * k + i + 1] = 1 if i % 2 == 0 else -1

    for i in range(2 * k + 1, n):
        M[i][i - 1] = 1
        M[i][i] = 1

    return M


t = int(input())
for _ in range(t):
    x = int(input())
    M = construct_cf_matrix(x)
    print(len(M))
    for row in M:
        print(" ".join(str(v) for v in row))
