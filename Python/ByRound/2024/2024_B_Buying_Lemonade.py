# Contest 2024, Problem B: Buying Lemonade
# URL: https://codeforces.com/contest/2024/problem/B

R=lambda:map(int,input().split())
t,=R()
while t:
 t-=1;n,k=R();r=k;a=sorted(R());p=0
 while k>0:k+=(p-(p:=a[-n]))*n;r+=1;n-=1
 print(r-1)