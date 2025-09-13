# Contest 2133, Problem A: Redstone?
# URL: https://codeforces.com/contest/2133/problem/A

for s in [*open(0)][2::2]:
    x = s.strip().split(" ")
    print("YNEOS"[len(list(set(x))) == len(x) :: 2])
