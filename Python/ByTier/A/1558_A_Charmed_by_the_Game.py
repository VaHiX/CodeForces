# Contest 1558, Problem A: Charmed by the Game
# URL: https://codeforces.com/contest/1558/problem/A

for s in [*open(0)][1:]:
    a, b = map(int, s.split())
    s = a + b
    print(len(r := range(d := abs(a - b) // 2, s - d + 1, 2 - s % 2)), *r)
