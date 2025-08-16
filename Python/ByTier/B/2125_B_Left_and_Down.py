# Contest 2125, Problem B: Left and Down
# URL: https://codeforces.com/contest/2125/problem/B

import math
for s in[*open(0)][1:]:*a,k=map(int,s.split());print(1+(max(*a)>math.gcd(*a)*k))