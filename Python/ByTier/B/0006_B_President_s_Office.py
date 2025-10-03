# Contest 6, Problem B: President's Office
# URL: https://codeforces.com/contest/6/problem/B

row_count, column_count, p_c = input().lower().split()
row_count, column_count = int(row_count), int(column_count)
mat = [list(input().lower()) for i in range(row_count)]
acc_colors = set()
p_indexes = [
    (i, j) for i in range(len(mat)) for j in range(len(mat[i])) if mat[i][j] == p_c
]

for column, row in p_indexes:
    for y, x in (
        (column, row - 1),
        (column, row + 1),
        (column - 1, row),
        (column + 1, row),
    ):

        if y in range(row_count) and x in range(column_count):
            if mat[y][x] not in (p_c, "."):
                acc_colors.add(mat[y][x])
print(len(acc_colors))
