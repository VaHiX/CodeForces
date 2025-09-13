# Contest 2137, Problem B: Fun Permutation
# URL: https://codeforces.com/contest/2137/problem/B

for s in [*open(0)][2::2]:
    a = s.split()
    for x in a:
        print(len(a) + 1 - int(x))
