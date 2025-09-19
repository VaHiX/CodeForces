# Contest 2027, Problem A: Rectangle Arrangement
# URL: https://codeforces.com/contest/2027/problem/A

for _ in range(int(input())):
    ma1=0
    ma2=0
    for i in range(int(input())):
        a,b=map(int,input().split())
        ma1=max(ma1,a)
        ma2=max(ma2,b)
    print(2*(ma1+ma2))