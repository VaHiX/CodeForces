# Contest 2029, Problem A: Set
# URL: https://codeforces.com/contest/2029/problem/A

for s in [*open(0)][1:]:
    l, r, k = map(int, s.split())
    print(max(0, r // k - l + 1))
