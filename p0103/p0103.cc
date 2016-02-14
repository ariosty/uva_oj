#include <iostream>
using namespace std;

// insertion sort
void insertSort(int *a, int len) {
    for (int i = 1; i < len; i++) {
        int j = i - 1, data = a[i];
        while (j >= 0 && a[j] > data)
            a[j + 1] = a[j--];
        a[j + 1] = data;
    }
}

// determine whether a fits in b
bool fit(int *a, int *b, int len) {
    for (int i = 0; i < len; i++)
        if (a[i] >= b[i]) return false;
    return true;
}

// main solving procedure
void solve(int k, int n) {
    int **boxes = new int*[k];
    for (int i = 0; i < k; i++) boxes[i] = new int[n];
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            cin >> boxes[i][j];
    for (int i = 0; i < k; i++) insertSort(boxes[i], n);
    int *indices = new int[k];
    for (int i = 0; i < k; i++) indices[i] = i;
    for (int i = 1; i < k; i++) {
        int j = i - 1, *data = boxes[i];
        while (j >= 0 && !fit(boxes[j], data, n)) {
            boxes[j + 1] = boxes[j];
            indices[j + 1] = indices[j];
            j--;
        }
        boxes[j + 1] = data;
        indices[j + 1] = i;
    }
    int *prev = new int[k], *len = new int[k];
    for (int i = 0; i < k; i++) {
        prev[i] = -1;
        len[i] = 1;
    }
    for (int i = 1; i < k; i++) {
        int maxLen = 0, maxJ = 0;
        for (int j = 0; j < i; j++)
            if (fit(boxes[j], boxes[i], n) && len[j] > maxLen) {
                maxLen = len[j];
                maxJ = j;
            }
        prev[i] = maxJ;
        len[i] = maxLen + 1;
    }
    int maxChain = 0;
    for (int i = 1; i < k; i++)
        if (len[i] > len[maxChain])
            maxChain = i;
    int maxLen = len[maxChain];
    cout << maxLen << endl;
    int *chain = new int[maxLen];
    for (int i = 0; i < maxLen; i++) {
        chain[i] = indices[maxChain] + 1;
        maxChain = prev[maxChain];
    }
    for (int i = maxLen - 1; i >= 0; i--) {
        cout << chain[i];
        if (i > 0) cout << " ";
    }
    cout << endl;
    delete[] chain;
    delete[] len;
    delete[] prev;
    delete[] indices;
    for (int i = 0; i < k; i++) delete[] boxes[i];
    delete[] boxes;
}

int main(void) {
    int k,n;
    while (cin >> k >> n) solve(k, n);
    return 0;
}
