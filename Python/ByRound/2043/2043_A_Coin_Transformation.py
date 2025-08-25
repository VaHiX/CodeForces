# Contest 2043, Problem A: Coin Transformation
# URL: https://codeforces.com/contest/2043/problem/A

for n in [*open(0)][1:]:
    print(1 << (len(bin(int(n))) - 3) // 2)
