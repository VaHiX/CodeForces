# Contest 2037, Problem E: Kachina's Favorite Binary String
# URL: https://codeforces.com/contest/2037/problem/E

import sys

input = lambda: sys.stdin.readline().strip()

t = int(input())
for _ in range(t):
	n = int(input())
	ans = ''
	
	print('? {} {}'.format(1, n))
	sys.stdout.flush()
	w = int(input())
	
	if w == 0:
		print("! IMPOSSIBLE")
		sys.stdout.flush()
	else:
		flag = True
		cnt = 1
		for i in range(2, n + 1):
			print('? {} {}'.format(1, i))
			sys.stdout.flush()
			w = int(input())
			if flag:
				if w == 0:
					cnt += 1
				else:
					ans = '1' * (cnt - w) + '0' * (w) + '1'
					flag = False
			elif not flag:
				if (w - num) == 0:
					ans += '0'
				else:
					ans += '1'
					
			num = w
		
		print('! {}'.format(ans))
		sys.stdout.flush()