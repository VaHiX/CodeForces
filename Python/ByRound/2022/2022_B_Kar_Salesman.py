# Contest 2022, Problem B: Kar Salesman
# URL: https://codeforces.com/contest/2022/problem/B

import math
for i in range(int(input())):
    n, x = map(int, input().split())
    a = [int(x) for x in input().split()]
    print(max(max(a), math.ceil(sum(a)/x)))