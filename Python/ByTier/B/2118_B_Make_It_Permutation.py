# Contest 2118, Problem B: Make It Permutation
# URL: https://codeforces.com/contest/2118/problem/B

t = int(input())
for _ in range(t):
    n = int(input())
    print(2 * n - 1)
    for i in range(1, n + 1):
        print(i, 1, i)
        if i < n:
            print(i, i + 1, n)
