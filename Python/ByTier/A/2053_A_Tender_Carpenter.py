# Contest 2053, Problem A: Tender Carpenter
# URL: https://codeforces.com/contest/2053/problem/A

for s in [*open(0)][2::2]:
    a = (*map(int, s.split()),)
    print("YNEOS"[all(2 * min(x) <= max(x) for x in zip(a, a[1:])) :: 2])
