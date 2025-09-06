# Contest 1223, Problem A: CME
# URL: https://codeforces.com/contest/1223/problem/A

s=int(input())
for i in range(s):
 n=int(input())
 if n==1:
  print(3)
 elif n==2:
  print(2)
 elif n%2==0:
  print(n%2)
 elif n%2==1:
  print(1)