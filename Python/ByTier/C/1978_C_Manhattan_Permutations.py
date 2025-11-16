# Problem: CF 1978 C - Manhattan Permutations
# https://codeforces.com/contest/1978/problem/C

"""
Manhattan Permutations Problem

Algorithm:
- For a permutation of n elements, the Manhattan value is the sum of absolute differences between each element and its index (1-based).
- The minimum Manhattan value is 0 (when the permutation is [1,2,3,...,n]).
- The maximum Manhattan value is n*(n-1) (when elements are as far as possible from their indices).
- The key insight is that we can use swaps to adjust the Manhattan value by even amounts (since each swap changes the Manhattan value by 2 * (difference in original positions)).
- If k is odd, it's impossible to achieve since each operation contributes an even value.
- We use a two-pointer approach to construct the permutation:
  1. Start with [1,2,3,...,n]
  2. Use two pointers from both ends, and if swapping elements at these positions reduces k by 2*(a-b), do the swap
  3. Continue until we either reduce k to 0 or determine it's impossible

Time Complexity: O(n) for each test case, as we process each element at most once.
Space Complexity: O(n) for storing the permutation.

Approach:
1. If k is odd, return "No" since only even adjustments are possible with swaps.
2. Initialize permutation as [1,2,3,...,n].
3. Use two pointers to iteratively reduce k by swapping elements.
4. If k becomes 0, return the permutation; otherwise return "No".
"""

def main():
    t = int(input())
    allans = []
    for _ in range(t):
        n, k = readIntArr()
        if k % 2 == 1:  # If k is odd, impossible to achieve with swaps (each swap contributes even difference)
            allans.append(["No"])
        else:
            ans = list(range(1, n + 1))  # Start with identity permutation
            l, r = 0, n - 1  # Two pointers
            while l < r:
                # Check if swapping elements at l and r can reduce k
                if k - 2 * (ans[r] - ans[l]) >= 0:
                    k -= 2 * (ans[r] - ans[l])  # Reduce k by the difference
                    ans[l], ans[r] = ans[r], ans[l]  # Swap elements
                    l += 1  # Move left pointer
                    r -= 1  # Move right pointer
                else:
                    r -= 1  # Reduce right pointer to try smaller differences
            if k == 0:  # Successfully reduced k to 0
                allans.append(["Yes"])
                allans.append(ans)
            else:
                allans.append(["No"])
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

def queryInteractive(a, b, c):
    print("? {} {} {}".format(a, b, c))
    sys.stdout.flush()
    return int(input())

def answerInteractive(x1, x2):
    print("! {} {}".format(x1, x2))
    sys.stdout.flush()

inf = float("inf")

for _abc in range(1):
    main()


# https://github.com/VaHiX/CodeForces/