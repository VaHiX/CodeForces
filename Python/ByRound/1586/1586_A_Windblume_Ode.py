# Contest 1586, Problem A: Windblume Ode
# URL: https://codeforces.com/contest/1586/problem/A

import sys
import os
from io import BytesIO

sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))

f = sys.stdin
if os.environ.get('USER') == "loic":
    f = open("data.in")

line = lambda: f.readline().split()

def write(w):
    sys.stdout.write(w)
    sys.stdout.write("\n")


def is_prime(n):
    i = 2
    while i*i <= n:
        if n%i == 0:
            return False
        i += 1
    return True
 
def solve():
    B = []
    s = sum(A)
    if is_prime(s):
        j = -1
        for i in range(N):
            if A[i]%2 == 1:
                j = i
                break
        for i in range(j):
            B.append(i+1)
        for i in range(j+1,N):
            B.append(i+1)
    else:
        B = list(i+1 for i in range(N))
    
    return str(str(len(B)) + "\n" + " ".join(str(v) for v in B))

T = int(line()[0])
for test in range(1,T+1):
    N = int(line()[0])
    A = list(map(int,line()))
    write(solve())
    
f.close()