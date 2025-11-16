# Problem: CF 2145 E - Predicting Popularity
# https://codeforces.com/contest/2145/problem/E

"""
Algorithm: Segment Tree with Binary Search
Purpose: Predict movie popularity by simulating a process where users watch a movie
         if it meets their preference thresholds and the movie becomes suitable for
         more users as the popularity increases.
Time Complexity: O(m * log(n)) where m is the number of updates and n is the number of users.
Space Complexity: O(n) for the segment tree storage.
"""

import sys


def solve():
    data = sys.stdin.buffer.read().split()
    it = (int(token) for token in data)
    ac = next(it)
    dr = next(it)
    n = next(it)
    a_values = [next(it) for _ in range(n)]
    d_values = [next(it) for _ in range(n)]
    m = next(it)
    size = 1
    total_slots = n + 1
    while size < total_slots:
        size <<= 1
    INF = 10**15
    seg_sum = [0] * (2 * size)
    seg_min = [INF] * (2 * size)
    for idx in range(total_slots):
        pos = size + idx
        seg_sum[pos] = -1
        seg_min[pos] = -1
    for pos in range(size - 1, 0, -1):
        left = pos << 1
        right = left | 1
        seg_sum[pos] = seg_sum[left] + seg_sum[right]
        seg_min[pos] = min(seg_min[left], seg_sum[left] + seg_min[right])

    def seg_add(index, delta):
        if index < 0 or index >= total_slots:
            return
        position = size + index
        seg_sum[position] += delta
        seg_min[position] += delta
        position >>= 1
        while position:
            left = position << 1
            right = left | 1
            seg_sum[position] = seg_sum[left] + seg_sum[right]
            seg_min[position] = min(seg_min[left], seg_sum[left] + seg_min[right])
            position >>= 1

    def first_negative_prefix() -> int:
        if seg_min[1] >= 0:
            return total_slots
        prefix = 0
        node = 1
        while node < size:
            left = node << 1
            right = left | 1
            if seg_min[left] + prefix < 0:
                node = left
            else:
                prefix += seg_sum[left]
                node = right
        result = node - size
        return result if result <= n else n

    def deficit_score(a_val, d_val):
        return max(a_val - ac, 0) + max(d_val - dr, 0)

    current_scores = [0] * n
    for idx in range(n):
        score = deficit_score(a_values[idx], d_values[idx])
        current_scores[idx] = score
        if score <= n:
            seg_add(score, 1)
    outputs = []
    for _ in range(m):
        user_index = next(it) - 1
        new_a = next(it)
        new_d = next(it)
        old_score = current_scores[user_index]
        if old_score <= n:
            seg_add(old_score, -1)
        updated_score = deficit_score(new_a, new_d)
        current_scores[user_index] = updated_score
        if updated_score <= n:
            seg_add(updated_score, 1)
        watchers = first_negative_prefix()
        outputs.append(str(watchers))
    sys.stdout.write("\n".join(outputs))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/