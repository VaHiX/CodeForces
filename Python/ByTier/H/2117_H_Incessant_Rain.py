# Contest 2117, Problem H: Incessant Rain
# URL: https://codeforces.com/contest/2117/problem/H

from sys import stdin
input = stdin.readline
inputlist = lambda: map(int, stdin.readline().split())
import heapq

def merge(a0, a1, a2, a3, b0, b1, b2, b3):
    best = max(a0, b0, a2 + b1)
    left = max(a1, a3 + b1)
    right = max(b2, b3 + a2)
    total = a3 + b3
    return best, left, right, total

class SegmentTree:
    def __init__(self, n):
        self.n = 1
        while self.n < n:
            self.n <<= 1
        self.tree = [0] * (8 * self.n) 

        base_pos = 4 * self.n
        for i in range(n):
            pos = base_pos + 4 * i
            self.tree[pos] = -1
            self.tree[pos+1] = -1
            self.tree[pos+2] = -1
            self.tree[pos+3] = -1
        for i in range(n, self.n):
            pos = base_pos + 4 * i
            self.tree[pos] = 0
            self.tree[pos+1] = 0
            self.tree[pos+2] = 0
            self.tree[pos+3] = 0

        for i in range(self.n - 1, 0, -1):
            left = 4 * (2 * i)
            right = 4 * (2 * i + 1)
            best, left_val, right_val, total = merge(
                self.tree[left], self.tree[left+1], self.tree[left+2], self.tree[left+3],
                self.tree[right], self.tree[right+1], self.tree[right+2], self.tree[right+3]
            )
            pos = 4 * i
            self.tree[pos] = best
            self.tree[pos+1] = left_val
            self.tree[pos+2] = right_val
            self.tree[pos+3] = total

    def update(self, index, value):
        pos = 4 * (index + self.n)
        self.tree[pos] = value
        self.tree[pos+1] = value
        self.tree[pos+2] = value
        self.tree[pos+3] = value
        index = (index + self.n) // 2

        while index >= 1:
            left = 4 * (2 * index)
            right = 4 * (2 * index + 1)
            best, left_val, right_val, total = merge(
                self.tree[left], self.tree[left+1], self.tree[left+2], self.tree[left+3],
                self.tree[right], self.tree[right+1], self.tree[right+2], self.tree[right+3]
            )
            pos = 4 * index
            self.tree[pos] = best
            self.tree[pos+1] = left_val
            self.tree[pos+2] = right_val
            self.tree[pos+3] = total
            index //= 2

    def query(self):
        return self.tree[4]

def solve():
    n, q = inputlist()
    a = list(inputlist())

    start = [[] for _ in range(n + 1)]
    for i, val in enumerate(a):
        start[val].append(i)

    queries = [[] for _ in range(n + 1)]
    query_details_i = [0] * q
    
    for idx in range(q):
        i, num = inputlist()
        i -= 1 
        query_details_i[idx] = i
        if num != a[i]:
            queries[a[i]].append(~idx)
            queries[num].append(idx)
            a[i] = num

    query_op_effects = [[] for _ in range(q)]

    segtree = SegmentTree(n)

    k_counts = [0] * (n // 2 + 1)

    for val_proc in range(1, n + 1):
        if not start[val_proc] and not queries[val_proc]:
            k_counts[0] += 1
            continue

        for arr_idx in start[val_proc]:
            segtree.update(arr_idx, 1)

        current_k_val_tree = segtree.query()
        k_counts[max(0, current_k_val_tree // 2)] += 1

        for query_log_entry in queries[val_proc]:
            is_addition = query_log_entry >= 0
            query_idx = query_log_entry if is_addition else ~query_log_entry

            k_before_update_tree = segtree.query()
            query_op_effects[query_idx].append(~max(0, k_before_update_tree // 2))

            arr_idx_to_change = query_details_i[query_idx]
            leaf_val_for_update = 1 if is_addition else -1
            segtree.update(arr_idx_to_change, leaf_val_for_update)

            k_after_update_tree = segtree.query()
            query_op_effects[query_idx].append(max(0, k_after_update_tree // 2))

        if queries[val_proc]:
            for query_log_entry in reversed(queries[val_proc]):
                is_addition = query_log_entry >= 0 
                query_idx = query_log_entry if is_addition else ~query_log_entry

                arr_idx_to_change = query_details_i[query_idx]
                leaf_val_for_revert = -1 if is_addition else 1
                segtree.update(arr_idx_to_change, leaf_val_for_revert)

        if start[val_proc]: 
            for arr_idx in start[val_proc]:
                segtree.update(arr_idx, -1)

    results = [0] * q
    active_k_heap = []

    for k_val in range(n // 2, -1, -1): 
        if k_counts[k_val] > 0:
            heapq.heappush(active_k_heap, -k_val)

    for query_idx in range(q):
        for op_effect in query_op_effects[query_idx]:
            is_increment = op_effect >= 0
            k_val_affected = op_effect if is_increment else ~op_effect

            if is_increment:
                k_counts[k_val_affected] += 1
                if k_counts[k_val_affected] == 1: 
                    heapq.heappush(active_k_heap, -k_val_affected)
            else: 
                k_counts[k_val_affected] -= 1

        while active_k_heap and k_counts[-active_k_heap[0]] == 0:
            heapq.heappop(active_k_heap)

        if active_k_heap:
            results[query_idx] = -active_k_heap[0]
        else:
            results[query_idx] = 0 

    return results

for _ in range(int(input())):
    print(*solve())
