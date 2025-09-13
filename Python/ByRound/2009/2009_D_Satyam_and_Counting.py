# Contest 2009, Problem D: Satyam and Counting
# URL: https://codeforces.com/contest/2009/problem/D

import sys
input=lambda:sys.stdin.readline().strip()

t=int(input())
for _ in range(t):
	n=int(input())
	x=set()
	y=set()
	for _ in range(n):
		a,b=map(int,input().split())
		if b:x.add(a)
		else:y.add(a)
	ans=0
	for a in x:
		if a in y:
			ans+=len(x)-1+len(y)-1
		if a-1 in y and a+1 in y:
			ans+=1
	for a in y:
		if a-1 in x and a+1 in x:
			ans+=1
	print(ans)


