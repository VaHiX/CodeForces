# Contest 1743, Problem A: Password
# URL: https://codeforces.com/contest/1743/problem/A

print("\n".join([str(3 * (10 - n) * (9 - n)) for n in map(int, [*open(0)][1::2])]))
