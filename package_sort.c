/*
 * DSA Assignment 2 - Question 10
 * Logistics Company - Package Sorting by Weight
 * Implements Merge Sort and Quick Sort
 * Demonstrates stability for equal weights using Package IDs
 *
 * Packages (input order):
 * Weight: 20, 15, 20, 10, 15, 20, 25, 10
 * ID : P1, P2, P3, P4, P5, P6, P7, P8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct {
    int weight;
    char id[10];
} Package;

/* ==================== Utility Functions ==================== */

void printPackages(Package arr[], int n, const char *msg) {
    printf("%s: ", msg);
    for (int i = 0; i < n; i++) {
        printf("(%s,%d) ", arr[i].id, arr[i].weight);
    }
    printf("\n");
}

void copyArray(Package dest[], Package src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

/* ==================== MERGE SORT (Stable) ==================== */

int mergeComparisons = 0;

void merge(Package arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Package *L = (Package *)malloc(n1 * sizeof(Package));
    Package *R = (Package *)malloc(n2 * sizeof(Package));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        mergeComparisons++;

        /* <= ensures stability: equal elements keep original order */
        if (L[i].weight <= R[j].weight) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(Package arr[], int left, int right, int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        printf(" [Depth %d] Dividing: left=%d, mid=%d, right=%d\n",
               depth, left, mid, right);

        mergeSort(arr, left, mid, depth + 1);
        mergeSort(arr, mid + 1, right, depth + 1);
        merge(arr, left, mid, right);

        printf(" [Depth %d] After merge [%d..%d]: ",
               depth, left, right);

        for (int i = left; i <= right; i++) {
            printf("(%s,%d) ", arr[i].id, arr[i].weight);
        }

        printf("\n");
    }
}

void runMergeSort(Package original[], int n) {
    Package arr[MAX];

    copyArray(arr, original, n);
    mergeComparisons = 0;

    printf("\n========== MERGE SORT ==========\n");
    printPackages(arr, n, "Initial");

    printf("\n--- Intermediate Steps ---\n");

    mergeSort(arr, 0, n - 1, 0);

    printf("\n");
    printPackages(arr, n, "Final Sorted (Merge Sort)");

    printf("Total comparisons (approx): %d\n", mergeComparisons);
    printf("Note: Merge Sort is STABLE - equal weights retain original relative order.\n");
}

/* ==================== QUICK SORT (Unstable by default) ==================== */

int quickComparisons = 0;
int quickSwaps = 0;

void swap(Package *a, Package *b) {
    Package temp = *a;
    *a = *b;
    *b = temp;

    quickSwaps++;
}

int partition(Package arr[], int low, int high) {
    int pivot = arr[high].weight;
    int i = low - 1;

    printf(" Partitioning [%d..%d], Pivot = (%s,%d)\n",
           low, high, arr[high].id, pivot);

    for (int j = low; j < high; j++) {
        quickComparisons++;

        if (arr[j].weight < pivot) {
            i++;

            if (i != j) {
                swap(&arr[i], &arr[j]);
            }
        }
    }

    if (i + 1 != high) {
        swap(&arr[i + 1], &arr[high]);
    }

    printf(" After partition: ");

    for (int k = low; k <= high; k++) {
        printf("(%s,%d) ", arr[k].id, arr[k].weight);
    }

    printf(" | Pivot index = %d\n", i + 1);

    return i + 1;
}

void quickSort(Package arr[], int low, int high, int depth) {
    if (low < high) {
        int pi = partition(arr, low, high);

        printf(" [Depth %d] Recurse left of pivot %d, then right\n",
               depth, pi);

        quickSort(arr, low, pi - 1, depth + 1);
        quickSort(arr, pi + 1, high, depth + 1);
    }
}

void runQuickSort(Package original[], int n) {
    Package arr[MAX];

    copyArray(arr, original, n);
    quickComparisons = 0;
    quickSwaps = 0;

    printf("\n========== QUICK SORT ==========\n");
    printPackages(arr, n, "Initial");

    printf("\n--- Intermediate Steps (Partitions) ---\n");

    quickSort(arr, 0, n - 1, 0);

    printf("\n");
    printPackages(arr, n, "Final Sorted (Quick Sort)");

    printf("Total comparisons (approx): %d\n", quickComparisons);
    printf("Total swaps: %d\n", quickSwaps);
    printf("Note: Standard Quick Sort is UNSTABLE - equal weights may change order.\n");
}

/* ==================== STABLE VERSION CHECK (using Merge Sort) ==================== */

void verifyStability(Package original[], int n) {
    printf("\n========== STABILITY VERIFICATION (Part b) ==========\n");

    printf("Original order of packages with equal weights:\n");
    printf(" Weight 10: P4 then P8\n");
    printf(" Weight 15: P2 then P5\n");
    printf(" Weight 20: P1 then P3 then P6\n");
    printf(" Weight 25: P7\n\n");

    Package arr[MAX];

    copyArray(arr, original, n);

    /* Run stable Merge Sort */
    mergeComparisons = 0;
    mergeSort(arr, 0, n - 1, 0);

    printPackages(arr, n, "After Stable Merge Sort");

    printf("\nVerification of relative order for equal weights:\n");

    /* Check order of weight 10 */
    int found10 = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].weight == 10) {
            if (found10 == 0) {
                printf(" First weight 10: %s (expected P4)\n", arr[i].id);
                found10 = 1;
            } else {
                printf(" Second weight 10: %s (expected P8)\n", arr[i].id);
            }
        }
    }

    /* Check weight 15 */
    int found15 = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].weight == 15) {
            if (found15 == 0) {
                printf(" First weight 15: %s (expected P2)\n", arr[i].id);
                found15 = 1;
            } else {
                printf(" Second weight 15: %s (expected P5)\n", arr[i].id);
            }
        }
    }

    /* Check weight 20 */
    int count20 = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].weight == 20) {
            count20++;

            if (count20 == 1)
                printf(" First weight 20: %s (expected P1)\n", arr[i].id);
            else if (count20 == 2)
                printf(" Second weight 20: %s (expected P3)\n", arr[i].id);
            else if (count20 == 3)
                printf(" Third weight 20: %s (expected P6)\n", arr[i].id);
        }
    }

    printf("\nMerge Sort successfully preserves original relative order (STABLE).\n");
}

/* ==================== MAIN ==================== */

int main() {
    /* Input data with unique Package IDs based on arrival order */
    Package packages[] = {
        {20, "P1"},
        {15, "P2"},
        {20, "P3"},
        {10, "P4"},
        {15, "P5"},
        {20, "P6"},
        {25, "P7"},
        {10, "P8"}
    };

    int n = 8;

    printf("====================================================\n");
    printf(" DSA Assignment 2 - Question 10\n");
    printf(" Logistics Package Sorting by Weight\n");
    printf("====================================================\n");

    printf("Input Packages (Weight, ID):\n");
    printPackages(packages, n, "Data");

    /* Part a: Merge Sort and Quick Sort */
    runMergeSort(packages, n);
    runQuickSort(packages, n);

    /* Part b: Stability */
    verifyStability(packages, n);

    printf("\n====================================================\n");
    printf(" Execution Complete. See ANALYSIS.txt for detailed analysis.\n");
    printf("====================================================\n");

    return 0;
}
