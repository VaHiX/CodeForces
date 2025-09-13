# Contest 2101, Problem B: Quartet Swapping
# URL: https://codeforces.com/contest/2101/problem/B

for _ in range(int(input())):

    def swap(i, j):
        a[i], a[j] = a[j], a[i]
        a[i + 1], a[j + 1] = a[j + 1], a[i + 1]
        idx[a[i]] = i
        idx[a[j]] = j
        idx[a[i + 1]] = i + 1
        idx[a[j + 1]] = j + 1

    n = int(input())
    a = [int(i) for i in input().split()]
    idx = [0] * (n + 1)
    odd, even = [], []
    for i in range(n):
        idx[a[i]] = i
        if i & 1:
            odd.append(a[i])
        else:
            even.append(a[i])
    odd.sort(reverse=True)
    even.sort(reverse=True)
    for i in range(n - 4):
        if i & 1:
            x = odd.pop()
        else:
            x = even.pop()
        if idx[x] == n - 1:
            swap(n - 2, n - 4)
        swap(i, idx[x])
    if a[n - 2] < a[n - 4]:
        swap(n - 2, n - 4)
    print(*a)
