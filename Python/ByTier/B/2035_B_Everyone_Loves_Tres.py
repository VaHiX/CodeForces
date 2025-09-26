# Contest 2035, Problem B: Everyone Loves Tres
# URL: https://codeforces.com/contest/2035/problem/B

for n in [*map(int, open(0))][1:]:
    print((1 != n != 3) - 1 or (n % 2 * "63" + "66").rjust(n, "3"))
