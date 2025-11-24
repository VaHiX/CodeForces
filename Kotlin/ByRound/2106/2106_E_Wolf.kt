// Problem: CF 2106 E - Wolf
// https://codeforces.com/contest/2106/problem/E

/*
Problem: Wolf Binary Search Optimization
Algorithm: Binary search simulation with optimization using greedy approach
Time Complexity: O(n*q) overall in worst case, but optimized for each query in practice
Space Complexity: O(n) for storing indices and permutation

Key insights:
- We simulate binary search on a permuted array
- We can rearrange elements that are not equal to k to make the search successful
- The minimum number of swaps needed is determined by counting how many elements 
  in the search range would prevent k from being found
- Greedily count mismatches in left/right regions where the binary search path would be obstructed
*/

import java.io.*
import java.util.PriorityQueue
import java.util.TreeMap
import java.util.TreeSet
import kotlin.math.*
typealias ints = IntArray
typealias longs = LongArray
typealias bools = BooleanArray
fun List<Char>.conca():String = this.joinToString("")
val CharArray.conca :String get() = this.joinToString("")
val IntArray.conca :String get() = this.joinToString(" ")
@JvmName("concaInt")
fun List<Int>.conca():String = this.joinToString(" ")
val LongArray.conca:String get() = this.joinToString(" ")
@JvmName("concaLong")
fun List<Long>.conca():String = this.joinToString(" ")
@JvmName("concaString")
fun List<String>.conca():String = this.joinToString("")
fun Int.has(i:Int):Boolean = (this and (1 shl i) != 0)
fun Long.has(i:Int):Boolean = (this and (1L shl i) != 0L)
infix fun Int.mm(b:Int):Int{ return ((this.toLong() * b) % p).toInt() }
infix fun Int.mp(b:Int):Int{ val ans = this + b;return if(ans >= p) ans - p else ans }
infix fun Int.ms(b:Int):Int{ val ans = this - b;return if(ans < 0) ans + p else ans }
const val interactive = false
object Reader{
    private const val BS = 1 shl 16
    private const val NC = 0.toChar()
    private val buf = ByteArray(BS)
    private var bId = 0
    private var size = 0
    private var c = NC
    var lastTC:String = ""
    private var IN: BufferedInputStream = BufferedInputStream(System.`in`, BS)
    val OUT: PrintWriter = PrintWriter(System.out)
    private val char: Char
        get() {
            if(interactive){
                val c = System.`in`.read()
                return if(c == -1) NC else c.toChar()
            }
            while (bId == size) {
                size = IN.read(buf)
                if (size == -1) return NC
                bId = 0
            }
            return buf[bId++].toChar()
        } 
    fun nextLong(): Long {
        var neg = false
        if (c == NC) c = char
        while (c < '0' || c > '9') {
            if (c == '-') neg = true
            if(c == NC) throw Error("Bad Input")
            c = char
        }
        var res = 0L
        while (c in '0'..'9') {
            res = (res shl 3) + (res shl 1) + (c - '0')
            c = char
        }
        return if (neg) -res else res
    }
    fun nextString():String{
        val ret = StringBuilder()
        while (true){
            c = char
            if(c == NC) throw Error("Bad Input")
            if(!isWhitespace(c)){ break}
        }
        do{
            ret.append(c)
            c = char
        }while(!isWhitespace(c))
        return ret.toString()
    }
    private fun isWhitespace(c:Char):Boolean{
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == NC
    }
    fun flush(){
        OUT.flush()
    }
    fun takeString(str:String){
        lastTC = str
        IN = BufferedInputStream(lastTC.byteInputStream(),BS)
    }
    fun takeFile(name:String){
        IN = BufferedInputStream(File(name).inputStream(),BS)
    }
}
fun put(aa:Any){
    Reader.OUT.println(aa)
    if(interactive){ Reader.flush()}
}
fun put(vararg x:Any){
    val count = x.size
    for((pt, c) in x.withIndex()){
        Reader.OUT.print(c)
        if(pt + 1 != count) Reader.OUT.print(" ")
    }
    Reader.OUT.print("\n")
    if(interactive){ Reader.flush()}
}
fun done() = Reader.OUT.close()
val getint:Int get(){ val ans = getlong ; if(ans > Int.MAX_VALUE){IntArray(1000000000);error("Input Overflow")};return ans.toInt() }
val getlong:Long get() = Reader.nextLong()
val getstr:String get() = Reader.nextString()
fun getline(n:Int):IntArray = IntArray(n){getint}
fun getlineL(n:Int):LongArray = LongArray(n){getlong}
const val INF = (1e9).toInt() + 5
const val p = 1_000_000_007
const val multiCase = true
fun main() {
    val t = if (multiCase) getint else 1
    repeat(t) {
        val n = getint
        val q = getint
        val p = IntArray(n) { getint - 1 } // Convert to 0-indexed
        val inds = IntArray(n) // inds[x] = index of value x in permutation
        for (i in 0 until n) {
            inds[p[i]] = i
        }
        val result = IntArray(q)
        repeat(q) {
            var l = getint - 1 // Convert to 0-indexed
            var r = getint - 1
            val x = getint - 1 // Convert to 0-indexed
            val ind = inds[x] // Index of target value x
            if (ind < l || ind > r) {
                // Target is outside the search range
                result[it] = -1
                return@repeat
            }
            // Count of elements that would make search fail on left and right
            var s = x // Number of elements smaller than x that can block left path
            var g = n - x - 1 // Number of elements larger than x that can block right path
            var ss = 0 // Count of mismatches on left side
            var gg = 0 // Count of mismatches on right side
            while (l <= r) {
                val m = l + (r-l) / 2 // Midpoint of current range
                if (p[m] == x) break // Found the target, binary search complete
                if (m > ind) {
                    // Midpoint is to the right of target position
                    if (p[m] < x) gg++ // Wrong direction - would block search
                    g--
                    r = m - 1 // Move left
                } else {
                    // Midpoint is to the left of target position
                    if (p[m] > x) ss++ // Wrong direction - would block search
                    s--
                    l = m + 1 // Move right
                }
            }
            if (s < 0 || g < 0) result[it] = -1 // Impossible case
            else result[it] = (2 * min(ss, gg) + 2 * (max(ss, gg) - min(ss, gg))) // Minimum swaps needed
        }
        put(result.conca)
	}
    done()
}


// https://github.com/VaHiX/CodeForces/