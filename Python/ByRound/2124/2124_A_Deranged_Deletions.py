# Contest 2124, Problem A: Deranged Deletions
# URL: https://codeforces.com/contest/2124/problem/A

for _ in range(int(input())):
	n = int(input())
	a = list(map(int,input().split()))

	if n == 1: print("NO")
	else:
		for i in range(n - 1):
			if a[i] > a[i + 1]:
				print("YES")
				print(2)
				print(a[i], a[i + 1])
				break
		else:
			print("NO")
