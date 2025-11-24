# Problem: CF 1774 D - Same Count One
# https://codeforces.com/contest/1774/problem/D

"""
Algorithm: Greedy swap to balance 1s across arrays
Approach:
    1. Compute total number of 1s and check if it's divisible by n (possible to balance).
    2. For each column, identify which rows need to give 1s (have more than goal) and which need 1s (have less than goal).
    3. Greedily swap 1s from surplus rows to deficit rows in same column.
    
Time Complexity: O(n * m) - Each element in the arrays is processed a constant number of times.
Space Complexity: O(n * m) - Store input arrays and auxiliary structures (count array, zero/one lists per column).
"""

from sys import stdin, stdout

input = stdin.buffer.readline
write = stdout.write


def main():
    tt = int(input().strip())
    for _ in range(tt, 0, -1):
        n, m = map(int, input().strip().split())
        arr = [[int(c) for c in input().strip().split()] for _ in range(n)]
        cnt = [sum(row) for row in arr]
        tot = sum(cnt)
        if tot % n:
            write("-1\n")
            continue

        goal = tot // n
        ans = sum(c - goal for c in cnt if c > goal)
        write(str(ans) + "\n")
        for j in range(m):
            zero, one = [], []
            for i in range(n):
                if cnt[i] < goal and not arr[i][j]:
                    zero.append(i)
                if cnt[i] > goal and arr[i][j]:
                    one.append(i)
            for i1, i2 in zip(zero, one):
                cnt[i1] += 1
                cnt[i2] -= 1
                write(f"{i1 +1 } {i2 +1 } {j +1 }\n")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/