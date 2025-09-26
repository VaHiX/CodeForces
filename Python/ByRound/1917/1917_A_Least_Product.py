# Contest 1917, Problem A: Least Product
# URL: https://codeforces.com/contest/1917/problem/A

for s in [*open(0)][2::2]:
    print(("1 1 0", 0)["0" in s.split() or s.count("-") % 2])
