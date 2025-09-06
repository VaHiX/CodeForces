# Contest 1588, Problem A: Two Arrays
# URL: https://codeforces.com/contest/1588/problem/A

import sys
for _ in range(int(sys.stdin.readline())):
    n = int(sys.stdin.readline())
    a = [int(i) for i in sys.stdin.readline().split()]
    b = [int(i) for i in sys.stdin.readline().split()]
    a.sort(); b.sort()
    for i in range(n):
        if a[i] > b[i] or a[i] < b[i] - 1: 
            print('NO')
            break
    else:
        print('YES')