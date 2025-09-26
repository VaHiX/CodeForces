# Contest 2034, Problem A: King Keykhosrow's Mystery
# URL: https://codeforces.com/contest/2034/problem/A

import math

for _ in range(int(input())):
    n, m = map(int, input().split())
    print(math.lcm(n, m))
