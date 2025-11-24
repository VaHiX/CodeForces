# Problem: CF 1991 B - AND Reconstruction
# https://codeforces.com/contest/1991/problem/B

"""
AND Reconstruction

Algorithm:
- For a valid array 'a' such that b[i] = a[i] & a[i+1], we need to construct 'a'
- Start with a[0] = b[0] (this is a valid choice)
- For subsequent elements, we try to set a[j] = b[j-1] | b[j] (OR of two consecutive b values)
- Then verify that a[j] & a[j-1] == b[j-1] holds
- If this fails, then no valid array can be constructed
- Final element a[n-1] should equal b[n-2] to satisfy last constraint

Time Complexity: O(n) per test case, where n is the size of array a
Space Complexity: O(n) for storing the result array a
"""

def and_reconstruction(t, test_cases):
    results = []
    for i in range(t):
        n = test_cases[i][0]
        b = test_cases[i][1]

        a = [0] * n

        # Initialize first element of array a to first element of b
        a[0] = b[0]

        valid = True

        # Iterate through the middle elements to construct a
        for j in range(1, n - 1):
            # Try to set a[j] to OR of two consecutive elements in b
            a[j] = b[j - 1] | b[j]

            # Check if constructed a[j] satisfies the constraint with a[j-1]
            if (a[j] & a[j - 1]) != b[j - 1]:
                valid = False
                break

        # If constraints not satisfied, mark as invalid
        if not valid:
            results.append([-1])
        else:
            # Set last element to match last constraint
            a[-1] = b[-1]
            results.append(a)

    return results


import sys

input = sys.stdin.read


def main():
    data = input().split()
    index = 0
    t = int(data[index])
    index += 1
    test_cases = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        b = list(map(int, data[index : index + n - 1]))
        index += n - 1
        test_cases.append((n, b))

    results = and_reconstruction(t, test_cases)
    for result in results:
        if result == [-1]:
            print(-1)
        else:
            print(" ".join(map(str, result)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/