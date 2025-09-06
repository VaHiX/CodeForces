# Contest 5, Problem B: Center Alignment
# URL: https://codeforces.com/contest/5/problem/B

lst = [line.rstrip() for line in open(0).readlines()]
n = max(len(w) for w in lst)

res = ["*" * (n + 2)]
L = True
for w in lst:
    spaces = n - len(w)
    wSpaces = " " * (spaces // 2)
    w1 = w
    if len(w) % 2 != n % 2:
        w1 = w + " " if L else " " + w
        L = not L
    res.append("*" + wSpaces + w1 + wSpaces + "*")
res.append("*" * (n + 2))
print("\n".join(res))
