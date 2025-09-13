# Contest 2049, Problem A: MEX Destruction
# URL: https://codeforces.com/contest/2049/problem/A

t = int(input())
for _ in range(t):
    num, arr = int(input()), input().strip("0 ").split()
    if "0" in arr:
        print(2)
    elif arr:
        print(1)
    else:
        print(0)
