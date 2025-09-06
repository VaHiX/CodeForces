# Contest 2038, Problem B: Make It Equal
# URL: https://codeforces.com/contest/2038/problem/B

import sys

def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        l = list(map(int,input().split()))
        verif = True
        i = 0
        op = 0
        ops = [0]*n
        while verif :
            u = l[i]//2
            l[i] = l[i]%2
            l[(i+1)%n] += u
            ops[i] += u
            op += u
            if i == n-1 :
                verif = False
                for i in range(len(l)):
                    if l[i] > 1 :
                        verif = True
            i += 1
            i = i%n
        exist = False 
        for i in range(len(l)):
            if l[i] != l[0]:
                exist = True
        if exist :
            print(-1)
        else :
            c = min(ops)
            print(op-c*n)

main()
        
            