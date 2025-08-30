# Contest 2078, Problem C: Breach of Faith
# URL: https://codeforces.com/contest/2078/problem/C

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    arr.sort()
    cur = 0
    for i in range(1, 2 * n - 2, 2):
        cur += arr[i] - arr[i + 1]
    cur -= arr[-1]
    cur = arr[0] - cur
    arr.append(cur)
    arr[-1], arr[-2] = arr[-2], arr[-1]
    print(" ".join(map(str, arr)))
