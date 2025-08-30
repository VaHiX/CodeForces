# Contest 2102, Problem B: The Picky Cat
# URL: https://codeforces.com/contest/2102/problem/B

for s in [*open(0)][2::2]:
    a = (*map(abs, map(int, s.split())),)
    print("YNEOS"[sum(x < a[0] for x in a) * 2 > len(a) :: 2])
