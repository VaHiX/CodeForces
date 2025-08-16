# Contest 2119, Problem A: Add or XOR
# URL: https://codeforces.com/contest/2119/problem/A

for s in[*open(0)][1:]:a,b,x,y=map(int,s.split());b-=a;print(y if a%2==-b==1else-1if b<0else b*x-(b+~a%2)//2*max(0,x-y))