# Contest 1898, Problem A: Milica and String
# URL: https://codeforces.com/contest/1898/problem/A

e = [*open(0).read().split()][1:]
for n, k, s in zip(*[iter(e)] * 3):
    n = int(n)
    k = int(k)
    B = s.count("B")
    if B == k:
        print(0)
    else:
        x, y = ["AB", "BA"][B > k]
        c = [1, -1][B > k]
        for i in range(n):
            B += c * (s[i] == x)
            if B == k:
                print(1)
                print(i + 1, y)
                break
