# Problem: CF 1870 D - Prefix Purchase
# https://codeforces.com/contest/1870/problem/D

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    out_lines = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        c = list(map(int, data[index : index + n]))
        index += n
        k = int(data[index])
        index += 1
        # Precompute suffix minimums of c array
        m_suf = [0] * n
        m_suf[-1] = c[-1]
        for i in range(n - 2, -1, -1):
            m_suf[i] = min(c[i], m_suf[i + 1])
        # If even the minimum cost to buy everything exceeds k, all elements are 0
        if k < m_suf[0]:
            a = [0] * n
            out_lines.append(" ".join(map(str, a)))
        else:
            # Calculate the maximum number of times we can buy the first option
            T_max = k // m_suf[0]
            a = [0] * n
            a[0] = T_max
            t_curr = T_max
            coins = k
            # Iterate through each position updating the array
            for i in range(n - 1):
                m_next = m_suf[i + 1]
                # Calculate how many times we can buy current option
                if m_next < c[i]:
                    x_i = 0
                elif m_next == c[i]:
                    x_i = 0
                else:
                    # Compute how many times to buy with current cost such that 
                    # we maintain the optimal number of operations to reach next element
                    num = t_curr * m_next - coins
                    if num <= 0:
                        x_i = 0
                    else:
                        den = m_next - c[i]
                        x_i = (num + den - 1) // den
                        if x_i > t_curr:
                            x_i = t_curr
                # Deduct coins and update counts
                coins -= x_i * c[i]
                t_curr -= x_i
                a[i + 1] = a[i] - x_i
            out_lines.append(" ".join(map(str, a)))
    for line in out_lines:
        print(line)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/