# Problem: CF 1901 E - Compressed Tree
# https://codeforces.com/contest/1901/problem/E

"""
Algorithm: Tree Dynamic Programming with DFS
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves finding the maximum sum of node values in a tree after 
performing operations to remove leaf nodes and then compressing the tree by 
removing nodes with exactly 2 neighbors. 

Key insights:
1. We use DFS to traverse the tree and compute maximum sums at each node
2. For each node, we track the top 3 maximum values from its children
3. We consider different cases for how we can include children in our final sum:
   - Include one child (max of children)
   - Include two children (max two children)
   - Include three children (max three children)
4. The compression happens automatically by the tree structure, so we don't need 
   to simulate it explicitly.

The solution uses a modified DFS with bit manipulation to handle post-order traversal.
"""

import random
import sys
from math import inf


class FastIO:
    def __init__(self):
        self.random_seed = random.randint(0, 10**9 + 7)
        return

    @staticmethod
    def read_int():
        return int(sys.stdin.readline().strip())

    @staticmethod
    def read_float():
        return float(sys.stdin.readline().strip())

    @staticmethod
    def read_list_ints():
        return list(map(int, sys.stdin.readline().strip().split()))

    @staticmethod
    def read_list_floats():
        return list(map(float, sys.stdin.readline().strip().split()))

    @staticmethod
    def read_list_ints_minus_one():
        return list(map(lambda x: int(x) - 1, sys.stdin.readline().strip().split()))

    @staticmethod
    def read_str():
        return sys.stdin.readline().strip()

    @staticmethod
    def read_list_strs():
        return sys.stdin.readline().strip().split()

    @staticmethod
    def read_list_str():
        return list(sys.stdin.readline().strip())

    @staticmethod
    def st(x):
        return print(x)

    @staticmethod
    def lst(x):
        return print(*x)

    @staticmethod
    def round_5(f):
        res = int(f)
        if f - res >= 0.5:
            res += 1
        return res

    @staticmethod
    def max(a, b):
        return a if a > b else b

    @staticmethod
    def min(a, b):
        return a if a < b else b

    @staticmethod
    def ceil(a, b):
        return a // b + int(a % b != 0)

    def read_graph(self, n, directed=False):
        dct = [[] for _ in range(n)]
        for _ in range(n - 1):
            i, j = self.read_list_ints_minus_one()
            dct[i].append(j)
            if not directed:
                dct[j].append(i)
        return dct


class Solution:
    def __init__(self):
        return

    @staticmethod
    def main(ac=FastIO()):
        for _ in range(ac.read_int()):
            n = ac.read_int()
            nums = ac.read_list_ints()
            dct = ac.read_graph(n)
            ans = max(0, max(nums))  # Initialize with max of nums or 0 (edge case)
            sub = nums[:]  # Copy the node values for DP
            stack = [(0, -1)]  # Stack for DFS traversal, (node, parent)

            while stack:
                i, fa = stack.pop()
                if i >= 0:
                    # Pre-order processing (push children to stack)
                    stack.append((~i, fa))  # Mark as visited, push with negation for post-order
                    for j in dct[i]:
                        if j != fa:
                            stack.append((j, i))  # Add children to stack
                else:
                    # Post-order processing (compute DP value)
                    i = ~i  # Restore index
                    x = y = z = -inf  # Top 3 maximum values from children
                    pos = 0  # Sum of positive values from children
                    
                    for j in dct[i]:
                        if j != fa:
                            cur = sub[j]
                            # Update top 3 values
                            if cur >= x:
                                x, y, z = cur, x, y
                            elif cur >= y:
                                y, z = cur, y
                            elif cur >= z:
                                z = cur
                            # Add positive values to pos
                            if cur >= 0:
                                pos += cur

                    # Compute sub[i] based on max values from children
                    sub[i] = max(sub[i], x)
                    ans = max(ans, x + nums[i])  # Include one child

                    sub[i] = max(sub[i], x + y + nums[i])
                    ans = max(ans, x + y)  # Include two children

                    if z >= 0:
                        sub[i] = max(sub[i], pos + nums[i])
                        ans = max(ans, pos + nums[i])  # Include many positive children
                    else:
                        sub[i] = max(sub[i], x + y + z + nums[i])
                        ans = max(ans, x + y + z + nums[i])  # Include all 3 children
                        
            ac.st(ans)
        return


Solution().main()


# https://github.com/VaHiX/CodeForces/