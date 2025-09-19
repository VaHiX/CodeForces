# Contest 2075, Problem A: To Zero
# URL: https://codeforces.com/contest/2075/problem/A

for s in [*open(0)][1:]:
    n, k = map(int, s.split())
    print(1 - (k - n) // ~-k)
