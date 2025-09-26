# Contest 1742, Problem A: Sum
# URL: https://codeforces.com/contest/1742/problem/A

for s in [*open(0)][1:]:
    a, b, c = sorted(map(int, s.split()))
    print("YNEOS"[a + b != c :: 2])
