# Contest 2040, Problem A: Game of Division
# URL: https://codeforces.com/contest/2040/problem/A

for _ in range(int(input())):
  n,k=map(int,input().split())
  a=list(map(int,input().split()))
  for i in range(n):
    if all((a[j]-a[i])%k for j in range(n) if i!=j):
      print("YES")
      print(i+1)
      break
  else:
    print("NO")