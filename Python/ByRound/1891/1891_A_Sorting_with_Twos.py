# Contest 1891, Problem A: Sorting with Twos
# URL: https://codeforces.com/contest/1891/problem/A

for s in [*open(0)][2::2]:
    (*a,) = map(int, s.split())
    print("YNEOS"[any(sorted(x := a[1 << i : 1 << i + 1]) < x for i in range(5)) :: 2])
