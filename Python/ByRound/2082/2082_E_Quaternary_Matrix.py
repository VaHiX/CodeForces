# Problem: CF 2082 E - Quaternary Matrix
# https://codeforces.com/contest/2082/problem/E

"""
E. Quaternary Matrix

Problem Description:
Given a quaternary matrix (elements 0, 1, 2, 3), find the minimum number of elements to change to make it "good".
A matrix is good if:
- XOR of all numbers in each row equals 0.
- XOR of all numbers in each column equals 0.

Algorithm:
The approach uses a greedy method with bit manipulation:
1. For each row/column, compute XOR of its elements.
2. Create lists for rows/columns with non-zero XOR values.
3. Match these "bad" rows and columns to minimize changes by pairing them up.
4. Handle remaining mismatches carefully to ensure final matrix is good.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

"""
def solve():
    import sys

    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    pos = 1
    out_lines = []
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        m = int(data[pos])
        pos += 1
        # Initialize matrix and XOR tracking arrays
        a = [[0] * m for _ in range(n)]
        rx = [0] * n  # row XORs
        cx = [0] * m  # column XORs
        rv = [[] for _ in range(4)]  # rows with specific XOR values (1 to 3)
        cv = [[] for _ in range(4)]  # columns with specific XOR values (1 to 3)
        for i in range(n):
            s = data[pos]
            pos += 1
            for j, ch in enumerate(s):
                a[i][j] = int(ch)
                rx[i] ^= a[i][j]  # accumulate row XOR
                cx[j] ^= a[i][j]  # accumulate column XOR
        # Store indices of rows/columns with non-zero XOR
        for i in range(n):
            if rx[i]:
                rv[rx[i]].append(i)
        for j in range(m):
            if cx[j]:
                cv[cx[j]].append(j)
        ans = 0  # count of changes needed
        rV = []  # values of rows with non-zero XOR
        cV = []  # values of columns with non-zero XOR
        # Pair up rows and columns with same XOR values to minimize changes
        for x in range(1, 4):
            while rv[x] and cv[x]:
                ans += 1
                i_idx = rv[x].pop()  # row index
                j_idx = cv[x].pop()  # column index
                a[i_idx][j_idx] ^= x  # change value at intersection
        # If remaining, store which values have unmatched rows or columns
        for x in range(1, 4):
            if rv[x]:
                rV.append(x)
            if cv[x]:
                cV.append(x)
        # Handle cases where we can reduce further by pairing two sets of mismatches
        if rV and cV:
            if len(cV) == 2:
                i_val = rV[0]  # XOR value of remaining rows
                j_val = cV[0]  # XOR values of columns
                k_val = cV[1]
                while rv[i_val] and cv[j_val] and cv[k_val]:
                    ans += 2
                    i_idx = rv[i_val].pop()
                    j_idx = cv[j_val].pop()
                    k_idx = cv[k_val].pop()
                    a[i_idx][j_idx] ^= j_val
                    a[i_idx][k_idx] ^= k_val
            elif len(rV) == 2:
                i_val = cV[0]
                j_val = rV[0]
                k_val = rV[1]
                while cv[i_val] and rv[j_val] and rv[k_val]:
                    ans += 2
                    j_idx = rv[j_val].pop()
                    k_idx = rv[k_val].pop()
                    i_idx = cv[i_val].pop()
                    a[j_idx][i_idx] ^= j_val
                    a[k_idx][i_idx] ^= k_val
        # Handle remaining mismatches by making one final adjustment
        i_val = -1
        j_val = -1
        for x in range(1, 4):
            if rv[x]:
                i_val = x
            if cv[x]:
                j_val = x
        if i_val != -1 and j_val != -1:
            while rv[i_val] and cv[j_val]:
                i1 = rv[i_val].pop()
                i2 = rv[i_val].pop()  # pick two rows
                j1 = cv[j_val].pop()
                j2 = cv[j_val].pop()  # pick two columns
                ans += 3
                a[i2][j1] ^= i_val
                a[i1][j2] ^= j_val
                a[i1][j1] ^= i_val ^ j_val  # ensure final consistency
        # Adjust any remaining row/column mismatches by changing first element of each
        for x in range(1, 4):
            for i in rv[x]:  # if rows have non-zero XOR
                ans += 1
                a[i][0] ^= x  # change first column element of that row
            for j in cv[x]:  # if columns have non-zero XOR
                ans += 1
                a[0][j] ^= x  # change first row element of that column
        out_lines.append(str(ans))
        for i in range(n):
            out_lines.append("".join(str(x) for x in a[i]))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/