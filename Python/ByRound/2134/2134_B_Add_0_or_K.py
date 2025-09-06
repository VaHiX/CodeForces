# Contest 2134, Problem B: Add 0 or K
# URL: https://codeforces.com/contest/2134/problem/B

t = int(input())
for _ in range(t):
    n,k = map(int,input().split())
    arr = list(map(int, input().split()))
    for i in range(n):
        arr[i]+=(arr[i]%(k+1))*k
    print(*arr)