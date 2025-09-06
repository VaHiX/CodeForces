# Contest 1503, Problem A: Balance the Bits
# URL: https://codeforces.com/contest/1503/problem/A

import sys
input = sys.stdin.readline


for _ in range(int(input())):
    n = int(input())
    s = input()[:-1]
    a = []
    b = []
    a1 = b1 = ew = 0
    for i in s:
        if i == '0':
            if a1 > b1:
                a1 -= 1
                b1 += 1
                a.append(')')
                b.append('(')
            else:
                a1 += 1
                b1 -= 1
                a.append('(')
                b.append(')')
        else:
            a1 += 1
            b1 += 1
            a.append('(')
            b.append('(')
        if b1 < 0:
            ew = 1
            break
    if a1 % 2 or ew == 1:
        print('NO')
    else:
        c = 0
        for i in range(n-1, -1, -1):
            if s[i] == '1':
                if a1 > 0:
                    a1 -= 2
                    a[i] = ')'
                    b[i] = ')'
            if b[i] == ')':
                c += 1
            else:
                c -= 1
            if c < 0:
                break
        if c != 0:
            print('NO')
        else:
            print('YES')
            print(''.join(a))
            print(''.join(b))