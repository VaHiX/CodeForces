# Contest 86, Problem A: Reflection
# URL: https://codeforces.com/contest/86/problem/A

a,b = map(int,input().split())
la,lb = len(str(a)),len(str(b))
mid = (10**lb)//2
if a<=mid<=b:
    print(mid*(mid-1))
else:
    if a>mid:
        print(a*((10**la)-1-a))
    else:
        print(b*((10**lb)-1-b))