// Problem: CF 2114 G - Build an Array
// https://codeforces.com/contest/2114/problem/G

/*
 * Problem: G. Build an Array
 * Purpose: Determine if a sequence of k operations can produce the given array from an empty array.
 *          Each operation adds an integer to either end of the array; adjacent identical elements merge into their sum.
 * 
 * Algorithm:
 * - For each element in the input array, calculate its "base" value (the odd part) and power of 2 (how many times it was halved).
 * - Use a sliding window technique to simulate possible merging sequences.
 * - Maintain bounds on how many operations are needed to construct the array based on cumulative sum computations.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array
 * Space Complexity: O(n), for storing intermediate arrays and computations
 */

private tailrec fun calc(d: Int, c: Int = 0): Pair<Int, Int> = if (d % 2 == 0) calc(d / 2, c + 1) else d to c

fun main() = java.util.Scanner(System.`in`).run {
    repeat(nextInt()) {
        val (n, k) = nextInt() to nextLong()
        List(n) { calc(nextInt()) }.unzip().let { (d, e) ->
            var p = d[0]
            // Initial computation of minimal operations for first element
            val init = (1 until n).fold(1L shl e[0]) { r, i -> 
                r + if (d[i] != p) { 
                    p = d[i]; 1L shl e[i] 
                } else if (e[i] > e[i - 1]) 
                    (1L shl e[i]) - (1L shl (e[i - 1] + 1)) + 1 
                else 
                    1L shl e[i] 
            }
            var res = init
            var q = d[0]
            // Compute maximum possible operations needed for valid sequence
            val final = (1 until n).fold(init) { a, i ->
                res = if (d[i] != q) { 
                    q = d[i]; 
                    (res - (1L shl e[i - 1]) + (1L shl e[i])) + (1L shl e[i - 1]) - (1L shl e[i]) 
                }
                else if (e[i] > e[i - 1]) 
                    (res - (1L shl e[i - 1]) + (1L shl e[i])) - ((1L shl e[i]) - (1L shl (e[i - 1] + 1)) + 1) + (1L shl e[i - 1])
                else 
                    (res - (1L shl e[i - 1]) + (1L shl e[i])) - (1L shl e[i]) + ((1L shl e[i - 1]) - (1L shl (e[i] + 1)) + 1)
                maxOf(a, res)
            }
            // Output YES if k is within valid range
            println(if (k in n..final) "YES" else "NO")
        }
    }
}


// https://github.com/VaHiX/CodeForces/