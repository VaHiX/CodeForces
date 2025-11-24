// Problem: CF 2011 C - Split the Expression
// https://codeforces.com/contest/2011/problem/C

/*
C. Split the Expression
Algorithm: Dynamic Programming with greedy approach on digit splitting
Time Complexity: O(n * log(max_value)) where n is the length of the string
Space Complexity: O(n) for storing the split numbers

The problem involves splitting a string of digits and '+' signs into valid expressions,
and maximizing the sum of results. For each numeric block, we can either:
1. Treat it as a single number
2. Split it into two parts (prefix and suffix) and sum those parts.
We explore all possibilities greedily for each block to maximize contribution.

Each block is processed by:
- Splitting it into two parts: prefix and suffix (at different positions).
- Calculating the sum of the "split" parts (e.g., 456 → 4 + 56 or 45 + 6).
- Choosing the maximum such sum.

The first and last blocks are always added directly to the result.
Intermediate blocks are evaluated for optimal split strategy.
 */
import java.util.*
fun main() {
    repeat(readln().toInt()) {
        val str = readln()
        var cur = 0L
        val n = str.length
        val v = mutableListOf<Long>()
        for (i in 0 until n) {
            if (str[i] == '+') {
                v.add(cur) // Add the accumulated number
                cur = 0
            } else {
                cur = cur * 10 + (str[i] - '0') // Accumulate digits
            }
        }
        v.add(cur) // Add the last number
        
        var ans = v[0] + v[v.size - 1] // Add first and last directly
        for (i in 1 until v.size - 1) { // Process intermediate blocks
            val cand1 = v[i] / 10 + v[i] % 10 // Split into tens and unit: e.g. 456 -> 45 + 6
            var kat = 1L
            while (kat * 10 <= v[i]) { // Find the highest digit place
                kat *= 10
            }
            val cand2 = v[i] / kat + v[i] % kat // Split into first and rest: e.g. 456 -> 4 + 56
            ans += maxOf(cand1, cand2) // Choose the better split for this block
        }
        println(ans)
    }
}


// https://github.com/VaHiX/codeForces/