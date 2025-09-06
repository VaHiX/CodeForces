# Contest 1601, Problem A: Array Elimination
# URL: https://codeforces.com/contest/1601/problem/A

import sys
input = sys.stdin.buffer.readline
from math import gcd
for _ in range(int(input())):
	n = int(input())
	a = list(map(int,input().split()))
	c = [0]*30
	for i in a:
		for j in range(30):
			if (i>>j)&1:
				c[j] += 1
	g = 0
	for i in c:
		g = gcd(g,i)
	if g==0:
		print(*range(1,n+1))
	else:
		y = []
		for i in range(1,int(g**0.5)+1):
			if g%i==0:
				y.append(i)
				if i!=g//i: y.append(g//i)
		y.sort()
		print(*y)
