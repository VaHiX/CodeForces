# Contest 2091, Problem A: Olympiad Date
# URL: https://codeforces.com/contest/2091/problem/A

for q in [*open(0)][2::2]:
    x = q.replace(" ", "")
    y = "01032025"
    z = 0
    for i in range(len(x)):
        y = y.replace(x[i], "", 1)
        if len(y) == 0:
            z = i + 1
            break
    print(z)
