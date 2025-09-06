# Contest 2037, Problem D: Sharky Surfing
# URL: https://codeforces.com/contest/2037/problem/D

from bisect import bisect_left
import heapq
import sys
input=lambda:sys.stdin.readline().strip()

t=int(input())
for _ in range(t):
	n,m,l=map(int,input().split())
	ws=[]
	seps=[]
	for _ in range(n):
		a,b=map(int,input().split())
		ws.append(b-a+1)
		seps.append(a)
	locs=[[] for _ in range(n+1)]
	for _ in range(m):
		x,v=map(int,input().split())
		locs[bisect_left(seps,x)].append(v)
	p=1
	u=0
	q=[]
	for i in range(n):
		for v in locs[i]: heapq.heappush(q, -v)
		while len(q) and p <= ws[i]:
			u+=1
			p-=heapq.heappop(q)
		if p<=ws[i]:
			print(-1)
			break
	else:
		print(u)




