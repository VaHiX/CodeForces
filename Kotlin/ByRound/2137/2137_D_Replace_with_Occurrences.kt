// Problem: CF 2137 D - Replace with Occurrences
// https://codeforces.com/contest/2137/problem/D

/**
 * Problem: D. Replace with Occurrences
 *
 * Purpose:
 *   Given an array b of size n, determine if there exists an array a of size n such that 
 *   for each element a_i, the number of occurrences of a_i in array a equals b_i.
 *   If such an array exists, construct it.
 *
 * Algorithm:
 *   - Group indices by their b values (i.e., all indices where b[i] = x are grouped together).
 *   - For each group with value x, check if the number of indices is divisible by x. 
 *     If not, no valid assignment is possible.
 *   - Assign colors (distinct integers) to groups such that:
 *     * Each group of size x gets assigned x consecutive elements in the output array.
 *     * Elements within a group have same value in output array.
 *
 * Time Complexity: O(n), where n is the length of input array b.
 * Space Complexity: O(n), for storing the map and result array.
 */
import java.io.BufferedInputStream
import java.lang.StringBuilder
import java.util.StringTokenizer

private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun read(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    fun nextInt(): Int {
        var c: Int
        do {
            c = read()
        } while (c <= 32 && c >= 0)
        var sign = 1
        if (c == '-'.code) {
            sign = -1
            c = read()
        }
        var res = 0
        while (c > 32 && c >= 0) {
            res = res * 10 + (c - '0'.code)
            c = read()
        }
        return res * sign
    }
}

fun main() {
    val fs = FastScanner()
    val t = fs.nextInt() // Read number of test cases
    val out = StringBuilder()
    repeat(t) {
        val n = fs.nextInt() // Read size of array b
        val b = IntArray(n) { fs.nextInt() } // Read the array b
        val groups = HashMap<Int, MutableList<Int>>() // Map value -> list of indices where b[i] == value
        
        // Group indices by their corresponding b[i] value
        for (i in 0 until n) {
            groups.computeIfAbsent(b[i]) { mutableListOf() }.add(i)
        }
        
        val ans = IntArray(n) // Result array to be constructed
        var color = 1 // Color represents the value assigned to a group of indices
        var ok = true // Flag to check if a valid assignment is possible
        
        // Process each group
        for ((valB, idxList) in groups) {
            if (idxList.size % valB != 0) {
                // If group size is not divisible by value, impossible to assign
                ok = false
                break
            }
            var i = 0
            // Assign same value (color) to `valB` number of elements in sequence
            while (i < idxList.size) {
                for (j in 0 until valB) {
                    ans[idxList[i + j]] = color
                }
                color++
                i += valB
            }
        }
        
        // Output result or -1 if impossible
        if (!ok) {
            out.append("-1\n")
        } else {
            out.append(ans.joinToString(" ")).append('\n')
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/