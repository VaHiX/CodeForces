# Contest 39, Problem A: C*++ Calculations
# URL: https://codeforces.com/contest/39/problem/A

a = int(input())
s = "+" + input()

t = []

p = 0
n = len(s)
while p < n:
    pa = s.find("a", p)
    if pa >= p + 3 and s[pa - 2 : pa] == "++":
        np = pa + 1
    else:
        np = pa + 3
    t.append(s[p:np])
    p = np

coef = []
for s in t:
    if s[-1] == "a":
        pre = True
    else:
        pre = False
    v = 1
    if len(s) > 4:
        v = int(s[:-4])
    elif s[0] == "-":
        v = -1
    coef.append((v, pre))

coef.sort()
ans = 0
for v, pre in coef:
    if pre:
        a += 1
    ans += v * a
    if not pre:
        a += 1
print(ans)
