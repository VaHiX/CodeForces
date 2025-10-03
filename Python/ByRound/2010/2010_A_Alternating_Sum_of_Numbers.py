# Contest 2010, Problem A: Alternating Sum of Numbers
# URL: https://codeforces.com/contest/2010/problem/A

for s in[*open(0)][2::2]:*a,=map(int,s.split());print(sum(a[::2])-sum(a[1::2]))