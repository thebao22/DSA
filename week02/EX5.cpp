#include <iostream>
#include <vector>
#define N 100
using namespace std;
int minimal_length_of_sum(int a[], int left, int right ,int target) {
	int j = left;
	int k = left;
	int min_length =right - left + 2;
	int current_length = 0;
	int sum = 0;
	for (j; j <= right; j++) {
		sum += a[j];
		current_length++;
		while (sum >= target) {
			if (current_length < min_length) {
				min_length = current_length;
			}
			sum -= a[k];
			k++;
			current_length--;
		}
	}
	if (min_length == right - left + 2) return 0;
	return min_length;
}
void CreateArr(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] < 0)a[i] = -a[i];
	}

}

int main() {
	int a[N];
	int n;
	cin >> n;
	CreateArr(a, n);
	int k;
	cout << "nhap target: "; cin >> k;
	int index = minimal_length_of_sum(a,0,n-1,k);
	cout << index << endl;
	system("pause");
	return 0;
}