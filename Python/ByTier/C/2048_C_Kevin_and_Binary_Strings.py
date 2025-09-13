# Contest 2048, Problem C: Kevin and Binary Strings
# URL: https://codeforces.com/contest/2048/problem/C

for _ in range(int(input())):
    s = input()
    n = len(s)
    k = s.find("0")
    if k == -1:
        print(1, n, n, n)
    else:
        l = n - k
        p = s[k:].find("1")
        k = 0 if p == -1 else max(k - p, 0)
        print(1, n, k + 1, k + l)
