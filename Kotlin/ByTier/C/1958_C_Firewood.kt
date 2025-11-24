// Problem: CF 1958 C - Firewood
// https://codeforces.com/contest/1958/problem/C

/*
C. Firewood
Algorithm: The problem involves splitting a log of weight 2^n grams into smaller logs such that some subset sums to exactly k grams.
We need to determine the minimum number of cuts to achieve this.

Key idea:
- We can represent k in binary.
- Each bit in the binary representation tells us how many times we need to split a log to get that weight.
- The number of operations needed is equal to the total number of bits in k minus the number of trailing zeros (i.e., the position of the last set bit).

Time Complexity: O(1) per test case
Space Complexity: O(1)

The solution uses bit manipulation:
- n - k.countTrailingZeroBits() calculates how many splits are needed to get logs of weights that sum to k.
*/
fun main() {
    repeat(readln().toInt()) {
        val (n, k) = readln().split(' ').map { it.toLong() }
        println(n - k.countTrailingZeroBits()) // Calculate minimum minutes required
    }
}


// https://github.com/VaHiX/codeForces/