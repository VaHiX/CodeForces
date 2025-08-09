# Contest 2130, Problem B: Pathless
# URL: https://codeforces.com/contest/2130/problem/B

for _ in range(int(input())):
    n,s=map(int,input().split())
    a=list(map(int,input().split()))
    total=sum(a)
    T=s-total

    print(*([0]*a.count(0)+[2]*a.count(2)+[1]*a.count(1)) if T<0 or T==1 else [-1])
