# Problem: CF 2127 G1 - Inter Active (Easy Version)
# https://codeforces.com/contest/2127/problem/G1

"""
Interactive problem: Find a hidden permutation p of length n.

Algorithm:
- Use binary search to determine each element of the permutation.
- For each position i in the permutation:
  - Perform binary search on candidates for that position.
  - Query the jury with permutations constructed based on mid-point of candidates.
  - Adjust binary search bounds based on jury response.

Time Complexity: O(n^2 * log n) in worst case due to nested loops and binary search per element.
Space Complexity: O(n) for storing permutation, candidates, and temporary variables.

This implementation uses an interactive framework with custom input/output handlers,
including a bootstrap function to simulate tail call optimization for recursive generators.
"""

import sys
from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


input = sys.stdin.readline
output = lambda x: sys.stdout.write(str(x) + "\n")
outputL = lambda x: sys.stdout.write(" ".join(map(str, x)) + "\n")
I = lambda: input().rstrip("\n")
II = lambda: int(input())
MII = lambda: map(int, input().split())
LMII = lambda: list(MII())
TMII = lambda: tuple(MII())
LI = lambda: list(I())
LSI = lambda: list(map(int, I()))


def query(a):
    for i in range(len(a)):
        a[i] += 1  # Adjust for 1-based indexing
    print("?", *a, flush=True)
    return II()


def answer(a):
    for i in range(len(a)):
        a[i] += 1  # Adjust for 1-based indexing
    print("!", *a, flush=True)


def solve():
    n = II()
    k = n // 4  # Select k as roughly n/4 for binary search strategy.
    print(n // 4 + 1, flush=True)  # Output k as specified by problem constraints
    ans = [0] * n
    for i in range(n):
        cand = list(range(n))
        cand.remove(i)  # Remove current position from consideration for assignment
        left, right = 0, len(cand) - 1
        while left < right:
            mid = (left + right) // 2
            diff = list()
            same = list() 
            b = [-1] * n
            b[k] = i  # Set fixed index k to value i for consistent testing
            
            # Partition indices into "diff" and "same" groups based on proximity to k
            for j in range(n):
                if j != k:
                    if k < j <= n - k - 1:
                        same.append(j)
                    else:
                        diff.append(j)

            # Adjust mid to ensure valid split of diff elements into first half
            while mid - left + 1 > len(diff):
                mid -= 1

            # Fill in the first part of the permutation b using differences.
            for j in range(left, mid + 1):
                b[diff[j - left]] = cand[j]
            
            # Fill in the second part using same indices
            for j in range(mid + 1, right + 1):
                b[same[j - mid - 1]] = cand[j]
            
            s = set(b)
            pos = list()
            for j in range(n):
                if b[j] == -1:
                    pos.append(j)

            # Assign remaining elements to unused positions
            for j in range(n):
                if j not in s:
                    b[pos.pop()] = j
                    
            assert max(b) == n - 1
            assert min(b) == 0
            
            # Query jury with constructed permutation
            p = query(b[:])
            
            # Rearrange the same groups again for second query to get count of pairs
            for j in range(len(diff) // 2):
                b[diff[j]], b[diff[-j - 1]] = b[diff[-j - 1]], b[diff[j]]
            for j in range(len(same) // 2):
                b[same[j]], b[same[-j - 1]] = b[same[-j - 1]], b[same[j]]
                
            p += query(b[:])  # Add result from second shuffled query
            
            # Narrow down search space based on returned count
            if p == n - 1:
                right = mid
            else:
                left = mid + 1
                
        ans[cand[left]] = i  # Assign final candidate to correct index in answer
        
    answer(ans)


TC = II()


def main():
    for _ in range(TC):
        solve()


main()


# https://github.com/VaHiX/codeForces/