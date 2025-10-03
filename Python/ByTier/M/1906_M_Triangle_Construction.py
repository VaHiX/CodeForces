# Contest 1906, Problem M: Triangle Construction
# URL: https://codeforces.com/contest/1906/problem/M

n = int(input())
l = list(map(int, input().split()))
print(min(sum(l) // 3, sum(l) - max(l)))
