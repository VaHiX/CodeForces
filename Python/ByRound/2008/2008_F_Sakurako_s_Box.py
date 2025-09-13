# Contest 2008, Problem F: Sakurako's Box
# URL: https://codeforces.com/contest/2008/problem/F

import sys

input = sys.stdin.buffer.readline
p = 10 ** 9 + 7
for _ in range(int(input())):
	n = int(input())
	s = t = 0
	for x in map(int, input().split()):
		s += x
		t += x * x
	print(((s % p) ** 2 - t) * pow(n * (n - 1), p - 2, p) % p)