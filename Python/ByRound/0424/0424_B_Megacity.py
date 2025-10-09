# Contest 424, Problem B: Megacity
# URL: https://codeforces.com/contest/424/problem/B

import math
import sys


def main() -> int:
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, s = next(reader)
    values = sorted(
        reader,
        key=lambda x: math.sqrt(x[0] ** 2 + x[1] ** 2),
    )
    t = -1
    for x, y, k in values:
        s += k
        t += 1
        if s >= 1_000_000:
            break

    r = math.sqrt(values[t][0] ** 2 + values[t][1] ** 2) if s >= 1_000_000 else -1
    print(f"{r:.7f}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
