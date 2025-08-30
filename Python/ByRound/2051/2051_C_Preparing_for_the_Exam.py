# Contest 2051, Problem C: Preparing for the Exam
# URL: https://codeforces.com/contest/2051/problem/C

lines = [list(map(int, line.strip().split())) for line in open(0).readlines()[1:]]
t = len(lines)

for i in range(0, t, 3):
    n, m, k = lines[i]
    ans = sum(lines[i + 2])
    qs = n * (n + 1) // 2
    if k == n:
        print("1" * m)
    elif k <= n - 2:
        print("0" * m)
    else:
        for mq in lines[i + 1]:
            if qs - mq == ans:
                print("1", end="")
            else:
                print("0", end="")
        print()
