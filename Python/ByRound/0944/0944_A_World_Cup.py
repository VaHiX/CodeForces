# Contest 944, Problem A: World Cup
# URL: https://codeforces.com/contest/944/problem/A

n, a, b = map(int, input().split())
ans = 0
a-=1
b-=1

while a != b:
    a //= 2
    b //= 2
    ans += 1
if 2**ans == n:
    print('Final!')
else:
    print(ans)
