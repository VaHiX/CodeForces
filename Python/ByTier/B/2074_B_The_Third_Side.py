# Contest 2074, Problem B: The Third Side
# URL: https://codeforces.com/contest/2074/problem/B

for s in [*open(0)][2::2]:
    print(sum(map(int, a := s.split())) - len(a) + 1)
