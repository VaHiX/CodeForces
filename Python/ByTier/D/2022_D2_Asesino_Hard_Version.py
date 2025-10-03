# Contest 2022, Problem D2: Asesino (Hard Version)
# URL: https://codeforces.com/contest/2022/problem/D2

import sys
#import random,os
#from math import ceil,floor,gcd,lcm,sqrt,isqrt #, log, factorial, comb, perm,
#log10, log2, log, sin, asin, tan, atan, radians
#from collections import defaultdict as dd
#from collections import OrderedDict as Od  #ordered set
#from collections import Counter
#from collections import deque as dq #deque  e.g. myqueue=dq(list)
#from bisect import * #bisect_left, bisect(a,value)
#from heapq import * #heappop(Q),heappush,heapify,Q[0] is smallest
#from itertools import permutations(p,r)#combinations(p,r)
#combinations(p,r) gives r-length tuples #combinations_with_replacement
#sys.setrecursionlimit(100000) #default is 1000 
# input = BytesIO(os.read(0, os.fstat(0).st_size)).readline
input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))
###############################################
def query(x, y):
    print('?', x, y,  flush=True)
    return sint()
def answer(x):
    print('!', x, flush=True)
T = sint()
for _ in range(T):
    n=sint()
    while n>5:
        if query(n-1,n)+query(n,n-1)==1:answer(n if query(1,n)+query(n,1)==1 else n-1);break
        else:n-=2
    else:
        if n==3:
            if query(1,2)+query(2,1)==1:
                answer(1 if query(1,n)+query(n,1)==1 else 2)
            else:
                answer(n)
        elif n==4:
            if query(1,2)+query(2,1)==1:
                answer(1 if query(1,n)+query(n,1)==1 else 2)
            else:
                answer(n if query(1,n)+query(n,1)==1 else 3)
        else:
            v=[query(1,2),query(2,3),query(3,1)]
            if sum(v)%2:
                answer(n if query(1,n)+query(n,1)==1 else 4)
            else:
                if v[0]+query(2,1)==1:
                    answer(1 if query(1,3)+v[2]==1 else 2)
                else:
                    answer(3)
