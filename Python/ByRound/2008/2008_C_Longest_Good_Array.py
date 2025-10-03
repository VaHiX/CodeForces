# Contest 2008, Problem C: Longest Good Array
# URL: https://codeforces.com/contest/2008/problem/C

for _ in range(int(input())):
  l, r = map(int, input().split())
  print(int(((1+8*(r-l))**0.5 - 1)//2 + 1))