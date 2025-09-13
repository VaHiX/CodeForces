# Contest 1747, Problem A: Two Groups
# URL: https://codeforces.com/contest/1747/problem/A

for s in [*open(0)][2::2]:
    print(abs(sum(map(int, s.split()))))
