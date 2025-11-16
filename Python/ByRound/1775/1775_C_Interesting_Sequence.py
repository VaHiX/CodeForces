# Problem: CF 1775 C - Interesting Sequence
# https://codeforces.com/contest/1775/problem/C

"""
Algorithm: Bit Manipulation
Approach:
1. Check if x is a submask of n (i.e., (n & x) == x). If not, return -1.
2. Convert both n and x into 65-bit binary representations.
3. Traverse from highest bit to lowest:
   - If bit in n is 1 and bit in x is 0, we need to find a valid m such that 
     all bits from current position to 0 must be 0 in the AND operation.
   - If any bit in n is 0 and x is 1, then there's no solution.
4. Calculate minimal m using a greedy approach based on these conditions.

Time Complexity: O(log(max(n,x))) which is effectively O(60) due to fixed bit length
Space Complexity: O(1) - only using fixed size arrays of 65 elements
"""

from sys import stdin, stdout

input = stdin.readline
inp = lambda: map(int, input().split())


def print(*args, end="\n", sep=" ") -> None:
    stdout.write(sep.join(map(str, args)) + end)


def pow(num, p):
    if p == 0:
        return 1
    sq = pow(num, p // 2)
    sq = sq * sq
    if p & 1:
        sq *= num
    return sq


def solve():
    n, x = inp()
    bit1 = [0] * 65
    bit2 = [0] * 65
    c = 64
    ans = 0
    a = n
    # If x is not a submask of n, then no such m can be found
    if (n & x) != x:
        print(-1)
        return

    # Convert n and x into 65-bit binary representations
    while n > 0 or x > 0:
        bit1[c] = n & 1
        bit2[c] = x & 1
        x >>= 1
        n >>= 1
        c -= 1

    # Traverse from highest to lowest bit
    for i in range(64, -1, -1):
        if bit1[i] and not (bit2[i]):
            # Calculate how much to add to reach required bits
            ans2 = 0
            for j in range(64, i, -1):
                if bit1[j]:
                    if bit2[j]:
                        print(-1)
                        return
                else:
                    ans2 += 1 << (64 - j)
            for j in range(i, -1, -1):
                if bit1[j] == 0:
                    break
                elif bit1[j] == 1 and bit2[j] == 1:
                    print(-1)
                    return
            ans = ans2 + 1
    print(a + ans)


t = int(input())
while t > 0:
    solve()
    t -= 1


# https://github.com/VaHiX/CodeForces/