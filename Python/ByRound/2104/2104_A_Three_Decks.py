# Contest 2104, Problem A: Three Decks
# URL: https://codeforces.com/contest/2104/problem/A

for s in [*open(0)][1:]:
    a, b, c = map(int, s.split())
    c += a + b
    print("YNEOS"[0 < c % 3 or b * 3 > c :: 2])
