# Contest 2075, Problem C: Two Colors
# URL: https://codeforces.com/contest/2075/problem/C

for t in range(int(input())):
    n, m = map(int, input().split())
    l1 = [0] * (n + 1)
    for i in map(int, input().split()):
        l1[i] += 1
    for i in range(n - 1, 0, -1):
        l1[i] += l1[i + 1]
    ans = 0
    for i in range(1, n):
        a1 = l1[i]
        a2 = l1[n - i]
        tmp = i if i >= n - i else n - i
        ans += a1 * a2 - l1[tmp]
    print(ans)
