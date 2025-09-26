# Contest 2031, Problem A: Penchick and Modern Monument
# URL: https://codeforces.com/contest/2031/problem/A

for s in [*open(0)][2::2]:
    print(len(a := s.split()) - max(map(a.count, a)))
