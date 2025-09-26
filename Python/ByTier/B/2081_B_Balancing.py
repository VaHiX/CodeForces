# Contest 2081, Problem B: Balancing
# URL: https://codeforces.com/contest/2081/problem/B

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main():
    n = int(input())
    arr = list(map(int, input().split()))
    dec = 0
    first = -1
    last = -1
    for i in range(n - 1):
        if arr[i] > arr[i + 1]:
            dec += 1
            if first < 0:
                first = i
            last = i + 1

    if dec == 0:
        print(0)
        return

    ans = 0

    if arr[last] - arr[first] < last - first:
        ans += 1
        dec -= 1

    ans += (dec - 1) // 2 + 1

    print(ans)


T = int(input())
t = 1
while t <= T:
    main()
    t += 1
