# Contest 2048, Problem A: Kevin and Combination Lock
# URL: https://codeforces.com/contest/2048/problem/A

for i in [*open(0)][1:]:
    print("YNEOS"[int(i) % 33 > 0 :: 2])
