# Problem: CF 1974 B - Symmetric Encoding
# https://codeforces.com/contest/1974/problem/B

"""
Decode Symmetric Encoding

Algorithm:
- For each encoded string, first find all distinct characters and sort them alphabetically.
- Create a mapping from each character to its symmetric counterpart in the sorted list.
- Use this mapping to decode the string by replacing each character with its symmetric partner.

Time Complexity: O(n log n) per test case, dominated by sorting the distinct characters.
Space Complexity: O(n) for storing the distinct characters and the mapping.

Techniques:
- Set to get unique characters
- Sorting to arrange characters in alphabetical order
- Dictionary for efficient character mapping
"""

def decode_string(encoded):
    # Get all distinct characters and sort them alphabetically
    distinct_characters = sorted(set(encoded))
    char_to_symmetric = {}
    length = len(distinct_characters)

    # Map each character to its symmetric counterpart
    for i in range(length):
        # The symmetric character is at the mirrored index
        char_to_symmetric[distinct_characters[i]] = distinct_characters[length - 1 - i]

    # Decode the string by applying the mapping
    decoded = "".join(char_to_symmetric[char] for char in encoded)
    return decoded


def main():
    import sys

    input = sys.stdin.read
    data = input().split()

    t = int(data[0])
    index = 1
    results = []

    for _ in range(t):
        # Read the length of the encoded string (not used directly but needed for parsing)
        int(data[index])
        encoded = data[index + 1]
        index += 2

        decoded = decode_string(encoded)
        results.append(decoded)

    for result in results:
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/