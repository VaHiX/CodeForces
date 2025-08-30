# Contest 2067, Problem A: Adjacent Digit Sums
# URL: https://codeforces.com/contest/2067/problem/A

for s in [*open(0)][1:]:
    x, y = map(int, s.split())
    y -= x
    print("NYoe s"[y <= 1 == y % 9 :: 2])
