# Contest 2109, Problem A: It's Time To Duel
# URL: https://codeforces.com/contest/2109/problem/A

for s in [*open(0)][2::2]:
    print("YNEOS"[("0" in s) > ("0 0" in s) :: 2])
