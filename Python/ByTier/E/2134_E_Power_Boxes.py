# Contest 2134, Problem E: Power Boxes
# URL: https://codeforces.com/contest/2134/problem/E

import sys
input = lambda: sys.stdin.readline().rstrip()

def II(base=10):
    return int(input(),base)

def LI():
    return list(map(int,input()))

def LII():
    return list(map(int,input().split()))

prt = lambda s: print(s,flush=1)
def main():
    n = II()
    f = [0]*(n+2)
    f[n] = 1
    for i in range(n-1,0,-1):
        if f[i+1]==f[i+2]:
            f[i] = 1+f[i+1]
        else:
            prt(f'throw {i}')
            f[i] = II()
    res = [0]*(n+1)
    todo = []
    for i in range(1,n):
        if f[i]==f[i+1]:
            res[i] = 2
        elif f[i+1]>f[i+2]:
            res[i] = 1
        else:
            todo.append(i)
    for i in todo:
        prt(f'swap {i}')
        prt(f'throw {i+1}')
        a = II()
        res[i] = 1 if a==f[i+2]+1 else 2
    prt(f'swap {n-1}')
    prt(f'throw {n-1}')
    res[n] = 1 if II()==2 else 2
    prt('! '+' '.join(map(str,res[1:])))

for _ in range(II()):
    main()

