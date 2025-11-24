# Problem: CF 2048 I1 - Kevin and Puzzle (Easy Version)
# https://codeforces.com/contest/2048/problem/I1

"""
Algorithm: Construct a valid array 'a' such that for each position i in string s:
- If s[i] == 'L', then c(1, i-1) == a[i] (number of distinct elements from index 1 to i-1)
- If s[i] == 'R', then c(i+1, n) == a[i] (number of distinct elements from index i+1 to n)

Approach:
1. Handle special cases where the string has only Ls or only Rs at the ends.
2. For general case, we use a greedy algorithm to assign values to positions:
   - We maintain sets of seen values and counts of unassigned positions.
   - For each L, we assign it based on the distinct count from earlier.
   - For each R, we assign it based on the distinct count from later.
3. Final validation is done to check if assignment is consistent.

Time Complexity: O(n)
Space Complexity: O(n)

"""

def construct(s):
    n = len(s)
    l, r = [], []

    # Separate indices of Ls and Rs
    for i in range(n):
        if s[i] == "L":
            l.append(i)
        else:
            r.append(i)

    # Reverse the list of Rs to process right to left
    r.reverse()
    i, j = 0, 0

    # Initialize result array
    a = [-1] * n
    sl, sr = set(), set()  # Sets for distinct elements seen from left and right
    unkl, unkr = 0, 0      # Count of unassigned elements from left and right
    curl, curr = 0, n - 1  # Cursors for traversal

    # Assign values based on L/R order
    while i < len(l) and j < len(r):
        # Update sets for L side
        while curl < l[i]:
            if a[curl] == -1:
                unkl += 1
            else:
                sl.add(a[curl])
            curl += 1

        # Update sets for R side
        while curr > r[j]:
            if a[curr] == -1:
                unkr += 1
            else:
                sr.add(a[curr])
            curr -= 1

        # Greedily assign value based on which side seems better
        if len(sl) + unkl < len(sr) + unkr:
            a[l[i]] = len(sl) + unkl
            if l[i] > r[j]:
                unkr -= 1
                sr.add(a[l[i]])
            i += 1
        else:
            a[r[j]] = len(sr) + unkr
            if r[j] < l[i]:
                unkl -= 1
                sl.add(a[r[j]])
            j += 1

    # Assign remaining Ls
    while i < len(l):
        while curl < l[i]:
            if a[curl] == -1:
                unkl += 1
            else:
                sl.add(a[curl])
            curl += 1
        a[l[i]] = len(sl) + unkl
        i += 1

    # Assign remaining Rs
    while j < len(r):
        while curr > r[j]:
            if a[curr] == -1:
                unkr += 1
            else:
                sr.add(a[curr])
            curr -= 1
        a[r[j]] = len(sr) + unkr
        j += 1

    # Validation step: verify assigned array satisfies constraints
    seen = set()
    for i in range(n):
        if s[i] == "L" and a[i] != len(seen):
            return []
        seen.add(a[i])

    seen = set()
    for i in range(n - 1, -1, -1):
        if s[i] == "R" and a[i] != len(seen):
            return []
        seen.add(a[i])

    return a


def solve():
    n = int(input())
    s = input()

    # Find number of leading Ls and trailing Rs
    l, r = 0, n
    while l < n and s[l] == "L":
        l += 1
    while r > 0 and s[r - 1] == "R":
        r -= 1

    # Special case handling
    if l != r and l == n - r:
        a = [0] * n
        for i in range(n):
            if i < l:
                a[i] = i
            elif i >= r:
                a[i] = n - 1 - i
            else:
                a[i] = l + 1

        print(" ".join(map(str, a)))
    else:
        a = construct(s)
        if not a:
            print(-1)
        else:
            print(" ".join(map(str, a)))


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/