# Problem: CF 2049 E - Broken Queries
# https://codeforces.com/contest/2049/problem/E

"""
Algorithm: Binary Search on k
Time Complexity: O(log n)
Space Complexity: O(1)

The problem involves finding a hidden value k in a binary array using a magical device that
reverses answers for ranges of size >= k. The approach is to use binary search on k by
making strategic queries and checking inconsistencies in answers.

The key insight is to use queries of size n//4 and n//2 to determine which half contains
the 1, then binary search on k within that half.
"""

import sys

for _ in range(int(sys.stdin.readline().rstrip("\r\n"))):
    n = int(sys.stdin.readline().rstrip("\r\n"))
    # Query first quarter to determine initial pattern
    print("?", 1, n // 4, flush=True)
    x = int(sys.stdin.readline().rstrip("\r\n"))
    # Query second quarter to compare with first
    print("?", n // 4 + 1, n // 2, flush=True)
    y = int(sys.stdin.readline().rstrip("\r\n"))
    if x == y:
        # If both quarters give same result, 1 is in third or fourth quarter
        print("?", n // 2 + 1, n, flush=True)
        x = int(sys.stdin.readline().rstrip("\r\n"))
        if x == 0:
            # 1 is in fourth quarter, binary search to find k
            lo = 2
            hi = n // 2
            while lo <= hi:
                mid = (lo + hi) // 2
                print("?", 1, mid, flush=True)
                x = int(sys.stdin.readline().rstrip("\r\n"))
                if x == 0:
                    lo = mid + 1
                else:
                    k = mid
                    hi = mid - 1
            print("!", k, flush=True)
        else:
            # 1 is in second half, binary search from end
            lo = n // 2 + 1
            hi = n - 1
            while lo <= hi:
                mid = (lo + hi) // 2
                print("?", n - mid + 1, n, flush=True)
                x = int(sys.stdin.readline().rstrip("\r\n"))
                if x == 1:
                    lo = mid + 1
                else:
                    k = mid
                    hi = mid - 1
            print("!", k, flush=True)
    else:
        # If quarters differ, 1 is in first or second quarter
        print("?", 1, n // 2, flush=True)
        x = int(sys.stdin.readline().rstrip("\r\n"))
        if x == 0:
            # 1 is in second quarter, search from end
            lo = 2
            hi = n // 2
            while lo <= hi:
                mid = (lo + hi) // 2
                print("?", n - mid + 1, n, flush=True)
                x = int(sys.stdin.readline().rstrip("\r\n"))
                if x == 0:
                    lo = mid + 1
                else:
                    k = mid
                    hi = mid - 1
            print("!", k, flush=True)
        else:
            # 1 is in first quarter, search from start
            lo = n // 2 + 1
            hi = n - 1
            while lo <= hi:
                mid = (lo + hi) // 2
                print("?", 1, mid, flush=True)
                x = int(sys.stdin.readline().rstrip("\r\n"))
                if x == 1:
                    lo = mid + 1
                else:
                    k = mid
                    hi = mid - 1
            print("!", k, flush=True)


# https://github.com/VaHiX/CodeForces/