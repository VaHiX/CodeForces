# Problem: CF 2169 E - Points Selection
# https://codeforces.com/contest/2169/problem/E

"""
Author: Rahul Samant
Created: 2025-11-14 20:39:16

Problem: Points Selection
Approach:
- This problem is a min-max optimization game.
- Alice picks points to remove (minimize score), Bob picks rectangle (minimize score).
- The total score = sum of removed point costs + rectangle perimeter.
- The key insight: Bob will always choose a rectangle that bounds all remaining points with minimal perimeter.
- For a fixed set of points to remove, we can compute the minimal rectangle perimeter for the remaining points.
- The idea is to iterate over all partitions of 4 masks (0-15) representing which points are selected for bounding rectangle.
- Use pruning to avoid computing all combinations.
- Time and Space Complexity:
    - Time Complexity: O(3^4 * n * log n) due to bitmask partitions and sorting.
    - Space Complexity: O(n + 16 * K) where K=6, for storing candidates and masks.
Algorithms/Techniques:
- Bitmask Dynamic Programming with pruning
- Min-Max Game Theory
- Sliding window-like logic with candidate selection for optimal rectangle
"""

import sys

_tokens = iter(sys.stdin.buffer.read().split())


def read_int() -> int:
    return int(next(_tokens))


K = 6


def _generate_partitions(bits: int):
    if bits == 0:
        yield ()
        return
    lsb = bits & -bits
    remaining = bits ^ lsb
    sub = remaining
    while True:
        mask = sub | lsb
        for tail in _generate_partitions(bits ^ mask):
            yield (mask,) + tail
        if sub == 0:
            break
        sub = (sub - 1) & remaining


PARTITIONS = tuple(_generate_partitions(0b1111))  # Precomputed partitions of 4 masks (0..15)
MASKS = tuple(range(1, 16))  # All non-empty subsets of 4 bits (mask 0 not included)
COEFF_X = [int(bool(mask & 1)) - int(bool(mask & 2)) for mask in range(16)]  # X coefficient for each mask
COEFF_Y = [int(bool(mask & 4)) - int(bool(mask & 8)) for mask in range(16)]  # Y coefficient for each mask


def push_candidate(bucket: list, value: int, idx: int) -> None:
    # Maintain top K candidates sorted descending by value
    if len(bucket) == K and value <= bucket[-1][0]:
        return
    pos = len(bucket)
    while pos > 0 and bucket[pos - 1][0] < value:
        pos -= 1
    bucket.insert(pos, (value, idx))
    if len(bucket) > K:
        bucket.pop()


def solve() -> None:
    t = read_int()
    out_lines: list[str] = []

    for _ in range(t):
        n = read_int()
        xs = [read_int() for _ in range(n)]
        ys = [read_int() for _ in range(n)]
        cs = [read_int() for _ in range(n)]

        total_cost = sum(cs)
        top = [[] for _ in range(16)]  # Store top candidates for each mask

        # Preprocess points into candidate sets based on masks
        for idx in range(n):
            x2 = xs[idx] << 1  # Multiply x by 2 to avoid floating point issues
            y2 = ys[idx] << 1  # Multiply y by 2 to avoid floating point issues
            base = -cs[idx]  # Negate cost for maximizing total (as we want to minimize net penalty)
            for mask in MASKS:
                value = base + COEFF_X[mask] * x2 + COEFF_Y[mask] * y2
                push_candidate(top[mask], value, idx)

        best = -(10**30)  # Initialize best score to very small value
        used = [False] * n  # Track which points are used in current subset

        # Check all possible partitions of mask set
        for masks in PARTITIONS:
            if any(not top[mask] for mask in masks):
                continue  # Skip if any subset has no valid candidates

            def dfs(pos: int, acc: int) -> None:
                nonlocal best
                if pos == len(masks):
                    if acc > best:
                        best = acc
                    return

                mask = masks[pos]
                for value, idx in top[mask]:
                    if used[idx]:
                        continue
                    used[idx] = True
                    dfs(pos + 1, acc + value)
                    used[idx] = False

            dfs(0, 0)

        out_lines.append(str(total_cost + best))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/