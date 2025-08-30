# Contest 2085, Problem F2: Serval and Colorful Array (Hard Version)
# URL: https://codeforces.com/contest/2085/problem/F2

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = [0] + list(map(int, input().split()))
    b = [0] * (n + 1)
    c = [0] * (n + 1)
    s, d, x = 0, -k, 10**18
    for i in range(1, n + 1):
        if b[a[i]] == 0:
            s += i - 1
        else:
            p = b[a[i]]
            mid = (p + i) >> 1
            if (p + i) & 1:
                c[mid] -= 1
                c[mid + 1] -= 1
            else:
                c[mid] -= 2
        c[i] += 2
        b[a[i]] = i
    for i in range(1, n + 1):
        x = min(x, s)
        d += c[i]
        s += d
    for i in range(1, k + 1):
        x -= abs(i - ((k + 1) >> 1))
    print(x)
