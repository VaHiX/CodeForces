# Problem: CF 2168 A2 - Encode and Decode (Hard Version)
# https://codeforces.com/contest/2168/problem/A2

"""
Encode and Decode (Hard Version)

Purpose:
This program implements a run-twice communication strategy to encode and decode an array of integers.
During the first run (encoding), the array is converted into a string of lowercase letters.
During the second run (decoding), that string is reverse-engineered to recover the original array.

Algorithms:
1. Encoding:
   - The size 'n' is encoded using base-26 with 3 characters.
   - Each element of the array is encoded using base-26 with 7 characters.
   - All encoded parts are concatenated.

2. Decoding:
   - The first 3 characters represent 'n' in base-26.
   - Each subsequent 7-character chunk represents an array element in base-26.
   - These chunks are converted back to integers and assembled into the original array.

Time Complexity:
- Encoding: O(n * 7) = O(n), due to processing each array element.
- Decoding: O(n * 7) = O(n), similar processing for array elements.
- Overall time complexity per run is linear with respect to input size.

Space Complexity:
- Encoding: O(n * 7) = O(n), for storing the encoded string.
- Decoding: O(n * 7) = O(n), for storing decoded array elements.
- Total space complexity is linear with respect to input size.
"""

import sys


def encode_base26(num, length):
    # Convert a number into a base-26 string representation using lowercase letters
    result = []
    for i in range(length):
        result.append(chr(ord("a") + num % 26))  # Map remainder to a-z
        num //= 26  # Integer division to move to next digit
    return "".join(result[::-1])  # Reverse to get correct order


def decode_base26(s):
    # Convert a base-26 string back to integer
    result = 0
    for char in s:
        result = result * 26 + (ord(char) - ord("a"))  # Compute value in base-26
    return result


def first_run():
    # Read input for first run
    n = int(sys.stdin.readline())
    arr = list(map(int, sys.stdin.readline().split()))
    
    # Encode n using 3 characters
    n_encoded = encode_base26(n, 3)
    
    # Encode each array element using 7 characters
    arr_encoded = "".join(encode_base26(x, 7) for x in arr)
    
    # Concatenate and print result
    result = n_encoded + arr_encoded
    print(result)


def second_run():
    # Read input for second run
    s = sys.stdin.readline().strip()
    
    # Decode n from first 3 characters
    n_encoded = s[:3]
    n = decode_base26(n_encoded)
    
    # Decode array elements from subsequent 7-character chunks
    arr = []
    for i in range(n):
        start_idx = 3 + i * 7  # Start index for current element
        end_idx = start_idx + 7  # End index for current element
        num_encoded = s[start_idx:end_idx]
        arr.append(decode_base26(num_encoded))
    
    # Print decoded values
    print(n)
    print(" ".join(map(str, arr)))


def main():
    # Determine if this is first or second run based on first line
    first_line = sys.stdin.readline().strip()
    if first_line == "first":
        first_run()
    elif first_line == "second":
        second_run()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/