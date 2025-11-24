# Problem: CF 1899 G - Unusual Entertainment
# https://codeforces.com/contest/1899/problem/G

"""
Fenwick Tree (Binary Indexed Tree) implementation for range queries and updates.
Time Complexity: O(log n) for update and query operations
Space Complexity: O(n)
"""

import sys


class Fenw:
    def __init__(self, size):
        self.n = size
        self.tree = [0] * (self.n + 1)

    def update(self, index, delta):
        i = index + 1
        while i <= self.n:
            self.tree[i] += delta
            i += i & -i

    def query(self, index):
        i = index + 1
        s = 0
        while i:
            s += self.tree[i]
            i -= i & -i
        return s

    def range_query(self, l, r):
        if l > r:
            return 0
        res = self.query(r)
        if l > 0:
            res -= self.query(l - 1)
        return res


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    out_lines = []
    for _ in range(t):
        n = int(data[index])
        q = int(data[index + 1])
        index += 2
        graph = [[] for _ in range(n)]
        for _ in range(n - 1):
            u = int(data[index])
            v = int(data[index + 1])
            index += 2
            u -= 1
            v -= 1
            graph[u].append(v)
            graph[v].append(u)

        p = list(map(int, data[index : index + n]))
        index += n

        parent = [-1] * n
        in_time_arr = [0] * n
        out_time_arr = [0] * n
        next_child = [0] * n
        stack = [0]
        parent[0] = -1
        timer = 0

        # DFS to compute in-time and out-time for each node
        while stack:
            u = stack[-1]
            if next_child[u] == 0:
                in_time_arr[u] = timer
                timer += 1
            if next_child[u] < len(graph[u]):
                v = graph[u][next_child[u]]
                next_child[u] += 1
                if parent[u] == v:
                    continue
                parent[v] = u
                stack.append(v)
            else:
                out_time_arr[u] = timer - 1
                stack.pop()

        # Create position array to map vertex to its position in permutation
        pos_arr = [0] * (n + 1)
        for idx, vertex in enumerate(p):
            pos_arr[vertex] = idx

        events = []
        # Add events for each vertex in the permutation
        for v in range(1, n + 1):
            internal_index = v - 1
            x_coord = pos_arr[v]
            y_coord = in_time_arr[internal_index]
            events.append((x_coord, 0, y_coord))

        queries = []
        for i in range(q):
            l = int(data[index])
            r = int(data[index + 1])
            x = int(data[index + 2])
            index += 3
            internal_x = x - 1
            L0 = in_time_arr[internal_x]
            R0 = out_time_arr[internal_x]
            l0 = l - 1
            r0 = r - 1
            # Prepare events for range query on subtree
            events.append((r0, 1, L0, R0, i))
            events.append((l0 - 1, 2, L0, R0, i))
            queries.append((l0, r0, L0, R0))

        # Sort events by x-coordinate and type
        events.sort(key=lambda x: (x[0], x[1]))

        fenw = Fenw(timer)
        res_r = [0] * q
        res_l = [0] * q

        # Process all events
        for event in events:
            if event[1] == 0:
                # Insert vertex into Fenwick tree
                x_coord, _, y_coord = event
                fenw.update(y_coord, 1)
            else:
                # Query range for subtree
                x_coord, type_flag, L0, R0, q_idx = event
                total = fenw.range_query(L0, R0)
                if type_flag == 1:
                    res_r[q_idx] = total
                else:
                    res_l[q_idx] = total

        # Compare results to determine if descendant exists
        for i in range(q):
            if res_r[i] - res_l[i] > 0:
                out_lines.append("YES")
            else:
                out_lines.append("NO")

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/