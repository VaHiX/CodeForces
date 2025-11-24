# Problem: CF 1939 C - More Gifts
# https://codeforces.com/contest/1939/problem/C

"""
Algorithm: Optimized gift distribution using sliding window and cycle detection
Time Complexity: O(n * log(n) + n)
Space Complexity: O(n)

This solution uses the following techniques:
1. Preprocessing to reduce gift types to unique values with mapping
2. Sliding window technique to find maximum consecutive gifts a participant can receive
3. Cycle detection to handle large k values efficiently
4. Mathematical calculation to jump through cycles instead of simulating each step

The approach:
- First, compress gift types to unique values for efficient processing
- Use sliding window to determine the maximum number of consecutive gifts 
  a participant can receive without exceeding t different types
- For large k values, detect cycles in the distribution pattern and jump through them
- Apply cycle detection and mathematical optimization to avoid simulating all k stacks
"""

def test():
    from random import randint

    for _ in range(100):
        n = randint(1, 10)
        k, t = [randint(1, 100) for __ in range(2)]
        a = [randint(1, 20) for __ in range(n)]

        ans = solve(n, k, t, a)
        bf = bf_solve(n, k, t, a)
        if ans != bf:
            print(f"n={n } k={k } t={t } a={a } ans={ans } bf={bf }")
            return
    return


def bf_solve(n, k, t, a):
    box_number = 1
    participant = 1
    s = set()
    i = -1
    while True:
        if i == n - 1 and box_number == k:
            return participant
        elif box_number > k:
            return participant - 1
        i += 1
        if i == n:
            box_number += 1
            i = 0
        s.add(a[i])
        if len(s) > t:
            participant += 1
            s = {a[i]}
    assert False
    return


def solve(n, k, t, a):

    # Create a sorted list of unique gift types to map original types to compressed indices
    temp = sorted(a)
    temp2 = []
    for i in range(n):
        if i == n - 1 or temp[i] != temp[i + 1]:
            temp2.append(temp[i])
    m = len(temp2)
    if m <= t:
        return 1

    # Map original gift types to compressed indices for faster processing
    for i in range(n):
        lo, hi = -1, m - 1
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if temp2[mid] <= a[i]:
                lo = mid
            else:
                hi = mid - 1
        a[i] = lo

    # Sliding window to find maximum consecutive gifts each participant can handle
    right = [-1] * n
    counts = [0] * m
    unique_counts = 0
    r = -1

    def can_move_right(r):
        if counts[a[r % n]] == 0:
            return unique_counts + 1 <= t
        else:
            return True

    for i in range(n):
        while can_move_right(r + 1):
            r += 1
            r %= n
            if counts[a[r]] == 0:
                unique_counts += 1
            counts[a[r]] += 1

        right[i] = r

        counts[a[i]] -= 1
        if counts[a[i]] == 0:
            unique_counts -= 1

    # Initialize participant and box tracking for cycle detection
    pn = [-1] * n
    bn = [-1] * n
    participant = 1
    gift_index = 0
    box_number = 1
    while True:

        if box_number == k + 1:
            return participant - 1

        # If this gift index was seen before, detect cycle
        if pn[gift_index] == -1:
            pn[gift_index] = participant
            bn[gift_index] = box_number
        else:
            # Calculate cycle parameters
            cycle_participants = participant - pn[gift_index]
            cycle_boxes = box_number - bn[gift_index]

            # Jump through cycles instead of simulating each step
            x = ceil((k + 1 - box_number) / cycle_boxes) - 1
            participant += x * cycle_participants
            box_number += x * cycle_boxes

            # Reset tracking after cycle jump
            pn = [-1] * n
            bn = [-1] * n
            pn[gift_index] = participant
            bn[gift_index] = box_number

        # Move to next gift in sequence
        next_gift = (right[gift_index] + 1) % n
        if next_gift < gift_index:
            box_number += 1
        gift_index = next_gift
        participant += 1

    assert False
    return


def main():

    n, k, t = readIntArr()
    a = readIntArr()

    ans = solve(n, k, t, a)
    print(ans)

    return


import sys

input = sys.stdin.buffer.readline


def oneLineArrayPrint(arr):
    print(" ".join([str(x) for x in arr]))


def multiLineArrayPrint(arr):
    print("\n".join([str(x) for x in arr]))


def multiLineArrayOfArraysPrint(arr):
    print("\n".join([" ".join([str(x) for x in y]) for y in arr]))


def readIntArr():
    return [int(x) for x in input().split()]


def makeArr(defaultValFactory, dimensionArr):
    dv = defaultValFactory
    da = dimensionArr
    if len(da) == 1:
        return [dv() for _ in range(da[0])]
    else:
        return [makeArr(dv, da[1:]) for _ in range(da[0])]


def queryInteractive(a, b, c):
    print("? {} {} {}".format(a, b, c))
    sys.stdout.flush()
    return int(input())


def answerInteractive(x1, x2):
    print("! {} {}".format(x1, x2))
    sys.stdout.flush()


inf = float("inf")


from math import ceil

for _abc in range(1):
    main()


# https://github.com/VaHiX/CodeForces/