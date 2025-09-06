# Contest 598, Problem A: Tricky Sum
# URL: https://codeforces.com/contest/598/problem/A

import math
for i in range(int(input())):
    q = int(input())
    w=int(math.log2(q))
    p = (2**(w+1))-1
    k = q*(q+1)//2
    print(k-p*2)