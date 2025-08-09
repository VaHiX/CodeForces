# Contest 2128, Problem A: Recycling Center
# URL: https://codeforces.com/contest/2128/problem/A

for i in range(int(input())):
    a,b = list(map(int, input().split()))
    c = list(map(int, input().split()))
    c.sort(reverse=True)
    st = 0
    res = 0
    for i in c:
        q = pow(2,st)*i
        if q <= b:
            st+=1
        else:
            res+=1
    print(res)