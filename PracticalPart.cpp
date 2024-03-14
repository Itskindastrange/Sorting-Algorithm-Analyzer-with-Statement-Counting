#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& arr);
void bubbleSort(vector<int>& arr);
void selectionSort(vector<int>& arr);
void quickSort(vector<int>& arr, int low, int high);
void mergeSort(vector<int>& arr, int left, int right);
void countSort(vector<int>& arr);
void bucketSort(vector<int>& arr);
void radixSort(vector<int>& arr);

int countStatements = 0;


void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}


void processInputFile(const string& inputFile, const string& outputFile) {
    ifstream input(inputFile);
    ofstream output(outputFile);

    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }

    string line;
    int arrayCount = 1;

    while (getline(input, line)) {
        vector<int> inputArray;
        stringstream ss(line);
        int num;
        while (ss >> num) {
            inputArray.push_back(num);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
        vector<int> countCheck;
        countStatements = 0;

        auto start = high_resolution_clock::now();
        insertionSort(inputArray);
        auto stop = high_resolution_clock::now();
        auto insertionSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        countStatements = 0;
        start = high_resolution_clock::now();
        bubbleSort(inputArray);
        stop = high_resolution_clock::now();
        auto bubbleSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        countStatements = 0;
        start = high_resolution_clock::now();
        selectionSort(inputArray);
        stop = high_resolution_clock::now();
        auto selectionSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        countStatements = 0;
        start = high_resolution_clock::now();
        quickSort(inputArray, 0, inputArray.size() - 1);
        stop = high_resolution_clock::now();
        auto quickSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        countStatements = 0;
        start = high_resolution_clock::now();
        mergeSort(inputArray, 0, inputArray.size() - 1);
        stop = high_resolution_clock::now();
        auto mergeSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        countStatements = 0;
        start = high_resolution_clock::now();
        countSort(inputArray);
        stop = high_resolution_clock::now();
        auto countSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        countStatements = 0;
        start = high_resolution_clock::now();
        bucketSort(inputArray);
        stop = high_resolution_clock::now();
        auto bucketSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        countStatements = 0;
        start = high_resolution_clock::now();
        radixSort(inputArray);
        stop = high_resolution_clock::now();
        auto radixSortDuration = duration_cast<microseconds>(stop - start);
        countCheck.push_back(countStatements);
        vector<pair<string, long long>> timings = {
            {"Insertion Sort", insertionSortDuration.count()},
            {"Bubble Sort", bubbleSortDuration.count()},
            {"Selection Sort", selectionSortDuration.count()},
            {"Quick Sort", quickSortDuration.count()},
            {"Merge Sort", mergeSortDuration.count()},
            {"Count Sort", countSortDuration.count()},
            {"Bucket Sort", bucketSortDuration.count()},
            {"Radix Sort", radixSortDuration.count()}
        };
        sort(timings.begin(), timings.end(), [](const pair<string, long long>& a, const pair<string, long long>& b) {
            return a.second < b.second;
            });

        output << "Input Array " << arrayCount << ":" << endl;
        for (int i = 0; i < inputArray.size(); i++) {
            output << inputArray[i] << " ";
        }
        output << endl; 
        output << "Result:" << endl;
        output << "Best performing algorithm: " << timings[0].first << endl;
        output << "Worst performing algorithm: " << timings.back().first << endl << endl;

        output << "ALGORITHM--------TIME---------RAM MODEL" << endl;
        int i = 0;
        for (const auto& timing : timings) {
            output << timing.first << "......" << timing.second << "sec--- "<<countCheck[i]<<" \n";
            i++;
        }
        //for (int i = 0; i < countCheck.size(); i++)
        //{
        //    output << countCheck[i] << "\n";
        //}
        output << endl;

        arrayCount++;
    }

    input.close();
    output.close();
}






void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            countStatements++;
        }
        arr[j + 1] = key;
        countStatements++;
    }
}


void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                countStatements += 3;
            }
            countStatements += 2;
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
                countStatements++;
            }
            countStatements++;
        }
        swap(arr[i], arr[minIndex]);
        countStatements += 3;
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            countStatements += 3;
        }
        countStatements += 2;
    }
    swap(arr[i + 1], arr[high]);
    countStatements += 3;
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
        countStatements += 2;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        countStatements += 2;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        countStatements += 2;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void countSort(vector<int>& arr) {
    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;

    vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - min_val]++;
        countStatements++;
    }
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
        countStatements++;
    }
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
        countStatements += 2;
    }
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
        countStatements++;
    }
}

void bucketSort(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> buckets(n);

    for (int i = 0; i < n; ++i) {
        int bucket_index = n * arr[i] / (INT_MAX + 1LL);
        buckets[bucket_index].push_back(arr[i]);
        countStatements++;
    }

    for (int i = 0; i < n; ++i) {
        sort(buckets[i].begin(), buckets[i].end());
        countStatements++;
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < buckets[i].size(); ++j) {
            arr[index++] = buckets[i][j];
            countStatements++;
        }
    }
}

void radixSort(vector<int>& arr) {
    int max_num = *max_element(arr.begin(), arr.end());
    for (int exp = 1; max_num / exp > 0; exp *= 10) {
        vector<int> output(arr.size());
        vector<int> count(10, 0);

        for (int i = 0; i < arr.size(); i++) {
            count[(arr[i] / exp) % 10]++;
            countStatements++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
            countStatements++;
        }

        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
            countStatements += 2;
        }

        for (int i = 0; i < arr.size(); i++) {
            arr[i] = output[i];
            countStatements++;
        }
    }
}


int main() {

    processInputFile("input.txt", "output.txt");

    return 0;
}