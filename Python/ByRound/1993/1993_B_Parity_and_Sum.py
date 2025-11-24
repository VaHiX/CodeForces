# Problem: CF 1993 B - Parity and Sum
# https://codeforces.com/contest/1993/problem/B

"""
Algorithm: Greedy approach to minimize operations needed to make all elements of the array have the same parity.
Techniques: 
- Separate even and odd numbers.
- Sort even numbers.
- Greedily merge odd numbers with even numbers based on their values.

Time Complexity: O(n log n) due to sorting the even numbers, where n is the size of the array.
Space Complexity: O(n) for storing even and odd numbers separately.

Approach:
1. Split the input array into even and odd numbers.
2. If there are no even or no odd numbers, no operations are needed.
3. Otherwise, sort the even numbers.
4. Compare the maximum odd number with the smallest and largest even number to decide how many operations are needed:
   - If the max odd is greater than the largest even, we need to add all even numbers to the odd.
   - If the max odd is smaller than the smallest even, we need to add all even numbers + 1 (to handle the odd).
   - Otherwise, simulate adding numbers greedily from even to odd.
"""

class Solution:
    def __init__(self):
        pass

    def solve(self):
        t = int(input())
        res = []
        for _ in range(t):
            int(input())
            arr = list(map(int, input().split()))
            cnt = 0
            even, odd = [], []
            for a in arr:
                if a % 2 == 0:
                    even.append(a)
                else:
                    odd.append(a)
            if len(even) != 0 and len(odd) != 0:
                even = sorted(even)
                odd_max = max(odd)
                if odd_max > even[-1]:  # Max odd is greater than largest even
                    cnt = len(even)
                elif odd_max < even[0]:  # Max odd is smaller than smallest even
                    cnt = len(even) + 1
                else:
                    flag = True
                    for x in even:
                        if odd_max > x:
                            odd_max += x
                        else:
                            flag = False
                            break
                    cnt = len(even)
                    if not flag:
                        cnt += 1
            res.append(cnt)
        return res


if __name__ == "__main__":
    sol = Solution()
    res = sol.solve()
    for x in res:
        print(x)


# https://github.com/VaHiX/CodeForces/