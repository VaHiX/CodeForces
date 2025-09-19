# Contest 2116, Problem F: Gellyfish and Forget-Me-Not
# URL: https://codeforces.com/contest/2116/problem/F

import sys


def main():
    data = sys.stdin.read().splitlines()
    t = int(data[0].strip())
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index].strip())
        index += 1
        a_list = list(map(int, data[index].split()))
        index += 1
        b_list = list(map(int, data[index].split()))
        index += 1
        c_str = data[index].strip()
        index += 1

        total_a = 0
        for a_val in a_list:
            total_a ^= a_val

        d_list = [a_list[i] ^ b_list[i] for i in range(n)]
        basis_arr = [0] * 60
        ans = total_a

        for i in range(n - 1, -1, -1):
            temp = d_list[i]
            if temp == 0:
                continue

            for bit_index in range(59, -1, -1):
                if (temp >> bit_index) & 1:
                    if basis_arr[bit_index] != 0:
                        temp ^= basis_arr[bit_index]

            if temp != 0:
                high_bit_index = temp.bit_length() - 1
                basis_arr[high_bit_index] = temp
                high_bit_val = 1 << high_bit_index
                if c_str[i] == "0":
                    if ans & high_bit_val:
                        ans ^= temp
                else:
                    if not (ans & high_bit_val):
                        ans ^= temp
        results.append(str(ans))

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    main()
