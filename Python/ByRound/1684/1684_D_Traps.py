# Contest 1684, Problem D: Traps
# URL: https://codeforces.com/contest/1684/problem/D

for _ in range(int(input())):
    print(
        [
            sum(sorted([u[1][i] + i for i in range(u[0][0])])[: u[0][0] - u[0][1]])
            - ((u[0][0] - u[0][1]) * ((u[0][0] - u[0][1]) - 1)) // 2
            for u in [
                [list(map(int, input().split())), list(map(int, input().split()))]
            ]
        ][0]
    )
