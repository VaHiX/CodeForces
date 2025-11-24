// Problem: CF 2118 C - Make It Beautiful
// https://codeforces.com/contest/2118/problem/C

/*
C. Make It Beautiful
Algorithm: Greedily set bits from least significant to most significant.
For each bit position, try to set the bit in all numbers that can afford it within k operations,
prioritizing those with lower current values to maximize the number of 1-bits added.

Time Complexity: O(64 * n) = O(n) (since 64 is constant)
Space Complexity: O(n) for storing the array

Approach:
- Iterate through each bit position from 0 to 63.
- For each bit, go through all elements and see if flipping that bit (setting it to 1) can be done with remaining k operations.
- If yes, perform the flip and reduce k accordingly.
- After processing all bits, count total 1-bits in final array.

*/
import java.util.*;
public class Main {
    public static void main(String[] args) {
      Scanner in=new Scanner(System.in);
      int t=in.nextInt();
      while(t-->0){
        int n=in.nextInt();
        long k=in.nextLong();
        long[] arr=new long[n];
        for(int i=0;i<n;i++)arr[i]=in.nextLong();
        for (int idx = 0; idx < 64; idx++) {        // Iterate over all possible bit positions (0 to 63)
          for (int i = 0; i < n; i++) {
              if ((arr[i] & (1L << idx)) == 0L) {   // Check if the bit at position 'idx' is 0
                  long nextWithBit = (arr[i] | (1L << idx));  // Set that bit to 1
                  long cost = nextWithBit - arr[i];        // Cost to set this bit (i.e., increment value)
                  if (k >= cost) {                          // If we have enough operations
                      k -= cost;                            // Deduct the cost
                      arr[i] = nextWithBit;                 // Perform the update
                  }
                  if(k<0)break;                             // Early exit if no more operations available
              }
              if(k<0)break;
          }
        }
        long c=0;
        for(long x:arr)c+=Long.bitCount(x);    // Count total 1-bits in the modified array
        System.out.println(c-1);               // Output sum of beauties minus one (as per note)
      }
  }
}


// https://github.com/VaHiX/CodeForces/