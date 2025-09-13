# Contest 2092, Problem C: Asuna and the Mosquitoes
# URL: https://codeforces.com/contest/2092/problem/C

for s in [*open(0)][2::2]:
    a = (*map(int, s.split()),)
    k = sum(x % 2 for x in a)
    print((max(a), sum(a) - k + 1)[0 < k < len(a)])
