# Contest 2081, Problem F: Hot Matrix
# URL: https://codeforces.com/contest/2081/problem/F


def generateMatrix(n):
    if n == 1:
        return "YES\n0"
    elif n % 2 == 1:
        return "NO"
    else:
        matrix = [[0 for j in range(n + 1)] for i in range(n + 1)]
    for i in range(0, n, 2):
        for j in range(1, i + 2):
            matrix[j][i + 2 - j] = i + (j % 2 == 0)
        for j in range(n - i, n + 1):
            matrix[j][2 * n - i - j] = i + (j % 2 == 1)
        for j in range(1, n - i):
            matrix[j][i + 1 + j] = i + (j % 2 == 1)
        for j in range(i + 2, n + 1):
            matrix[j][j - i - 1] = i + (j % 2 == 0)
    res = ["YES"]
    for i in range(1, n + 1):
        res.append(" ".join(str(matrix[i][j]) for j in range(1, n + 1)))
    return "\n".join(res)


t = int(input())
for _ in range(t):
    n = int(input())
    print(generateMatrix(n))
