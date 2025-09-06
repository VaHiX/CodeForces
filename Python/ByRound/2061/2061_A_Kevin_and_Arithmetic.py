# Contest 2061, Problem A: Kevin and Arithmetic
# URL: https://codeforces.com/contest/2061/problem/A

for s in [*open(0)][2::2]:
    a = s.split()
    m = sum(int(x) % 2 for x in a)
    print(m + (m < len(a)) * 2 - 1)
