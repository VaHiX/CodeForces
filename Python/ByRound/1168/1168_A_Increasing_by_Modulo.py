# Contest 1168, Problem A: Increasing by Modulo
# URL: https://codeforces.com/contest/1168/problem/A

M=int(input().split()[1])
a=list(map(int,input().split()))
l,r=0,M
while l<r:
	m,p=(l+r)//2,0
	for v in a:
		if(p-v)%M>m:
			if v<p:l=m+1;break
			p=v
	else:r=m
print(l)