# Problem: CF 1864 G - Magic Square
# https://codeforces.com/contest/1864/problem/G

"""
Magic Square Transformation Problem

Algorithms/Techniques:
- This is a problem involving permutation group theory and graph matching
- We model each element's movement as a shift operation
- We use topological sorting to process row/column shifts in order
- We compute factorials to count the number of valid sequences
- We verify that each element is moved at most twice and the offset constraints are satisfied
- Time complexity is O(n^2) per test case, Space complexity is O(n^2)

Time Complexity: O(n^2) per test case, where n is the size of the matrix
Space Complexity: O(n^2) for storing positions, shifts, and auxiliary data structures
"""

mod = 998244353


def fac(n, memo={}):
    if n in memo:
        return memo[n]
    if n == 0:
        return 1
    result = n * fac(n - 1) % mod
    memo[n] = result
    return result


def solve(n, a, b):
    # Convert values to 0-based indexing
    a = [[v - 1 for v in row] for row in a]
    b = [[v - 1 for v in row] for row in b]
    deltai = [-1] * n
    deltaj = [-1] * n

    # Helper function to get coordinates of elements
    def locs(g):
        l = [-1] * n**2
        for i in range(n):
            for j in range(n):
                assert l[g[i][j]] == -1
                l[g[i][j]] = i, j
        return l

    # Get starting and ending positions of all elements
    la = locs(a)
    lb = locs(b)
    found = [[False] * n for _ in range(n)]
    
    # Calculate shifts needed for each element
    for i in range(n**2):
        ai, aj = la[i]
        bi, bj = lb[i]
        if ai != bi and aj != bj:
            # If element moves both row and column
            di = (ai - bi) % n
            dj = (aj - bj) % n
            assert di and dj
            if found[di][dj]:
                return 0  # Multiple elements requiring same shift - invalid
            found[di][dj] = True
        if ai == bi:
            # Row stays same, column shifted
            deltai[ai] = (bj - aj) % n
        if aj == bj:
            # Column stays same, row shifted
            deltaj[aj] = (bi - ai) % n
    
    # Prepare adjacency lists for topological ordering
    iseq = [[] for _ in range(n)]
    jseq = [[] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if deltai[i] > 0 and deltaj[j] > 0:
                # Check if the move is consistent
                if a[i][j - deltai[i]] != b[(i + deltaj[j]) % n][j]:
                    jseq[j].append(i)
                if a[i - deltaj[j]][j] != b[i][(j + deltai[i]) % n]:
                    iseq[i].append(j)
    
    # Calculate in-degrees for topological sort
    jdeg = [0] * n
    for i in range(n):
        if deltai[i] > 0:
            for j in iseq[i]:
                if deltaj[j] > 0:
                    jdeg[j] += 1
    
    ideg = [0] * n
    for j in range(n):
        if deltaj[j] > 0:
            for i in jseq[j]:
                if deltai[i] > 0:
                    ideg[i] += 1
    
    # Initialize queue for topological sort - process rows with no in-degrees
    ique = [i for i in range(n) if ideg[i] == 0 and deltai[i] > 0]
    jque = [j for j in range(n) if jdeg[j] == 0 and deltaj[j] > 0]
    
    ans = 1
    seq = []
    
    # Process shifts in topological order
    while ique or jque:
        # Multiply by number of arrangements for current batch of column shifts
        ans = ans * fac(len(ique)) % mod
        for i in ique:
            seq.append(("i", i, deltai[i]))
            for j in iseq[i]:
                jdeg[j] -= 1
                if jdeg[j] == 0:
                    jque.append(j)
        ique = []
        # Multiply by number of arrangements for current batch of row shifts
        ans = ans * fac(len(jque)) % mod
        for j in jque:
            seq.append(("j", j, deltaj[j]))
            for i in jseq[j]:
                ideg[i] -= 1
                if ideg[i] == 0:
                    ique.append(i)
        jque = []
    
    # Simulate the sequence to check validity
    moved = [0] * n**2
    c = [[*row] for row in a]
    for typ, x, d in seq:
        assert 0 < d < n
        if typ == "i":
            # Shift row i
            i = x
            vals = [c[i][j] for j in range(n)]
            vals = vals[-d:] + vals[:-d]
            for j in range(n):
                c[i][j] = vals[j]
        if typ == "j":
            # Shift column j
            j = x
            vals = [c[i][j] for i in range(n)]
            vals = vals[-d:] + vals[:-d]
            for i in range(n):
                c[i][j] = vals[i]
        for v in vals:
            moved[v] += 1
        del typ, x, d, vals
    
    # Check constraints
    if any(v > 2 for v in moved):
        return 0
    if c != b:
        return 0
    return ans


def main():
    def get_grid(n):
        return [[*map(int, input().split())] for _ in range(n)]

    for _ in range(int(input())):
        n = int(input())
        print(solve(n, get_grid(n), get_grid(n)) % mod)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/