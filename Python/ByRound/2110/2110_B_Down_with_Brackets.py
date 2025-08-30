# Contest 2110, Problem B: Down with Brackets
# URL: https://codeforces.com/contest/2110/problem/B

for s in [*open(0)][1:]:
    c = 0
    print("YNEOS"[all(c := c + 81 - 2 * ord(x) for x in s[:-2]) :: 2])
