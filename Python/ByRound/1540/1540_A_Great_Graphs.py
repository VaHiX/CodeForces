# Contest 1540, Problem A: Great Graphs
# URL: https://codeforces.com/contest/1540/problem/A

import sys
input = sys.stdin.readline

t=int(input())
for tests in range(t):
    n=int(input())
    arr=list(map(int,input().split()))

    arr.sort()
    res=0
    sumi=arr[-1]

    for i in range(n-1):
        res+=(arr[i+1]-arr[i])*(i+1)*(n-i-1)

    print(sumi-res)
    
