# Problem: CF 2124 I - Lexicographic Partition
# https://codeforces.com/contest/2124/problem/I

"""
Algorithm: Lexicographic Partition

Purpose:
This code solves a problem where given an array x of length n, we must determine if there exists a permutation a of integers 1 to n such that for each prefix of a, f(a[1..i]) = x[i]. Here, f(a) is defined as the number k such that among all possible partitions of a into k subarrays, the lexicographically largest resulting array b is produced.

This approach uses backtracking and stack-based simulation to reconstruct the permutation from the input array x, using inverse index tracking to assign values efficiently.

Approach:
1. For each element in x, we track positions where it appears.
2. Using a stack (deque), simulate partitioning and greedy assignment of values to produce the lexicographically optimal sequence.
3. At every step, determine whether elements can be placed optimally based on available indices and previous assignments.
4. Return a valid permutation if possible, else return "NO".

Time Complexity:
O(n) - Amortized over all test cases due to efficient indexing and stack operations.

Space Complexity:
O(n) - For storing inversion array and deque storage.
"""

from collections import deque


def solve(b, inv):
    n = len(b)
    if len(inv[1]) > 1:  # If 1 appears more than once, impossible to create valid sequence
        return []
    a = [0] * n
    s = deque()
    if len(inv[2]) > 1:
        # If 2 has multiple occurrences, assign smallest value to beginning
        a[0] = 1
        s.append((0, n - 1, 2, n, 1))
    else:
        # Otherwise begin with largest number
        a[0] = n
        s.append((0, n - 1, 1, n - 1, 1))
    while s:
        l, r, leftNum, rightNum, ok = s.pop()
        if l == r:
            continue
        if b[l + 1] != b[l] + 1:  # Check if increment follows expected order
            return []
        num = b[l] + 1  # Next value we want to process
        if num >= len(inv):  # Out of bounds
            return []
        nxt = []
        # Collect all indices for 'num' greater than current index l
        while inv[num] and inv[num][-1] > l:
            nxt.append(inv[num].pop())
        if not nxt:  # No suitable candidate
            return []
        if not ok and len(nxt) != 1:  # Inconsistent assignment rules
            return []
        if len(nxt) == 1:
            # Assign single element greedily to either left or right side
            if num + 1 < len(inv) and len(inv[num + 1]) > 1 and inv[num + 1][-2] > l:
                a[nxt[0]] = leftNum
                leftNum += 1
            else:
                a[nxt[0]] = rightNum
                rightNum -= 1
            s.append((l + 1, r, leftNum, rightNum, 1))
        else:
            # Multiple candidates; assign them greedily from right to left
            rightNum -= len(nxt)
            nx = rightNum + 1
            nxt.reverse()
            curLeft = leftNum
            for i in range(len(nxt)):
                pos = nxt[i]
                a[pos] = nx
                nx += 1
                nextInd = nxt[i + 1] - 1 if i + 1 < len(nxt) else r
                sz = nextInd - pos - 1
                s.append((pos, nextInd, curLeft, curLeft + sz, 0))
                curLeft += sz + 1
    return a


def main():
    import sys

    input = sys.stdin.read
    data = input().splitlines()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        x = list(map(int, data[index + 1].split()))
        index += 2
        inv = [[] for _ in range(n + 3)]  # Inverse mapping of element to indices
        for i in range(n):
            inv[x[i]].append(i)
        a = solve(x, inv)
        if not a:
            results.append("NO")
        else:
            results.append("YES")
            results.append(" ".join(map(str, a)))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/