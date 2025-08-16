# Contest 2123, Problem B: Tournament
# URL: https://codeforces.com/contest/2123/problem/B

for _ in range(int(input())):
  n,j,k = map(int,input().split())
  lst = list(map(int,input().split()))
  if (lst[j-1]==max(lst)) or k>1:
    print('YES')
  else:
    print('NO')