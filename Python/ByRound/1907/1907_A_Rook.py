# Contest 1907, Problem A: Rook
# URL: https://codeforces.com/contest/1907/problem/A

for x, y, _ in [*open(0)][1:]:
    print(*{u + y for u in "abcdefgh"} ^ {x + u for u in "12345678"})
