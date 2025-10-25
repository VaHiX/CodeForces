// Problem: CF 1857 F - Sum and Product
// https://codeforces.com/contest/1857/problem/F

/*
 * Problem: F. Sum and Product
 * 
 * Purpose: Given an array of integers, for each query (x, y), count the number of pairs (i, j)
 *          such that a[i] + a[j] = x and a[i] * a[j] = y, where i < j.
 * 
 * Approach:
 * 1. For each query, we derive the two numbers from sum x and product y using the quadratic formula.
 *    If x^2 - 4y is negative or not a perfect square, there are no valid pairs.
 * 2. Otherwise, we calculate a1 = (x + sqrt(x^2 - 4y)) / 2 and a2 = (x - sqrt(x^2 - 4y)) / 2.
 * 3. Count frequency of a1 and a2 in the array using a hash map.
 * 4. If a1 == a2, count combinations of pairs from those elements: C(n,2) = n*(n-1)/2.
 *    Otherwise, multiply counts of a1 and a2.
 * 
 * Time Complexity: O(n + q * sqrt(max_val)) per test case, where max_val is up to 1e18 (but sqrt is bounded).
 * Space Complexity: O(n) for the hash map storing frequencies.
 * 
 * Algorithms/Techniques:
 * - Hash map for fast frequency lookup
 * - Mathematical derivation using quadratic formula
 * - Collision resolution in hash map using linear probing
 */

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define MAX_SIZE 200000

typedef struct {
  long long key;
  int value;
} Entry;

typedef struct {
  Entry *entries;
  int size;
  int capacity;
} HashMap;

HashMap *createHashMap(int capacity) {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->entries = (Entry *)calloc(capacity, sizeof(Entry));
  map->size = 0;
  map->capacity = capacity;
  return map;
}

void freeHashMap(HashMap *map) {
  free(map->entries);
  free(map);
}

void insert(HashMap *map, long long key) {
  int index = labs(key) % map->capacity;
  // Linear probing to handle collisions
  while (map->entries[index].value != 0 && map->entries[index].key != key) {
    index = (index + 1) % map->capacity;
  }
  if (map->entries[index].key == key) {
    map->entries[index].value++;
  } else {
    map->entries[index].key = key;
    map->entries[index].value = 1;
    map->size++;
  }
}

int get(HashMap *map, long long key) {
  int index = labs(key) % map->capacity;
  // Linear probing to find key
  while (map->entries[index].value != 0 && map->entries[index].key != key) {
    index = (index + 1) % map->capacity;
  }
  return map->entries[index].value;
}

void solve() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    long long *a = (long long *)malloc(n * sizeof(long long));
    HashMap *map = createHashMap(2 * n); // Doubling capacity to reduce collisions
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i]);
      insert(map, a[i]); // Populate hash map with frequencies
    }
    int q;
    scanf("%d", &q);
    while (q--) {
      long long x, y;
      scanf("%lld %lld", &x, &y);
      long long discriminant = x * x - 4 * y;
      if (discriminant < 0) {
        printf("0 ");
        continue;
      }
      long long sqrt_discriminant = sqrt(discriminant);
      // Check if discriminant is a perfect square
      if (sqrt_discriminant * sqrt_discriminant != discriminant) {
        printf("0 ");
        continue;
      }
      long long a1 = (x + sqrt_discriminant) / 2;
      long long a2 = (x - sqrt_discriminant) / 2;
      // Verify the calculated values are correct
      if (a1 + a2 != x || a1 * a2 != y) {
        printf("0 ");
        continue;
      }
      int count1 = get(map, a1);
      int count2 = get(map, a2);
      if (a1 == a2) {
        // If both roots are equal, compute combinations
        printf("%lld ", (long long)count1 * (count1 - 1) / 2);
      } else {
        // Otherwise multiply their frequencies
        printf("%lld ", (long long)count1 * count2);
      }
    }
    printf("\n");
    free(a);
    freeHashMap(map);
  }
}

int main() {
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/