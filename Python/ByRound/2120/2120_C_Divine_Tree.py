# Contest 2120, Problem C: Divine Tree
# URL: https://codeforces.com/contest/2120/problem/C

import sys
input=lambda:sys.stdin.readline().strip()

t=int(input())
for _ in range(t):
	n,k=map(int,input().split())
	if k<n or k>(n*(n+1)//2):
		print(-1)
		continue
	lo=0
	hi=n
	while lo+1<hi:
		m=lo+(hi-lo)//2
		w=m+(m*(m-1)//2)+m*(n-m)
		if w>=k:hi=m
		else:lo=m
	rt=hi
	o=[]
	o.append(str(rt))
	w=rt+(rt*(rt-1)//2)+rt*(n-rt)
	rem=w-k
	for i in range(1,n+1):
		if i==rt: continue
		if i<rt:
			o.append(f'{rt} {i}')
		if i>rt:
			if i-rt<=rem:
				o.append(f'{rt-1} {i}')
			else:
				o.append(f'{rt} {i}')
	print('\n'.join(o))



