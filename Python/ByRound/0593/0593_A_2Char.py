# Contest 593, Problem A: 2Char
# URL: https://codeforces.com/contest/593/problem/A

n = int(input())
a = []
for i in range(n):
	x = input()
	if len(set(x)) < 3:
		a.append(x)
mx = 0
for i in range(26):
	for j in range(26):
		x = 0
		for k in a:
			if k.count(chr(ord('a') + i)) + k.count(chr(ord('a') + j)) == len(k):
				x += len(k)
		mx = max(mx, x)
print(mx)
