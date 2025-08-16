# Contest 1952, Problem F: Grid
# URL: https://codeforces.com/contest/1952/problem/F

n=21
a=[[int(i) for i in input()] for _ in range(n)]
ans=0
for x in range(n-3):
  for y in range(n-3):
    res=0
    for dx in range(4):
      for dy in range(4):
        res+=a[x+dx][y+dy]
    ans=max(ans,res)

print(ans)