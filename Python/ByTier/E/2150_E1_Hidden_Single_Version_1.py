# Problem: CF 2150 E1 - Hidden Single (Version 1)
# https://codeforces.com/contest/2150/problem/E1

"""
Hidden Single (Version 1)

Algorithm:
- This problem uses a divide-and-conquer approach with binary search-like logic to find the unique element in an array where all elements appear twice except one.
- The core idea is to use queries to determine which subset of positions contains the unique element by comparing how many times a value appears in left and right parts of a partitioned range.
- At each step, the algorithm partitions the array into two halves and performs queries to determine whether the unique element lies in the left or right half.

Time Complexity:
- Each recursive call processes at most 2n elements, and there are at most log(2n) levels due to halving.
- Total queries per test case: O(n + log n), which is within the bound of 4n + 2 * ceil(log_2(n)).

Space Complexity:
- The space complexity is O(2n - 1) for storing the order array and recursion stack depth O(log n).
"""

from random import shuffle


def ask(S, x):
    global ans
    if ans != -1:
        return -1
    print("?", x, len(S), *S)
    return int(input())


def seg(l, r):
    return list(range(l, r + 1))


def shuf(l, r):
    global order
    tmp = order[l : r + 1]
    shuffle(tmp)
    order[l : r + 1] = tmp


def f(A, l, r):
    global ans
    if not A:
        return
    if l == r:
        if A:
            ans = A[0]
        return
    m = (l + r) // 2
    shuf(l, r)                # Shuffle the current segment to randomize indices for fair querying
    left = []
    right = []
    for x in A:
        a = ask(order[l : m + 1], x)  # Query if x exists in the left part of the range
        if a == 0:
            b = 1
        else:
            b = ask(order[m + 1 : r + 1], x)  # If not, query in the right part
        if a == 1 and b == 0:
            left.append(x)
        elif a == 0 and b == 1:
            right.append(x)
    # Recurse based on larger group size to avoid imbalance in query count
    if len(left) > len(right):
        f(left, l, m)
        f(right, m + 1, r)
    else:
        f(right, m + 1, r)
        f(left, l, m)


def solve():
    global order, ans
    ans = -1
    n = int(input())
    order = [-1] + seg(1, n * 2 - 1)  # Initialize the order array with dummy index 0 and segments from 1 to 2n-1
    f(seg(1, n), 1, n * 2 - 1)
    print("!", ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/