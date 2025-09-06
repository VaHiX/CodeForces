# Contest 2136, Problem A: In the Dream
# URL: https://codeforces.com/contest/2136/problem/A

for _ in range(int(input())):
    a,b,c,d=map(int,input().split())
    t1=c-a 
    t2=d-b
    if(max(a,b)>2*min(a,b)+2  or max(t1,t2)>2*min(t1,t2)+2):
        print("No")
    else:
        print("Yes")