# Contest 1086, Problem A: Connect Three
# URL: https://codeforces.com/contest/1086/problem/A

import sys
input = sys.stdin.buffer.readline 

orders =  [(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]

def process(A, B, C):
    L = [A, B, C]
    answer = [float('inf'), None]
    for i, j, k in orders:
        x1, y1 = L[i]
        x2, y2 = L[j]
        x3, y3 = L[k]
        for l1 in range(2):
            for l2 in range(2):
                S = set([])
                if l1==0: 
                    for x0 in range(min(x1, x2), max(x1, x2)+1):
                        S.add((x0, y1))
                    for y0 in range(min(y1, y2), max(y1, y2)+1):
                        S.add((x2, y0))
                else:
                    for y0 in range(min(y1, y2), max(y1, y2)+1):
                        S.add((x1, y0))
                    for x0 in range(min(x1, x2), max(x1, x2)+1):
                        S.add((x0, y2))
                if l2==0: 
                    for x0 in range(min(x2, x3), max(x2, x3)+1):
                        S.add((x0, y2))
                    for y0 in range(min(y2, y3), max(y2, y3)+1):
                        S.add((x3, y0))
                else:
                    for y0 in range(min(y2, y3), max(y2, y3)+1):
                        S.add((x2, y0))
                    for x0 in range(min(x2, x3), max(x2, x3)+1):
                        S.add((x0, y3))
                entry = [len(S), S]
                answer = min(answer, entry)
    return answer
    
    
A = [int(x) for x in input().split()]
B = [int(x) for x in input().split()]
C = [int(x) for x in input().split()]
a1, a2 = process(A, B, C)
print(a1)
for x, y in a2:
    sys.stdout.write(f'{x} {y}\n')