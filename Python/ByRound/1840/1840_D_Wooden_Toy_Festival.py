# Problem: CF 1840 D - Wooden Toy Festival
# https://codeforces.com/contest/1840/problem/D

from sys import stdin, stdout


def input():
    """Faster input parsing"""
    return stdin.readline().strip()


def print(string):
    stdout.write(str(string) + "\n")


def print_array(array):
    """Prints an array of values, the way CodeForces requires"""
    stdout.write(" ".join(map(str, array)) + "\n")


def print_single_values(array):
    for v in array:
        print(v)


def solve(n, a):
    a.sort()
    left, right = 0, 1000000000

    while left < right:
        mid = (left + right) // 2

        carver_count = 1
        # The position of the first carver's pattern, shifted by mid to cover range
        carver_position = a[0] + mid

        for i in range(n):
            # Check if the current toy can be made by the current carver
            if abs(carver_position - a[i]) <= mid:
                continue
            else:
                # Assign a new carver with a new pattern centered around the current toy
                carver_count += 1
                carver_position = a[i] + mid

        # If we can make all toys with 3 or fewer carvers, try a smaller max time
        if carver_count <= 3:
            right = mid
        else:
            # Otherwise, we need a larger max time
            left = mid + 1

    return right


def test():
    pass


if __name__ == "__main__":
    for t in range(int(input())):
        n = int(input())
        a = [int(_) for _ in input().split(sep=" ")]
        print(solve(n, a))

### Complexity Analysis

# - **Time Complexity**: O(n log(10^9) * log n), where the log(10^9) factor comes from binary search over the answer and the log n factor from sorting the array and traversing it.
# - **Space Complexity**: O(1) excluding input storage, as we only use a few variables for computation and the array is sorted in place.

# https://github.com/VaHiX/CodeForces/