# Contest 2103, Problem A: Common Multiple
# URL: https://codeforces.com/contest/2103/problem/A

for s in [*open(0)][2::2]:
    print(len({*s.split()}))
