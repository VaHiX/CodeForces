# Problem: CF 1926 E - Vlad and an Odd Ordering
# https://codeforces.com/contest/1926/problem/E

import io
import os
import sys
import time

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
ii = lambda: int(input())
mi = lambda: map(int, input().split())
li = lambda: list(mi())
ls = lambda: list(map(str, input().split()))
MOD = 10**9 + 7


def MainProg(n, k):
    # Calculate number of odd numbers from 1 to n
    odd = (n + 1) // 2
    # If k is within the range of odd numbers, return the k-th odd number
    if k <= odd:
        return 2 * k - 1
    k -= odd  # Adjust k to account for odd numbers already processed
    
    num = 2  # Start with 2 (which is 2 * 1, i.e. 2 times an odd number)
    while k > 0:
        # Count how many numbers in range [1,n] that are multiples of 'num'
        # but not multiples of 'num * 2'
        m = n // num - n // (num * 2)
        # If k is within this group, return the appropriate number
        if k <= m:
            return num * (2 * k - 1)
        k -= m  # Reduce k by the count of numbers in this group
        num *= 2  # Move to next multiple (2*2, 2*4, etc.)
    return -1


def solve():
    n, k = map(int, input().split())
    print(MainProg(n, k))


def main():
    startTime = time.time()
    test_numbers = 1
    test_numbers = ii()
    for testcase in range(test_numbers):
        solve()
    print("Time: {} ms".format(int((time.time() - startTime) * 1000)), file=sys.stderr)


main()


# https://github.com/VaHiX/CodeForces/