# Contest 2056, Problem F1: Xor of Median (Easy Version)
# URL: https://codeforces.com/contest/2056/problem/F1

for _ in range(int(input())):
    k, m = [int(x) for x in input().split()]
    s = input().strip()
    n = sum(1 for i in s if int(i) & 1)
    a = 0
    for k in range(1, n + 1):
        if n - k & (k - 1 >> 1):
            continue
        for mm in range(1, m):
            if (mm & k - 1) == k - 1:
                a ^= mm
    print(a)
