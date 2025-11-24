# Problem: CF 1879 D - Sum of XOR Functions
# https://codeforces.com/contest/1879/problem/D

"""
Algorithm: Sum of XOR Functions
Technique: Bit Manipulation with Prefix Sums
Time Complexity: O(31 * n) = O(n)
Space Complexity: O(1) 

This solution calculates the sum of XOR values over all subarrays, weighted by their lengths.
It processes each bit position separately, using prefix sums to efficiently compute contributions
of subarrays where XOR is 0 or 1 at that bit position.
"""

import sys

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s) - 1])


def invr():
    return map(int, input().split())


def oupNum(n):
    sys.stdout.write(str(n) + "\n")


def oupList(lst):
    sys.stdout.write(" ".join(map(str, lst)) + "\n")


MOD = 998244353


def main():
    inp()
    nums = inlt()
    answer = 0
    # Iterate through each bit position (0 to 30)
    for i in range(31):
        currSum = 0
        currEvenOdd = 0
        # prefixL[0] and prefixL[1] store the sum of indices for even/odd XOR at current bit
        prefixL = [0, 0]
        # evenOddCnt[0] and evenOddCnt[1] store count of even/odd XOR prefixes
        evenOddCnt = [1, 0]
        for r in range(len(nums)):
            # Update currEvenOdd by XORing with the current bit
            currEvenOdd ^= (nums[r] >> i) & 1
            # Calculate contribution of subarrays ending at r with XOR=0 at bit i
            # by using prefix sums
            currSum += evenOddCnt[currEvenOdd ^ 1] * (r + 1) - prefixL[currEvenOdd ^ 1]
            # Update counts and prefix sums
            evenOddCnt[currEvenOdd] += 1
            prefixL[currEvenOdd] += r + 1
        # Add contribution of this bit to final answer
        answer += (1 << i) * currSum

    oupNum(answer % MOD)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/