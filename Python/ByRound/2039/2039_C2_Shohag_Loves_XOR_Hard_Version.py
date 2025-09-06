# Contest 2039, Problem C2: Shohag Loves XOR (Hard Version)
# URL: https://codeforces.com/contest/2039/problem/C2

import sys; input = sys.stdin.readline
def li():return [int(i)for i in input().split()]
for w in range(int(input())):
	x,y=li()
	ans=0
	for i in range(1,min(x,y)+1):
		if (x^i)%i==0:ans+=1
	if y>x:
		ans+=(y-x)//x
		e=y-y%x+x
		if x<e^x<=y:ans+=1
		e=y-y%x
		e=e^x
		if y>=2*x and (e<=x or e>y):ans-=1
	print(ans)

