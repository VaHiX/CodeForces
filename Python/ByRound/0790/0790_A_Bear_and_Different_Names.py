# Problem: CF 790 A - Bear and Different Names
# https://codeforces.com/contest/790/problem/A

import string


def list_to_string(_a):
    return " ".join(map(str, _a))


def solve():
    # Precompute possible names: single uppercase letters and two-letter combinations
    # starting with uppercase and followed by lowercase
    possible_names = list(string.ascii_uppercase)
    possible_names += list(
        map(
            lambda x: x[0] + x[1],
            zip(list(string.ascii_uppercase), list(string.ascii_lowercase)),
        )
    )
    n, k = map(int, input().split())
    a = list(input().split())
    result = possible_names[:n]  # Start with basic names
    # Iterate through each consecutive group of k soldiers
    for i in range(n - k + 1):
        if a[i] == "NO":  # If the group is not effective
            # Make the last soldier of the group same as the first soldier
            # This ensures that the group will have duplicate names (hence "NO")
            result[i + k - 1] = result[i]
    return list_to_string(result)


if __name__ == "__main__":
    print(solve())

### Complexity Analysis

# - **Time Complexity:** O(n * k), where n is the number of soldiers and k is the group size. We iterate through the groups and in worst case we may need to adjust the names of soldiers in each group.

# - **Space Complexity:** O(n), as we store the names of soldiers and precompute a list of possible names which has a fixed size dependent on the alphabet.

# https://github.com/VaHiX/CodeForces/