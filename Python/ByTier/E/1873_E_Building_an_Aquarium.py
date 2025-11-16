# Problem: CF 1873 E - Building an Aquarium
# https://codeforces.com/contest/1873/problem/E

"""
Algorithm: Binary Search + Prefix Sum
Time Complexity: O(n * log(max_height))
Space Complexity: O(1)

This code finds the maximum height h such that the total water needed to fill 
the tank up to height h is at most x. It sorts the coral heights first, then 
uses a greedy approach to determine how much water is needed for each possible
height h, and stops when the required water exceeds x.

The key idea is:
1. Sort the heights.
2. For each height h, calculate how much water is needed to bring all columns 
   up to that height.
3. Use a greedy method to check the water consumption incrementally for each 
   height level.

"""

def main():
    t = int(input())
    r = [str(solution(i, t)) for i in range(t)]
    print("\n".join(r))


def solution(ti, tn):
    n, x = map(int, input().split())
    aa = list(map(int, input().split()))
    aa.sort()
    for i in range(1, n):
        d = aa[i] - aa[i - 1]  # Difference in height between adjacent columns
        s = d * i              # Water needed to raise previous i columns to current level
        x -= s                 # Reduce available water
        if x == 0:
            return aa[i]
        if x < 0:
            # Partial water usage if x becomes negative
            return aa[i - 1] + (x + s) // i
    if x == 0:
        return aa[n - 1]
    if x > 0:
        # All columns can be raised by some amount
        return aa[n - 1] + (x) // n


main()


# https://github.com/VaHiX/CodeForces/