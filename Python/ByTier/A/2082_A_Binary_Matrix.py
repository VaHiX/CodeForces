# Contest 2082, Problem A: Binary Matrix
# URL: https://codeforces.com/contest/2082/problem/A

print(
    "\n".join(
        map(
            str,
            (
                max(
                    [
                        rc := (rc := rc if i else 0)
                        + ((x := int(input(), 2)).bit_count() & 1)
                        + (cc := (cc := cc if i else 0) ^ x)
                        - cc
                        for i in range(list(map(int, input().split()))[0])
                    ][-1],
                    cc.bit_count(),
                )
                for _ in range(int(input()))
            ),
        )
    )
)
