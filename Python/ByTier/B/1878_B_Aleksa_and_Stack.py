# Problem: CF 1878 B - Aleksa and Stack
# https://codeforces.com/contest/1878/problem/B

"""
Code purpose: This code constructs a strictly increasing array of positive integers of size n such that for every triplet of consecutive elements a_i, a_{i+1}, a_{i+2}, the value 3*a_{i+2} is not divisible by a_i + a_{i+1}. 

Algorithm:
- Start with initial array [2, 3].
- For each additional element:
  - Check if (v + last_element) is divisible by 3.
  - If yes, increment v by 1 to avoid divisibility.
  - Append v to the array and increment v.
- This ensures the condition 3*a_{i+2} % (a_i + a_{i+1}) != 0 is satisfied.

Time Complexity: O(n) - We iterate through n-2 elements and perform constant time operations.
Space Complexity: O(n) - We store the array of size n.

"""
def main():

    t = int(input())
    allans = []
    for _ in range(t):
        n = int(input())
        ans = [2, 3]
        v = 4
        for i in range(n - 2):
            if (v + ans[-1]) % 3 == 0:
                v += 1
            ans.append(v)
            v += 1
        allans.append(ans)
    multiLineArrayOfArraysPrint(allans)

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


def queryInteractive(a, b):
    print("? {} {}".format(a, b))
    sys.stdout.flush()
    return int(input())


def answerInteractive(ans):
    print("! {}".format(ans))
    sys.stdout.flush()


inf = float("inf")




for _abc in range(1):
    main()


# https://github.com/VaHiX/CodeForces/