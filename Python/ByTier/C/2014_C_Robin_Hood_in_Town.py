# Contest 2014, Problem C: Robin Hood in Town
# URL: https://codeforces.com/contest/2014/problem/C

for s in[*open(0)][2::2]:n=len(a:=sorted(map(int,s.split())));print(-(n<3)or
max(0,a[n//2]*n*2-sum(a)+1))