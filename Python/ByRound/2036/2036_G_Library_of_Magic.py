# Problem: CF 2036 G - Library of Magic
# https://codeforces.com/contest/2036/problem/G

# ## Problem Overview
# This is an interactive problem where we need to find three distinct numbers (a, b, c) that were stolen from a library containing n types of books, with each type appearing exactly twice except for the three stolen ones which appear only once. We can query the XOR of all book numbers in a range [l, r] to determine which books are present.

# ## Approach
# 1. Use binary search techniques to isolate the three missing numbers.
# 2. For each query, determine if the XOR reveals information about the distribution of numbers.
# 3. Utilize bit manipulation and divide-and-conquer strategies to minimize queries.
# 4. Handle special cases where the overall XOR is 0, which requires special treatment.

# ## Time Complexity
# - **Time**: O(log²(n)) for each test case, due to binary search over the range and bit manipulation operations.
# - **Space**: O(log(n)) for storing intermediate results and recursion stack.

# ## Code Implementation

import sys


def query(l: int, r: int) -> int:
    # Send XOR query for range [l, r] to the interactor
    print(f"xor {l } {r }")
    sys.stdout.flush()
    response = int(input())
    return response


def answer(a: int, b: int, c: int):
    # Report the found triplet (a, b, c) to the interactor
    print(f"ans {a } {b } {c }")
    sys.stdout.flush()


def solve2(left, right, big):
    # Binary search to isolate one missing number in range [left, right]
    l = left
    r = right

    res = []
    while l < r:
        mid = (l + r) // 2
        lv = query(l, mid)  # Query left half
        rv = big ^ lv       # XOR of right half (using property that a^b^c = 0 implies a^b = c)
        if lv != 0 and rv == 0:
            r = mid         # Left half is the answer
            big = lv
        elif lv == 0 and rv != 0:
            l = mid + 1     # Right half is the answer
            big = rv
        else:
            # Both halves have non-zero XOR; collect them
            res.append(lv)
            res.append(rv)
            break
    return res


def solve3(n, big):
    # Binary search in full range to isolate three missing numbers
    l = 1
    r = n

    res = []
    while l < r:
        mid = (l + r) // 2
        lv = query(l, mid)  # Query left half
        rv = big ^ lv       # XOR of right half
        if lv != 0 and rv == 0:
            r = mid
            big = lv
        elif lv == 0 and rv != 0:
            l = mid + 1
            big = rv
        else:
            # If both parts contribute to solution, process recursively
            if lv > n:
                # If lv is outside range, then it's a direct answer
                res.append(rv)
                res = res + solve2(l, mid, lv)
                break
            else:
                # Handle cases where we need more precise determination
                v1 = query(lv, lv)  # Query single value
                if v1 == lv:
                    # lv is the answer
                    res.append(lv)
                    res = res + solve2(mid + 1, r, rv)
                    break
                else:
                    # rv is the answer
                    res.append(rv)
                    res = res + solve2(l, mid, lv)
                    break
    return res


def solve_case(n: int):
    # Start with full range query
    v = query(1, n)

    res = []
    if v != 0:
        # If XOR result is non-zero, proceed with solve3
        res = solve3(n, v)
    else:
        # Special case when total XOR is 0
        # This indicates some numbers are missing in pairs
        for cut in range(1, 61):
            # Binary split and check at different bit levels
            small = query(1, 2**cut - 1)

            large = v ^ small  # This is the result of the other half
            if small != 0 and large != 0:
                # Found non-zero results - add those to answer
                res.append(small)
                res = res + solve2(2**cut, n, large)
                break

    # Output the three numbers in the required format
    answer(res[0], res[1], res[2])


t = int(input())
for _ in range(t):
    n = int(input())
    solve_case(n)


# https://github.com/VaHiX/CodeForces/