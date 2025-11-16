# Problem: CF 1772 D - Absolute Sorting
# https://codeforces.com/contest/1772/problem/D

"""
    Author   : @iinaamasum
    Mail     : iinaamasum@gmail.com
    GitHub   : https://github.com/iinaamasum
    LinkedIn : https://www.linkedin.com/in/iinaamasum/
"""

"""
    Problem: Absolute Sorting
    Algorithm: Binary search on the value of x to find a valid x such that applying 
               |a[i] - x| to all elements makes the array sorted.
    
    Key Idea:
        For each adjacent pair (a[i], a[i+1]), we want:
            |a[i] - x| <= |a[i+1] - x|
        This condition defines constraints on x.
        If a[i] < a[i+1], then x should be in range [0, (a[i]+a[i+1])/2] to satisfy the order.
        If a[i] > a[i+1], then x should be in range [(a[i]+a[i+1]+1)/2, INF] to satisfy the order.
        We take intersection of these ranges.

    Time Complexity: O(n) per test case
    Space Complexity: O(1)
"""

import sys

input = sys.stdin.readline
get_int = lambda: int(input())
get_ints = lambda: map(int, input().split())
get_list = lambda: list(map(int, input().split()))
get_str = lambda: input().rstrip("\n\r")
get_list_str = lambda: list(map(str, input().rstrip("\n\r").split(" ")))
output = lambda *args, end="\n": sys.stdout.write(
    " ".join([str(x) for x in args]) + end
)
yes = lambda: output("YES")
no = lambda: output("NO")


def solve():
    n = get_int()
    a = get_list()
    minn, maxx = 0, 10**9
    for i in range(n - 1):
        if a[i] < a[i + 1]:
            # If a[i] < a[i+1], x must be <= (a[i] + a[i+1]) // 2 to preserve order
            maxx = min(maxx, (a[i] + a[i + 1]) // 2)
        if a[i] > a[i + 1]:
            # If a[i] > a[i+1], x must be >= (a[i] + a[i+1] + 1) // 2 to preserve order
            minn = max(minn, (a[i] + a[i + 1] + 1) // 2)
    if minn > maxx:
        # No valid x exists
        output(-1)
    else:
        # Any value in [minn, maxx] works, output the smallest one
        output(minn)


def main():
    test_case = 1
    test_case = get_int()
    while test_case:
        solve()
        test_case -= 1
    return


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/