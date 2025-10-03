# Contest 2057, Problem A: MEX Table
# URL: https://codeforces.com/contest/2057/problem/A

for s in [*open(0)][1:]:
    print(max(map(int, s.split())) + 1)
