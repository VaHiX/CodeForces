# Contest 480, Problem A: Exams
# URL: https://codeforces.com/contest/480/problem/A

c = 0
for i in sorted([*map(int, s.split())] for s in [*open(0)][1:]):
    c = i[c <= i[1]]
print(c)
