#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <string>

using namespace std;

#if defined(__USE_VECTOR__)
void delay(int time)
{
    time *= 1000 * 1000;
    while(time--);
}

void swap(vector<int>& src, int s1, int s2, int line)
{
    int tmp = src.at(s1);
    src.at(s1) = src.at(s2);
    src.at(s2) = tmp;
    // cout << "[" << __FILE__ << ":" << line << "] Swap s1:s2 = " << s1 << "(" << src.at(s1) << "):" << s2 << "(" << src.at(s2) << ")\n";
}

void showData(vector<int>& src, int first, int last, int line)
{
    return;
    cout << "[" << __FILE__ << ":" << line << "] ";
    for(int k = 0;k < src.size();k++) {
        if(k == first || (first == 0 && k == 0)) {
            cout << "|=> ";
        }
        cout << src.at(k) << ' ';
        if(k == last) {
            cout << "<=| ";
        }
    }
    cout << '\n';
}

void quickSort(vector<int>& src, int first, int last)
{
    int pivot = (last - first) / 2 + first;
#if 0
    cout << "[" << __FILE__ << ":" << __LINE__ << "] first:pivot:last = " << first << ":" << pivot << ":" << last << '\n';
#endif
    showData(src, first, last, __LINE__);

    if(pivot - first >= 1 && last - pivot >= 1) {
        if(first < pivot) {
            // cout << "first run" << '\n';
            quickSort(src, first, pivot);
        }
        if(last > pivot) {
            // cout << "last run" << '\n';
            quickSort(src, pivot + 1, last);
        }
    }

    while(1) {
        int count = 0;
        int highFound = 0;
        int lowFound = 0;
        int i = first;
        int j = last;

        // cout << "[" << __FILE__ << ":" << __LINE__ << "] first:pivot:last = " << first << ":" << pivot << ":" << last << '\n';
        while(1) {
            // delay(100);
            // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp first:last:i:j:pivot = " << first << ":" << last << ":" << i << ":" << j << ":" << pivot << "(" << src.at(pivot) << ")\n";
            if(i >= j) {
                if(lowFound == 1) {
                    swap(src, pivot, i, __LINE__);
                    count++;
                }
                else if(highFound == 1) {
                    swap(src, pivot, j, __LINE__);
                    count++;
                }
                else if(((i == j) && (i < pivot && src.at(i) > src.at(pivot)) || (i > pivot && src.at(i) < src.at(pivot)))) {
                    swap(src, pivot, i, __LINE__);
                    count++;
                }
                if(count > 0) {
                    showData(src, first, last, __LINE__);
                }
                break;
            }

            // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp i:pivot:j = " << i << "(" << src.at(i) << "):" << pivot << "(" << src.at(pivot) << "):" << j << "(" << src.at(j) << ")\n";
            if(src.at(i) > src.at(pivot)) {
                lowFound = 1;
                // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp i:pivot = " << i << "(" << src.at(i) << "):" << pivot << "(" << src.at(pivot) << ")\n";
            }
            else {
                // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp i:pivot = " << i << ":" << pivot << "\n";
                if(i < last) {
                    i++;
                }
            }

            if(src.at(j) < src.at(pivot)) {
                highFound = 1;
                // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp j:pivot = " << j << "(" << src.at(j) << "):" << pivot << "(" << src.at(pivot) << ")\n";
            }
            else {
                if(j > first) {
                    j--;
                }
            }

            if(lowFound == 1 && highFound == 1) {
                swap(src, j, i, __LINE__);
                lowFound = 0;
                highFound = 0;
                count++;
                showData(src, first, last, __LINE__);
                // break;
            }
        }
#if 0
        cout << "[" << __FILE__ << ":" << __LINE__ << "] count = " << count << '\n';
#endif
        showData(src, first, last, __LINE__);
        if(count == 0) {
            // cout << "[" << __FILE__ << ":" << __LINE__ << "] first:pivot:last = " << first << ":" << pivot << ":" << last << '\n';
            break;
        }
    }
}
#endif  /* __USE_VECTOR__ */

#if !defined(__USE_VECTOR__)
static void merge(int* orig, int start, int mid, int end, int* result)
{
    int L, R, k, a;
    L = start;
    R = mid + 1;
    k = start;
 
    while(L <= mid && R <= end) {
        result[k++] = orig[L] <= orig[R] ? orig[L++] : orig[R++];
    }
 
    if(L>mid) {
        for(a = R; a <= end; a++) {
            result[k++] = orig[a];
        }
    }
    else {
        for(a = L; a <= mid; a++) {
            result[k++] = orig[a];
        }
    }
     
    for(a = start; a <= end; a++) {
        orig[a] = result[a];
    }
}

static void mergeSort(int* orig, int start, int end, int* result)
{
    // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp start:end = " << start << ":" << end << '\n';
    // 원소가 2개 이상이라면
    if(start < end) {
        // 중앙 값을 구하고
        int mid = (start + end) / 2;
        // 중앙을 기준으로 2개의 그룹으로 분할
        mergeSort(orig, start, mid, result);
        mergeSort(orig, mid+1, end, result);
        // 정렬 후 병합
        merge(orig, start, mid, end, result);
    }
    // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp start:end = " << start << ":" << end << '\n';
}
#endif  /* !__USE_VECTOR__ */
void sortNumber(vector<int>& src, int* orig, int size, int* result)
{
#if defined(__USE_VECTOR__)
    // quickSort(src, 0, src.size() - 1);
#else
    if(size == 1) {
        result[0] = orig[0];
        return;
    }
    // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp \n";
    mergeSort(orig, 0, size - 1, result);
    // cout << "[" << __FILE__ << ":" << __LINE__ << "] Stamp \n";
#endif  /* __USE_VECTOR__ */
}

int main(void)
{
    enum {
        MIN = 0,
        MAX = 1000000,
        N_MIN = -1000000,
        N_MAX = 1000000,
    };

    int input = -1;
    vector<int> buf;
    int *result;
    int *orig;
    int size = 0;

    cin.tie(NULL);
    ios::sync_with_stdio(false);
   
    cin >> input;
    if(input < MIN || input > MAX) {
        cout << "Invalid value input(" << input << ");" << endl;
        return -1;
    }
    size = input;

    orig = new int[size];
    for(int i = 0;i < size;i++) {
        cin >> input;
        if(input < N_MIN || input > N_MAX) {
            cout << "Invalid value input(" << input << ");" << endl;
            return -1;
        }
        buf.push_back(input);
        orig[i] = input;
    }
    result = new int[size];
    sortNumber(buf, orig, size, result);

    // for(int j = 0;j < buf.size();j++) {
    //     cout << buf.at(j) << '\n';
    // }
    for(int k = 0;k < size;k++) {
        cout << result[k] << '\n';
    }

    delete []result;
    delete []orig;

    return 0;
}