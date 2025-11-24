# Problem: CF 1886 A - Sum of Three
# https://codeforces.com/contest/1886/problem/A

"""
Problem: Sum of Three

Purpose:
This code determines whether a given integer n can be represented as the sum of three distinct positive integers, none of which are divisible by 3. If such a triplet exists, it outputs one valid combination; otherwise, it reports "NO".

Algorithms/Techniques:
- Mathematical analysis to determine validity of triplet
- Greedy approach: use fixed small numbers (1, 2, 4) and compute the third number
- Modular arithmetic to check divisibility by 3

Time Complexity:
O(t), where t is the number of test cases. Each test case is processed in constant time.

Space Complexity:
O(1), only a constant amount of extra space is used regardless of input size.
"""

from sys import stdin, stdout


def input():
    return stdin.readline().strip()


def print(string):
    return stdout.write(str(string) + "\n")


def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        if n < 7:  # Minimum sum of three distinct positive integers is 1+2+3=6
            print("NO")
        else:
            if n % 3 == 0:  # If n is divisible by 3, we need to avoid using multiples of 3
                # Try using 1, 4 and n-5 as the triplet
                # Check if all three numbers are distinct and none is divisible by 3
                if len(set([1, 4, n - 5])) == 3 and (n - 5) % 3 != 0 and n - 5 > 0:
                    print("YES")
                    print(f"1 4 {n -5 }")
                else:
                    print("NO")
            else:  # If n is not divisible by 3, we can use 1, 2 and n-3
                print("YES")
                print(f"1 2 {n -3 }")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/