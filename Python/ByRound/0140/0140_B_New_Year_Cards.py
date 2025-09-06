# Contest 140, Problem B: New Year Cards
# URL: https://codeforces.com/contest/140/problem/B

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def get(friend, arr, index):
    n = len(arr)
    loca = [-1] * n
    locf = [-1] * n
    for i in range(n):
        loca[arr[i]] = i
        locf[friend[i]] = i

    seq = []
    for i in range(n):
        if i == index:
            continue
        if seq and loca[i] > loca[seq[-1]]:
            continue
        seq.append(i)

    minimum = n
    output = -1
    for i in seq:
        if locf[i] < minimum:
            minimum = locf[i]
            output = i
    return output + 1


def main(t):

    n = int(input())
    grid = []
    for _ in range(n):
        temp = list(map(int, input().split()))
        for i in range(n):
            temp[i] -= 1
        grid.append(temp)

    arr = list(map(int, input().split()))
    for i in range(n):
        arr[i] -= 1

    ans = [get(grid[i], arr, i) for i in range(n)]

    print(*ans)


T = 1  # int(input())
t = 1
while t <= T:
    main(t)
    t += 1
