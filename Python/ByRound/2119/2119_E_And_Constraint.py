# Contest 2119, Problem E: And Constraint
# URL: https://codeforces.com/contest/2119/problem/E

baku = []
inf = 1<<61
for _ in range(int(input())):
	n = int(input())
	a = [int(t) for t in input().split()]
	b = [int(t) for t in input().split()]
	need = [0]*n
	for i in range(n-1):
		need[i] |= a[i]
		need[i+1] |= a[i]
	if any(need[i]&need[i+1] != a[i] for i in range(n-1)): baku.append(-1); continue
	
	def opt(e,p):
		x = e
		for z in range(29,-1,-1):
			if p&(1<<z) and not e&(1<<z):
				mask = (1<<z+1)-1
				x = (e^(e&mask)) | p
				break
		line = [x]
		if x == p: return line
		
		m = x&(-x)
		while m < (1<<31):
			if not p&m:
				if not x&m:
					x ^= m
					line.append(x)
				x ^= m
			m <<= 1
		return line

	nums = [opt(e,p) for e,p in zip(b,need)]
	v = [e-b[0] for e in nums[0]]
	for i in range(n-1):
		nl = nums[i]
		nr = nums[i+1]
		w = [inf]*len(nr)
		for x,bx in enumerate(nl):
			for y,by in enumerate(nr):
				if bx&by != a[i]: continue
				w[y] = min(w[y],v[x] + by-b[i+1])
		v = w
	baku.append(min(v))
print(*baku)