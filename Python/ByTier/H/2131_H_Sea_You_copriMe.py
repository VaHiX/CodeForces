# Contest 2131, Problem H: Sea, You & copriMe
# URL: https://codeforces.com/contest/2131/problem/H

MAX = 1_000_001
sieve = [0]*MAX
for p in range(2,MAX):
	if not sieve[p]:
		for i in range(p,MAX,p):
			sieve[i] = p
def primes(n):
	while n > 1:
		p = sieve[n]
		while n%p == 0: n //= p
		yield p
def rad(n):
	d = [1]
	for p in primes(n):
		L = len(d)
		for _ in range(L): d.append( d[-L]*(-p) )
	return d

from math import gcd
def solve():
	n,m = [int(t) for t in input().split()]
	a = [int(t) for t in input().split()]
	cnt = [0]*(m+1)
	for i in range(n):
		for d in rad(a[i]):
			cnt[abs(d)] += 1
	deg = [0]*n
	for i in range(n):
		for d in rad(a[i]):
			deg[i] += (1 if d > 0 else -1) * (cnt[abs(d)]-1)
	
	def adj(x): return [y for y in range(n) if gcd(a[x],a[y]) == 1 and x != y]

	x = max(range(n),key=lambda t:deg[t])
	if sum(deg) == deg[x]*2: return [-1]

	if deg[x] >= 3:
		S = adj(x)
		if all(deg[t]==1 for t in S):
			v = [0]*n
			v[x] = 1
			for e in S: v[e] = 1
			for i in range(n):
				if v[i]: continue
				if deg[i]:
					j = adj(i)[0]
					return [i,j,x,S[0]]
		for y in S:
			if deg[y] == 1: continue
			for z in adj(y):
				if z in [y,x]: continue
				for t in S:
					if t in [y,x,z]: continue
					return [x,t,y,z]
	if deg[x] == 1:
		y = adj(x)[0]
		for i in range(n):
			if i in [x,y]: continue
			if deg[i]:
				j = adj(i)[0]
				return [i,j,x,y]

	y,z = adj(x)
	if deg[y] == 1 and deg[z] == 1:
		for i in range(n):
			if i in [x,y,z]: continue
			if deg[i]:
				j = adj(i)[0]
				return [i,j,x,y]
	if deg[y] == 2 and deg[z] == 1:
		for t in adj(y):
			if t in [x,z]: continue
			return [x,z,y,t]
	if deg[z] == 2 and deg[y] == 1:
		for t in adj(z):
			if t in [x,y]: continue
			return [x,y,t,z]
	c,d = adj(y)
	if (c,d) == (x,z) or (c,d) == (z,x):
		for i in range(n):
			if i in [x,y,z]: continue
			if deg[i]:
				j = adj(i)[0]
				return [x,y,i,j]
	else:
		if not c in [x,z]: return [c,y,x,z]
		if not d in [x,z]: return [d,y,x,z]	

	
	return [-1]

	
baku = [solve() for _ in range(int(input()))]
for b in baku: print(*[e+1 for e in b])