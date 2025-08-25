# Contest 2047, Problem A: Alyona and a Square Jigsaw Puzzle
# URL: https://codeforces.com/contest/2047/problem/A

for s in [*open(0)][2::2]:
    t = 0
    print(sum((t := t + int(x)) ** 0.5 % 2 == 1 for x in s.split()))
