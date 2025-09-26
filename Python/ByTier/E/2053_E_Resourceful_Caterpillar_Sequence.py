# Contest 2053, Problem E: Resourceful Caterpillar Sequence
# URL: https://codeforces.com/contest/2053/problem/E

# ruff: noqa: E731, E741
import sys

read = sys.stdin.readline
input = lambda: read().rstrip()
ir = lambda: int(read())
rir = lambda: range(int(read()))
mir = lambda: map(int, read().split())
lmir = lambda: list(map(int, read().split()))


def solve():
    n = ir()
    tree = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = mir()
        tree[u - 1].append(v - 1)
        tree[v - 1].append(u - 1)

    is_leaf = [len(nbs) == 1 for nbs in tree]
    near = [
        i
        for i, nbs in enumerate(tree)
        if not is_leaf[i] and any(map(is_leaf.__getitem__, nbs))
    ]
    num_leaves = sum(is_leaf)
    num_far = n - num_leaves - len(near)
    turn0 = num_leaves * (n - num_leaves)
    turn1 = num_far * (sum(not is_leaf[j] for i in near for j in tree[i]) - len(near))
    print(turn0 + turn1)


def main():
    for _ in rir():
        solve()


if __name__ == "__main__":
    main()
