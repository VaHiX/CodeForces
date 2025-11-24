// Problem: CF 2121 D - 1709
// https://codeforces.com/contest/2121/problem/D

/**
 * Problem: D. 1709 - Sorting arrays with cross-swaps
 * 
 * Approach:
 * This solution aims to sort two arrays 'a' and 'b' such that:
 * 1. Both arrays are sorted in ascending order (a[i] < a[i+1], b[i] < b[i+1])
 * 2. For each i, a[i] < b[i]
 * 
 * To achieve this:
 * - First, we ensure all elements of 'a' are less than corresponding elements in 'b'
 *   by swapping a[i] with b[i] when necessary
 * - Then perform bubble sort on array 'a' to make it sorted
 * - Then perform bubble sort on array 'b' to make it sorted
 * 
 * Time Complexity: O(n^2) - For nested loops in sorting operations
 * Space Complexity: O(1) - Only using constant extra space apart from input arrays
 */
import java.util.StringTokenizer
import java.io.PrintWriter
@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { _writer.apply(block).flush() }
fun main(){
var t: Int = readInt()
while(t-- > 0) solve()
}
fun solve(){
    var ans: StringBuilder = StringBuilder()
    var count: Int = 0
    var n: Int = readInt()
    var a = readLine()!!.split(" ").map{ it.toInt() }.toIntArray()
    var b = readLine()!!.split(" ").map{ it.toInt() }.toIntArray()
    // Ensure a[i] < b[i] for all i by swapping when needed
    for (i in 0..n-1) {
        if (a[i] > b[i]) {
            a[i] = a[i].xor(b[i])      // XOR swap to exchange values of a[i] and b[i]
            b[i] = a[i].xor(b[i])
            a[i] = a[i].xor(b[i])
            ans.append("3 ${i+1}\n")   // Operation 3: swap a[i] with b[i]
            count++
        }
    }
    // Sort array 'a' using bubble sort
    var noSwap: Boolean
    for (i in 1..n-1) {
        noSwap = true
        for(j in n-1 downTo i) {
            if (a[j] < a[j-1]) {
                a[j] = a[j].xor(a[j-1])    // XOR swap to exchange values of a[j] and a[j-1]
                a[j-1] = a[j].xor(a[j-1])
                a[j] = a[j].xor(a[j-1])
                ans.append("1 ${j}\n")     // Operation 1: swap a[j] with a[j-1]
                count++
                noSwap = false
            }
        }
        if (noSwap) break        // Early termination if no swaps occurred in this pass
    }
    // Sort array 'b' using bubble sort
    for (i in 1..n-1) {
        noSwap = true
        for(j in n-1 downTo i) {
            if (b[j] < b[j-1]) {
                b[j] = b[j].xor(b[j-1])    // XOR swap to exchange values of b[j] and b[j-1]
                b[j-1] = b[j].xor(b[j-1])
                b[j] = b[j].xor(b[j-1]) 
                ans.append("2 ${j}\n")     // Operation 2: swap b[j] with b[j-1]
                count++
                noSwap = false
            }
        }
        if (noSwap) break        // Early termination if no swaps occurred in this pass
    }
    output{
        println(count)
        print(ans)
    }
}


// https://github.com/VaHiX/CodeForces/