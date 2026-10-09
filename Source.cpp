#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

const int N = 1000000;

int partition(double A[], int left, int right)
{
    double pivot = A[(left + right) / 2];

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (A[i] < pivot)
            i++;

        while (A[j] > pivot)
            j--;

        if (i <= j)
        {
            swap(A[i], A[j]);
            i++;
            j--;
        }
    }

    return i;
}

void QuickSort(double A[], int left, int right)
{
    if (left < right)
    {
        int p = partition(A, left, right);

        QuickSort(A, left, p - 1);
        QuickSort(A, p, right);
    }
}

void Heapify(double A[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i)
    {
        swap(A[i], A[largest]);

        Heapify(A, n, largest);
    }
}

void HeapSort(double A[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(A, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(A[0], A[i]);

        Heapify(A, i, 0);
    }
}

void Merge(double A[], double temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (A[i] <= A[j])
        {
            temp[k] = A[i];
            i++;
        }
        else
        {
            temp[k] = A[j];
            j++;
        }

        k++;
    }

    while (i <= mid)
    {
        temp[k] = A[i];
        i++;
        k++;
    }

    while (j <= right)
    {
        temp[k] = A[j];
        j++;
        k++;
    }

    for (int i = left; i <= right; i++)
        A[i] = temp[i];
}

void MergeSort(double A[], double temp[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        MergeSort(A, temp, left, mid);
        MergeSort(A, temp, mid + 1, right);

        Merge(A, temp, left, mid, right);
    }
}


int main()
{
    double* original = new double[N];
    double* A = new double[N];
    double* B = new double[N];
    double* C = new double[N];
    double* D = new double[N];
    double* temp = new double[N];

    for (int k = 1; k <= 10; k++)
    {
        string tenFile = "data/data" + to_string(k) + ".bin";

        ifstream f(tenFile, ios::binary);

        if (!f)
        {
            cout << "Khong mo duoc file: " << tenFile << endl;
            return 1;
        }

        f.read((char*)original, N * sizeof(double));
        f.close();

        for (int i = 0; i < N; i++)
            A[i] = original[i];

        auto start = high_resolution_clock::now();

        QuickSort(A, 0, N - 1);

        auto end = high_resolution_clock::now();

        long long timeQuick =
            duration<double, milli>(end - start).count();

        for (int i = 0; i < N; i++)
            B[i] = original[i];

        start = high_resolution_clock::now();

        HeapSort(B, N);

        end = high_resolution_clock::now();

        long long timeHeap =
            duration<double, milli>(end - start).count();

        for (int i = 0; i < N; i++)
            C[i] = original[i];

        start = high_resolution_clock::now();

        MergeSort(C, temp, 0, N - 1);

        end = high_resolution_clock::now();

        long long timeMerge =
            duration<double, milli>(end - start).count();


        for (int i = 0; i < N; i++)
            D[i] = original[i];

        start = high_resolution_clock::now();

        sort(D, D + N);

        end = high_resolution_clock::now();

        long long timeStdSort =
            duration<double, milli>(end - start).count();

        cout << "\n====================================" << endl;
        cout << "DATA " << k << endl;
        cout << "====================================" << endl;

        cout << "QuickSort : " << timeQuick << " ms" << endl;
        cout << "HeapSort  : " << timeHeap << " ms" << endl;
        cout << "MergeSort : " << timeMerge << " ms" << endl;
        cout << "sort      : " << timeStdSort << " ms" << endl;
    }

    delete[] original;
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;
    delete[] temp;

    return 0;
}