# Contest 875, Problem A: Classroom Watch
# URL: https://codeforces.com/contest/875/problem/A

n = int(input())
a = [n-i for i in range(min(81, n), 0, -1) if sum(map(int, str(n-i))) + n - i == n]
print(len(a))
if a: print(*a)