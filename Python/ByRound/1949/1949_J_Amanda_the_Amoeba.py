# Contest 1949, Problem J: Amanda the Amoeba
# URL: https://codeforces.com/contest/1949/problem/J


"""

3 7
.*..X..
**X.X..
**X....

....X*.
..X.X**
..X..**


"""

DEBUG = False


def printmap(f, change, name=None):
    if name:
        print(name)
    for y in range(r):
        for x in range(c):
            print(change(f[y][x], x, y), end="")
        print()
    print()


def pmd(f, d, name=None):
    printmap(f, lambda v, x, y: d[v], name)


def printdir(f, name=None):
    printmap(
        f,
        lambda v, x, y: (
            "0"
            if v == 0
            else (
                "."
                if v is None
                else ">" if v[0] > x else "<" if v[0] < x else "^" if v[1] < y else "v"
            )
        ),
        name,
    )


def printor(f1, f2, name=None):
    printmap(f1, lambda v, x, y: {0: ".", 1: "*", 2: "*", 3: "!"}[v + 2 * f2[y][x]])


def main():
    global r, c
    r, c = map(int, input().split())

    MOVES = []

    initial = [[False] * c for y in range(r)]
    final = [[False] * c for y in range(r)]
    rock = [[False] * c for y in range(r)]

    for y in range(r):
        l = input()
        for x in range(c):
            if l[x] == "X":
                rock[y][x] = True
            elif l[x] == "*":
                initial[y][x] = True
    input()

    for y in range(r):
        l = input()
        for x in range(c):
            if l[x] == "*":
                final[y][x] = True
                start = (x, y)

    if DEBUG:
        pmd(initial, {True: "*", False: "."}, "INITIAL")
        pmd(final, {True: "*", False: "."}, "FINAL")
        pmd(rock, {True: "X", False: "."}, "ROCK")

    # find path between blobs that does not contain either blob in between those points (dfs)

    # start=(x,y) # some node in final
    active = [start]
    parent = [[None] * c for y in range(r)]

    parent[start[1]][start[0]] = 0

    end = None
    while active:
        x, y = active.pop(-1)
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            if (
                0 <= x + dx < c
                and 0 <= y + dy < r
                and parent[y + dy][x + dx] is None
                and not rock[y + dy][x + dx]
            ):
                parent[y + dy][x + dx] = (x, y)
                active.append((x + dx, y + dy))
        if final[y][x]:
            parent[y][x] = 0
        if initial[y][x]:
            end = (x, y)
            break

    # check if succeeded
    if end is None:
        print("NO")
        return
    print("YES")

    # children
    children = [[0] * c for y in range(r)]

    # change start to actual start
    start = end
    while not parent[start[1]][start[0]] in (None, 0):
        start = parent[start[1]][start[0]]
        children[start[1]][start[0]] += 1

    # root FROM-blob towards path
    active = [end]
    seen = [[False] * c for y in range(r)]
    seen[end[1]][end[0]] = True
    leaves = []
    while active:
        x, y = active.pop(-1)

        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            if (
                0 <= x + dx < c
                and 0 <= y + dy < r
                and initial[y + dy][x + dx]
                and not seen[y + dy][x + dx]
            ):
                parent[y + dy][x + dx] = (x, y)
                seen[y + dy][x + dx] = True
                active.append((x + dx, y + dy))
                children[y][x] += 1
        if children[y][x] == 0:
            leaves.append((x, y))

    if DEBUG:
        printdir(parent, "PARENT")
        printmap(children, lambda v, x, y: str(v), "CHILDREN")

        print(leaves)

    # move along that path

    while not initial[start[1]][start[0]]:
        end = parent[end[1]][end[0]]
        initial[end[1]][end[0]] = True

        lx, ly = leaves.pop(-1)
        MOVES.append((lx, ly, end[0], end[1]))
        initial[ly][lx] = False
        px, py = parent[ly][lx]
        children[py][px] -= 1
        if children[py][px] == 0:
            leaves.append((px, py))
        if DEBUG:
            pmd(initial, {True: "*", False: "."}, "INITIAL MOVED")
            print(leaves)

    # fill in TO-blob (move from initial to visited)
    visited = [[False] * c for y in range(r)]
    x, y = start
    visited[y][x] = True
    initial[y][x] = False

    roots = []
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        if 0 <= x + dx < c and 0 <= y + dy < r and final[y + dy][x + dx]:
            roots.append((x + dx, y + dy))

    while roots:
        rx, ry = roots.pop(-1)
        if visited[ry][rx]:
            continue

        if initial[ry][rx]:
            # cut off tree, but don't move anything
            visited[ry][rx] = True
            initial[ry][rx] = False
            p = parent[ry][rx]
            if not p in (0, None):
                px, py = p
                if initial[py][px]:
                    children[py][px] -= 1
                    if children[py][px] == 0:
                        leaves.append((px, py))

        else:
            # move leaf here
            lx, ly = leaves.pop(-1)
            while not initial[ly][lx]:
                lx, ly = leaves.pop(-1)

            visited[ry][rx] = True
            initial[ly][lx] = False
            # update leaves
            p = parent[ly][lx]
            if not p in (0, None):
                px, py = p
                if initial[py][px]:
                    children[py][px] -= 1
                    if children[py][px] == 0:
                        leaves.append((px, py))

            # store move
            MOVES.append((lx, ly, rx, ry))

        # update roots
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            if (
                0 <= rx + dx < c
                and 0 <= ry + dy < r
                and final[ry + dy][rx + dx]
                and not visited[ry + dy][rx + dx]
            ):
                roots.append((rx + dx, ry + dy))

        if DEBUG:
            print("------------------------")
            pmd(initial, {True: "*", False: "."}, "INITIAL")
            pmd(visited, {True: "*", False: "."}, "VISITED")
            printor(initial, visited, "COMBINED")
            print(leaves, roots)

    # print output
    print(len(MOVES))
    for fx, fy, tx, ty in MOVES:
        print(fy + 1, fx + 1, ty + 1, tx + 1)


main()
