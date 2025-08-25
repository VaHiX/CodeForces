# Contest 2093, Problem B: Expensive Number
# URL: https://codeforces.com/contest/2093/problem/B

for s in [*open(0)][1:]:
    print(len(s) - s.strip().rstrip("0").count("0") - 2)
