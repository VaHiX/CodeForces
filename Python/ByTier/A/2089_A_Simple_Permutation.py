# Contest 2089, Problem A: Simple Permutation
# URL: https://codeforces.com/contest/2089/problem/A

t = int(input())

prime = [1] * 100001
for i in range(2, 100001):
    if prime[i] == 1:
        for j in range(2 * i, 100001, i):
            prime[j] = 0


for t_ in range(t):
    n = int(input())
    m = (n + 1) // 2
    if prime[m] == 1:
        p = m
    else:
        for i in range(1, min(m - 1, n - m) + 1):
            q = m + i
            r = m - i
            if prime[q] == 1:
                p = q
                break
            if prime[r] == 1:
                p = r
                break

    perm = [p]
    for i in range(1, min(p - 1, n - p) + 1):
        perm.append(p + i)
        perm.append(p - i)

    if p - 1 < n - p:
        for i in range(2 * p, n + 1):
            perm.append(i)
    elif p - 1 > n - p:
        for i in range(2 * p - n - 1, 0, -1):
            perm.append(i)

    print(" ".join(map(str, perm)))
