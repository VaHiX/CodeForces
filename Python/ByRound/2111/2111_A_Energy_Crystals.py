# Contest 2111, Problem A: Energy Crystals
# URL: https://codeforces.com/contest/2111/problem/A

for x in [*open(0)][1:]:
    print(len(bin(int(x))) * 2 - 3)
