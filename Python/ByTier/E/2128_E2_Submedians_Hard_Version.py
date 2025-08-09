# Contest 2128, Problem E2: Submedians (Hard Version)
# URL: https://codeforces.com/contest/2128/problem/E2

import sys; input = sys.stdin.readline
import heapq

for _ in range(int(input())):
	n,k = [int(t) for t in input().split()]
	a = [int(t)-1 for t in input().split()]

	def solve(m):
		b = [+1 if e >= m else -1 for e in a]
		p = [0]
		for e in b: p.append( p[-1] + e )
 
		best = 0
		L = 0
		for R in range(k,n+1):
			if p[R-k] < best:
				best = p[R-k]
				L = R-k
			if p[R] >= best:
				return (L,R)
		return 0
	def opt():
		x = 0
		jump = 1<<19
		while jump:
			if solve(x+jump): x += jump
			jump //= 2
		l,r = solve(x)
		return x,l,r
	Mx,L,R = opt()
	a = [n-1-e for e in a]
	mx,l,r = opt()
	mx = n-1-mx
	a = [n-1-e for e in a]
	
	bl = min(l,L)
	br = max(r,R)
	line = [0]*n
	for cl,cr,f,last in ((l,r,max,mx),(L,R,min,Mx)):
		hl = []
		hr = []
		med = last
		def insert(t):
			global med
			if hr and t < hr[0]: heapq.heappush(hl,-t)
			else: heapq.heappush( hr,t )
			while len(hr) > len(hl) + 1:
				heapq.heappush( hl, -heapq.heappop(hr) )
			while len(hl) > len(hr) + 1:
				heapq.heappush( hr, -heapq.heappop(hl) )
			if len(hl) == len(hr): med = f(-hl[0],hr[0])
			elif len(hl) > len(hr): med = -hl[0]
			else: med = hr[0]
		def update():
			global last
			nxt = f(last,med)
			if nxt == last and not nxt == med: return
			for i in range(last,nxt+1,+1): line[i] = (i+1,cl+1,cr)
			for i in range(last,nxt-1,-1): line[i] = (i+1,cl+1,cr)
			last = nxt

		for i in range(cl,cr): insert(a[i])
		update()
		while cl > bl:
			cl -= 1
			insert( a[cl] )
			update()
		while cr < br:
			insert( a[cr] )
			cr += 1
			update()
	print( sum(e != 0 for e in line) )
	for e in line:
		if e == 0: continue
		print(*e)