# Problem: CF 1869 D2 - Candy Party (Hard Version)
# https://codeforces.com/contest/1869/problem/D2

"""
Algorithm: Distribute candies to make all people have equal amount, with constraints on giving/recv
Techniques: Bit manipulation, greedy approach, simulation of binary representation

Time Complexity: O(n * log(max_a)) where n is number of people and max_a is maximum candies
Space Complexity: O(1) as we use fixed size arrays (40 elements) for bit counting

This solution works by:
1. First checking if total candies can be evenly distributed
2. Calculating how many candies each person needs to give or receive
3. For each need value, decomposing it into powers of 2 to determine how many transfers are needed
4. Checking if the required transfers can be arranged without violating the constraints
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    s = sum(a)
    if s % n != 0:
        print("NO")
        return

    av = s // n
    need = []
    for aa in a:
        need.append(av - aa)

    give = [0] * 40
    receive = [0] * 40

    def check(a):
        # Check if a is a power of 2
        ans = 0
        while a > 1:
            if a & 1 == 1:
                return -1
            else:
                ans += 1
                a >>= 1
        return ans

    def cal(a):
        # Calculate the binary decomposition of a
        y = 0
        while a:
            if a % 2 != 0:
                x = check(a + 1)
                if x == -1:
                    return -1, -1
                else:
                    return x + y, y
            else:
                y += 1
                a //= 2

    pos_give = [0] * 40
    pos_receive = [0] * 40

    for i, ne in enumerate(need):
        if ne > 0:
            x, y = cal(ne)
            if x == -1 and y == -1:
                print("NO")
                return
            give[y] += 1
            receive[x] += 1
            if check(ne) != -1:
                pos_receive[x] += 1

        elif ne < 0:
            x, y = cal(-ne)
            if x == -1 and y == -1:
                print("NO")
                return
            give[x] += 1
            receive[y] += 1
            if check(-ne) != -1:
                pos_give[x] += 1

    if receive == give:
        print("YES")
    elif receive != give:
        for i in range(39, -1, -1):
            if receive[i] > give[i]:
                nee = receive[i] - give[i]
                if pos_receive[i] < nee:
                    print("NO")
                    return
                else:
                    receive[i - 1] += nee
                    give[i - 1] -= nee
            elif receive[i] < give[i]:
                nee = give[i] - receive[i]
                if pos_give[i] < nee:
                    print("NO")
                    return
                else:
                    receive[i - 1] -= nee
                    give[i - 1] += nee
        print("YES")


tt = int(input())
for ww in range(tt):
    solve()


# https://github.com/VaHiX/CodeForces/