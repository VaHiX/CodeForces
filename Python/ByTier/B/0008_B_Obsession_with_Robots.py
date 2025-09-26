# Contest 8, Problem B: Obsession with Robots
# URL: https://codeforces.com/contest/8/problem/B

s = input()
l = []
l.append([0, 0])
x = 0
y = 0
f = 0
fl = 0
for i in s:
    if i == "R":
        x += 1
    if i == "L":
        x -= 1
    if i == "U":
        y -= 1
    if i == "D":
        y += 1
    f = 0
    for y1, x1 in l:
        if abs(y1 - y) + abs(x1 - x) <= 1:
            f += 1
    l.append([y, x])
    if f > 1:
        fl = 1
if fl:
    print("BUG")
else:
    print("OK")
