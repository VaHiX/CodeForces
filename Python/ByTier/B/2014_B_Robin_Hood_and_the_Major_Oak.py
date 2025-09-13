# Contest 2014, Problem B: Robin Hood and the Major Oak
# URL: https://codeforces.com/contest/2014/problem/B

for s in[*open(0)][1:]:n,k=map(int,s.split());print('YNEOS'[n%2+k&3>1::2])