# Contest 2074, Problem C: XOR and Triangle
# URL: https://codeforces.com/contest/2074/problem/C

for x in [*map(int, open(0))][1:]:
    print((-1, b := x & -x | ~x & -~x)[b < x])
