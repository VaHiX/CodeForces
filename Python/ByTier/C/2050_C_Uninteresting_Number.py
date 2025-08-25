# Contest 2050, Problem C: Uninteresting Number
# URL: https://codeforces.com/contest/2050/problem/C

for *n, _ in [*open(0)][1:]:
    f = n.count
    s = sum(map(int, n))
    print("NYOE S"[0 <= f("2") - s % 3 >= (s + s % 3 * 2) % 9 - f("3") * 3 :: 2])
