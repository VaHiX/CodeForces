# Contest 2014, Problem D: Robert Hood and Mrs Hood
# URL: https://codeforces.com/contest/2014/problem/D

import sys
input=lambda:sys.stdin.readline().strip()

t=int(input())
for _ in range(t):
	n,d,k=map(int,input().split())
	ps=[0]*(n+d+10)
	for i in range(k):
		l,r=map(int,input().split())
		r+=d
		ps[l]+=1
		ps[r]-=1
	for i in range(1,len(ps)):ps[i]+=ps[i-1]
	ps=ps[d:n+1]
	print(max(range(1,n-d+2),key=lambda i:ps[i-1]),min(range(1,n-d+2),key=lambda i:ps[i-1]))


