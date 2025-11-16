# Problem: CF 1999 G1 - Ruler (easy version)
# https://codeforces.com/contest/1999/problem/G1

"""
Algorithm: Binary Search on the missing number x
Time Complexity: O(log(999)) = O(1) since the search space is fixed and small
Space Complexity: O(1) - only using a few variables

The problem is to find a missing number x in the range [2, 999] using at most 10 queries.
Each query asks for the area of an a×b rectangle measured by the ruler.
If x is missing, then any dimension >= x will be measured as (dimension + 1).
Using binary search, we query rectangles of size (mid) × (mid + 1) to determine
whether x is in the left or right half.
"""

def main():
    import sys

    t = int(sys.stdin.readline())
    for _ in range(t):

        low = 1
        high = 999
        query_count = 0
        found = False
        while low < high and query_count < 10:
            # Binary search to find the missing number x
            mid = (low + high) // 2
            a = mid
            b = mid + 1
            print("? {} {}".format(a, b))
            sys.stdout.flush()
            response = int(sys.stdin.readline().strip())
            query_count += 1
            if response == -1:
                # Invalid query, terminate
                sys.exit()
            # Calculate expected areas based on different cases:
            # 1. If x <= mid, then a and b are both < x, so no adjustment
            expected1 = a * b
            # 2. If x = mid + 1, then a = mid < x and b = mid + 1 = x, so b becomes b+1
            expected2 = a * (b + 1)
            # 3. If x < mid, then both a and b are >= x, so both become +1
            expected3 = (a + 1) * (b + 1)
            if response == expected1:
                # x is in the range [mid+1, high], so move low to mid+1
                low = b + 1
            elif response == expected2:
                # x is exactly mid+1, because the second dimension got incremented
                low = b
                high = b
                found = True
                break
            elif response == expected3:
                # x is in the range [low, mid], so move high to mid
                high = a
            else:
                # Unexpected response
                print("Invalid response:", response)
                sys.exit()
        if not found:
            # If x is not identified in loop, it is low
            x = low
        else:
            x = low
        print("! {}".format(x))
        sys.stdout.flush()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/