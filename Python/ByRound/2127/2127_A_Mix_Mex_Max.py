# Contest 2127, Problem A: Mix Mex Max
# URL: https://codeforces.com/contest/2127/problem/A

t=int(input())
for _ in range(t):
    n=int(input())
    a=list(map(int,input().split()))
    s=list(set(a))
    if -1 in s:
        s.remove(-1)
    if 0 in s or len(s)>1:
        print('No')
    else:
        print('Yes')