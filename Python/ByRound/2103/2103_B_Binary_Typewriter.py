# Contest 2103, Problem B: Binary Typewriter
# URL: https://codeforces.com/contest/2103/problem/B

for s in [*open(0)][2::2]:
    k = s.count("10") * 2 + int(s[-2])
    print(len(s) + k - (k > 1) - (k > 2) - 1)
