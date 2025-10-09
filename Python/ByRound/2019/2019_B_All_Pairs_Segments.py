# Contest 2019, Problem B: All Pairs Segments
# URL: https://codeforces.com/contest/2019/problem/B

R=lambda:map(int,input().split())
t,=R()
while t:
 t-=1;n,q=R();d={};p=i=0
 for x in(*R(),0):d[r]=d.get(r:=i*(n-i),0)+x-p-1;p=x;d[r]=d.get(r:=r+i-1,0)+1;i+=1
 for k in R():print(d.get(k,0))
