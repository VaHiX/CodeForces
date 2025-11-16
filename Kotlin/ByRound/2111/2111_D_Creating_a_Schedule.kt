// Problem: CF 2111 D - Creating a Schedule
// https://codeforces.com/contest/2111/problem/D

/*
 * Problem: D. Creating a Schedule
 * Algorithm/Technique: Greedy approach with floor-based allocation
 *
 * Approach:
 * 1. For each group, assign 6 classrooms such that:
 *    - Each classroom appears exactly once per group (as per constraint)
 *    - The k-th class time is same across all groups
 *    - Maximize movements between floors
 * 2. Extract floor numbers from classroom indices by taking all digits except the last two.
 * 3. Sort classrooms by floor to facilitate optimal pairing of high-floor and low-floor rooms.
 * 4. Alternate assignments between groups using first and last elements in deque to maximize floor differences.
 *
 * Time Complexity: O(m log m) per test case due to sorting
 * Space Complexity: O(m) for storing classrooms and deque
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.StringTokenizer
data class Box(val width: Int, val length: Int, val height: Int)
fun main() {
    val writer = PrintWriter(System.out.bufferedWriter())
    val builder = StringBuilder()
    val br = BufferedReader(InputStreamReader(System.`in`))
    var tokenizer: StringTokenizer? = null
    fun nextString(): String {
        var t = tokenizer
        while (t == null || !t.hasMoreElements()) {
            t = StringTokenizer(br.readLine())
        }
        tokenizer = t
        return t.nextToken()
    }
    fun next(): Int {
        return nextString().toInt()
    }
    fun nextLong(): Long {
        return nextString().toLong()
    }
    repeat(next()) { // Process each test case
        val n = next() // Number of groups
        val m = next() // Number of classrooms
        val arr = IntArray(m) { next() } // Read classroom indices
        val deque = arr.sorted().toCollection(ArrayDeque()) // Sort and load into deque for efficient access
        var k = 0 // Holds first element in deque for current assignment
        var l = 0 // Holds last element in deque, or same as k if deque is empty
        repeat(n) { i -> // For each group
            if (i % 2 == 0) { // Even group index: assign pattern (k,l,k,l,k,l)
                k = deque.removeFirst() // Take the smallest available classroom (lowest floor)
                l = if (deque.isNotEmpty()) deque.removeLast() else k // If more classrooms, take largest; otherwise use same
                builder.append(k)
                builder.append(' ')
                builder.append(l)
                builder.append(' ')
                builder.append(k)
                builder.append(' ')
                builder.append(l)
                builder.append(' ')
                builder.append(k)
                builder.append(' ')
                builder.append(l)
                builder.appendLine()
            } else { // Odd group index: assign pattern (l,k,l,k,l,k)
                builder.append(l)
                builder.append(' ')
                builder.append(k)
                builder.append(' ')
                builder.append(l)
                builder.append(' ')
                builder.append(k)
                builder.append(' ')
                builder.append(l)
                builder.append(' ')
                builder.append(k)
                builder.appendLine()
            }
        }
    }
    writer.print(builder.toString())
    writer.flush()
}


// https://github.com/VaHiX/CodeForces/