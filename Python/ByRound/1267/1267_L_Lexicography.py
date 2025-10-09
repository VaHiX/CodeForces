# Contest 1267, Problem L: Lexicography
# URL: https://codeforces.com/contest/1267/problem/L

import sys

input = sys.stdin.buffer.readline


def process(n, l, k, S):
    d = [0 for i in range(26)]
    for c in S:
        d[ord(c) - ord("a")] += 1
    answer = [[None for j in range(l)] for i in range(n)]
    I = 0
    for i in range(k):
        while d[I] == 0:
            I += 1
        answer[i][0] = I
        d[I] -= 1
    j = 0
    while j + 1 <= l - 1:
        if k == 1 or (answer[k - 2][j] < answer[k - 1][j]):
            for j2 in range(j + 1, l):
                while d[I] == 0:
                    I += 1
                answer[k - 1][j2] = I
                d[I] -= 1
            break
        else:
            i1 = k - 1
            while i1 > 0 and answer[i1 - 1][j] == answer[k - 1][j]:
                i1 -= 1
            for j2 in range(i1, k):
                while d[I] == 0:
                    I += 1
                answer[j2][j + 1] = I
                d[I] -= 1
            j += 1
    for i in range(n):
        for j in range(l):
            if answer[i][j] is None:
                while d[I] == 0:
                    I += 1
                answer[i][j] = I
                d[I] -= 1
    for row in answer:
        row = [chr(x + ord("a")) for x in row]
        row = "".join(row)
        sys.stdout.write(f"{row}\n")


n, l, k = [int(x) for x in input().split()]
S = input().decode().strip()
process(n, l, k, S)
