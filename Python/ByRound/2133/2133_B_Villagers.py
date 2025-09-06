# Contest 2133, Problem B: Villagers
# URL: https://codeforces.com/contest/2133/problem/B

for _ in range(int(input())):
  n = int(input())
  a = list(map(int, input().split()))
  a.sort()
  sm = 0
  for i in range(n-1, -1, -2):
    sm += a[i]
  print(sm)