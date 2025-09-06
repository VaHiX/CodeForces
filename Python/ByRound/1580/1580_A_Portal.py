import sys

T = int(sys.stdin.readline().strip())

def v(is0, is1, x, y, a, b, flag):
    if flag == 1:
        g = is1
    else:
        g = is0
    return g[a+1][b+1] + g[x][y] - g[a+1][y] - g[x][b+1]

for t in range(T):
    n, m = list(map(int, sys.stdin.readline().strip().split(' ')))
    mat = []
    for i in range(n):
        mat.append(sys.stdin.readline().strip())
    is1 = [[0 for j in range(m + 1)] for i in range(n + 1)]
    is0 = [[0 for j in range(m + 1)] for i in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            is1[i][j] = is1[i-1][j] + is1[i][j-1] - is1[i-1][j-1] + int(mat[i-1][j-1] == '1')
            is0[i][j] = is0[i-1][j] + is0[i][j-1] - is0[i-1][j-1] + int(mat[i-1][j-1] == '0')
    res = 16
    for i in range(n):
        for j in range(m):
            for a in range(i + 4, n):
                left = v(is0, is1, i+1, j, a-1, j, 0)
                if left >= res:
                    break
                for b in range(j + 3, m):
                    up = v(is0, is1, i, j+1, i, b-1, 0)
                    r = left + up
                    if r >= res:
                        break
                    down = v(is0, is1, a, j+1, a, b-1, 0)
                    r += down
                    if r >= res:
                        break
                    mid = v(is0, is1, i+1, j+1, a-1, b-1, 1)
                    r += mid
                    if r >= res:
                        break
                    right = v(is0, is1, i+1, b, a-1, b, 0)
                    r += right
                    if r < res:
                        res = r
    print(res)
                    
            



