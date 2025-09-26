# Contest 2007, Problem C: Dora and C++
# URL: https://codeforces.com/contest/2007/problem/C

import math
 
T = int(input())
for _ in range(T) :
	n, a, b = map(int, input().split())
	d = math.gcd(a, b)
	a = list(map(int, input().split()))
	a = [x % d for x in a]
	a.sort()
	res = a[n - 1] - a[0]
	for i in range(1, n) :
		res = min(res, a[i - 1] + d - a[i])
	print(res)