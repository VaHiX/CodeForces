# Problem: CF 2032 D - Genokraken
# https://codeforces.com/contest/2032/problem/D

"""
根據條件 1 ，這個樹會是根節點 0 連接若干個子樹，每個子樹都是一條鏈
根據條件 2 ，這個樹會依照 Level-order 的順序編號
根據條件 3 ，節點 1 的子樹大小至少為 2

由於節點 1 一定有恰好 1 個子節點，所以可以利用條件 2，找到節點 1 的子節點
- 若 query(1, u) == 1，表示 1 和 u 會經過根節點 0，所以 u 是 0 的另一個子節點
- 若 query(1, u) == 0，表示 1 和 u 不會經過根節點 0，所以 u 是 1 的子節點

之後對於 queue 中的每個節點，都會有兩種情況
- 若 query(q[0], u) == 0，表示 u 是 q[0] 的子節點
- 若 query(q[0], u) == 1，表示 u 不是 q[0] 的子節點，且 q[0] 不會再有其他子節點

時間複雜度: O(n^2) 最壞情況下需要進行 n-2 次查詢，每查詢一次最多遍歷所有節點
空間複雜度: O(n) 用於存儲 parent 陣列和 deque
"""

import sys
from collections import deque

input = lambda: sys.stdin.readline().strip()


def query(x, y):
    print(f"? {x } {y }", flush=True)
    return int(input())


def answer(A):
    print("!", *A, flush=True)


t = int(input())
for _ in range(t):
    n = int(input())
    fa = [0] * n
    fa[1] = 0

    q = deque([1])
    u = 2

    # 處理節點 1 的子節點
    while u < n and q[0] == 1:
        if query(1, u) == 1:
            fa[u] = 0
        else:
            fa[u] = 1
            q.popleft()  # 出隊，因節點 1 的一個子節點已確定
        q.append(u)      # 將 u 加入隊列，作為待處理節點
        u += 1

    # 處理剩下的節點
    while u < n:
        if query(q[0], u) == 0:
            fa[u] = q[0]     # u 是 q[0] 的子節點
            q.append(u)      # 將 u 加入隊列
            u += 1
        q.popleft()          # 移除已處理的節點

    answer(fa[1:])


# https://github.com/VaHiX/CodeForces/