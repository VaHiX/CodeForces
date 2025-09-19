# Contest 2071, Problem A: The Play Never Ends
# URL: https://codeforces.com/contest/2071/problem/A

for k in [*open(0)][1:]:
    print("YNEOS"[int(k) % 3 != 1 :: 2])
