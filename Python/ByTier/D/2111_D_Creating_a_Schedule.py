# Contest 2111, Problem D: Creating a Schedule
# URL: https://codeforces.com/contest/2111/problem/D

[
    (
        lambda n, m, rooms: print(
            "\n".join(
                [
                    (
                        f"{rooms[i]} {rooms[m - i - 1]} " * 3
                        + "\n"
                        + f"{rooms[m - i - 1]} {rooms[i]} " * 3
                    )
                    for i in range(n // 2)
                ]
            )
            + (f"\n{rooms[n // 2]} {rooms[m - (n // 2) - 1]} " * 3 if n % 2 else "")
        )
    )(*map(int, input().split()), sorted(list(map(int, input().split()))))
    for _ in range(int(input()))
]
