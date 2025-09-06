# Contest 1341, Problem A: Nastya and Rice
# URL: https://codeforces.com/contest/1341/problem/A

for s in[*open(0)][1:]:n,a,b,c,d=map(int,s.split());print('YNeos'[c+d<n*(a-b)or(a+b)*n<c-d::2])