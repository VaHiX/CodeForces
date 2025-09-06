# Contest 1012, Problem A: Photo of The Sky
# URL: https://codeforces.com/contest/1012/problem/A

import sys 
input = sys.stdin.buffer.readline 

def process(A):
    n = len(A)
    A.sort()
    x1, x2, y1, y2 = A[0], A[n//2-1], A[n//2], A[n-1]
    answer = (x2-x1)*(y2-y1)
    for i in range(n):
        if 0 < i <= i+n//2-1 < n-1:
            x1 = A[0]
            x2 = A[n-1]
            y1 = A[i]
            y2 = A[i+n//2-1]
            answer = min(answer, (y2-y1)*(x2-x1))
    sys.stdout.write(f'{answer}\n')
    return 

n = int(input())
A = [int(x) for x in input().split()]
process(A)