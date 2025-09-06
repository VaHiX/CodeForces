# Contest 1240, Problem A: Save the Nature
# URL: https://codeforces.com/contest/1240/problem/A

def solve():
    N = int(input())
    P = list(map(int,input().split()))
    x,a = list(map(int,input().split()))
    y,b = list(map(int,input().split()))
    if x<y:
        x,y = y,x
        a,b = b,a
    k = int(input())
    P.sort(reverse=True)
    Q = [0]
    for i in range(N):
        Q.append(Q[-1]+P[i])
    xyc = 0
    xc = 0
    yc = 0
    ans = -1
    for i in range(1,N+1):
        if i%a==0 and i%b==0:
            xyc += 1
        elif i%a==0:
            xc += 1
        elif i%b==0:
            yc += 1
        if (Q[xyc] - Q[0])*(x+y) + (Q[xyc+xc]-Q[xyc])*x + (Q[xyc+xc+yc]-Q[xyc+xc])*y>=k*100:
            ans = i
            break
    print(ans)

T = int(input())


for i in range(T):
    solve()