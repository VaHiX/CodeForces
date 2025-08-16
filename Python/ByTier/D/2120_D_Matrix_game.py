# Contest 2120, Problem D: Matrix game
# URL: https://codeforces.com/contest/2120/problem/D

import sys
input=lambda:sys.stdin.readline().strip()

mod=10**9+7

t=int(input())
for _ in range(t):
	a,b,x=map(int,input().split())
	n=(a-1)*x+1
	m=1
	for i in range(a):
		m=(m*(((n-i)*pow(i+1,-1,mod))%mod))%mod
	m=(m*x*(b-1)+1)%mod
	print(n%mod,m%mod)

