# Contest 2048, Problem B: Kevin and Permutation
# URL: https://codeforces.com/contest/2048/problem/B

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = []
    for i in range(n):
        a.append(0)
    for i in range(1, n // k + 1):
        a[i * k - 1] = i
    j = n // k + 1
    for i in range(n):
        if a[i] == 0:
            a[i] = j
            j += 1
    a = [str(x) for x in a]
    print(" ".join(a))
