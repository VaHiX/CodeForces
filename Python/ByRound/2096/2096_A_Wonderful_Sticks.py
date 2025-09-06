# Contest 2096, Problem A: Wonderful Sticks
# URL: https://codeforces.com/contest/2096/problem/A

for *s, _ in [*open(0)][2::2]:
    m = M = s.count("<") + 1
    print(m, *(x < ">" and (m := m - 1) or (M := M + 1) for x in s))
