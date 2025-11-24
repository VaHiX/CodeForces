# Problem: CF 1894 B - Two Out of Three
# https://codeforces.com/contest/1894/problem/B

"""
Algorithm/Techniques: Greedy approach with hash map to track number occurrences and assign values.

Time Complexity: O(n), where n is the length of the array a. Each element is processed once.
Space Complexity: O(n), for storing the mapping from numbers to their assigned values and the answer array.

This solution attempts to satisfy exactly two out of three conditions by:
1. Tracking how many times each number appears.
2. Assigning values 1, 2, 3 greedily to ensure at least two pairs of numbers satisfy the required conditions.
3. If fewer than two such pairs exist, no valid solution is possible.
"""

def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        a = list(map(int, input().split()))
        num_map = {}  # Maps each number to a list of assigned values (1, 2, or 3)
        ans = []  # Result array
        pairs = 0  # Count of pairs that can satisfy a condition

        for num in a:
            if num not in num_map:
                # First occurrence of the number, assign 1
                num_map[num] = [1]
                ans.append(1)
            else:
                # If a second occurrence is found, form a pair
                if len(num_map[num]) == 1:
                    pairs += 1  # Increment pair count
                    # Assign either 2 or 3 based on parity of pairs to ensure
                    # we satisfy exactly two conditions in total
                    if pairs % 2:
                        num_map[num].append(3)
                    else:
                        num_map[num].append(2)
                # Append the second value assigned to this number
                ans.append(num_map[num][1])

        # If there are less than two pairs, we cannot satisfy exactly two conditions
        if pairs < 2:
            print("-1")
        else:
            print(" ".join(str(x) for x in ans))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/