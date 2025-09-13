# Contest 2020, Problem A: Find Minimum Operations
# URL: https://codeforces.com/contest/2020/problem/A

for s in[*open(0)][1:]:
 n,k=map(int,s.split());r=n*(k<2)
 while(k>1)*n:r+=n%k;n//=k
 print(r)
