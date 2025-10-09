# Contest 2013, Problem C: Password Cracking
# URL: https://codeforces.com/contest/2013/problem/C

import sys
input = sys.stdin.readline

def ask(x):
    print(f"? {x}")
    sys.stdout.flush()
    res = int(input())
    return res

def result(x):
    print(f"! {x}")
    sys.stdout.flush()

for _ in range(int(input())):
    n = int(input())
    ans = ""
    while len(ans)<n:
        if ask(ans+'0'):
            ans+='0'
        elif ask(ans+'1'):
            ans+='1'
        else:
            break
    while len(ans)<n:
        if ask('0'+ans):
            ans='0'+ans
        else:
            ans='1'+ans
    result(ans)



