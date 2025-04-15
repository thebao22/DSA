#include <iostream>
#include <algorithm>
#define N 100
using namespace std;
void triplet(int a[], int n) {
	sort(a, a + n);
	for (int i = 0; i < n-2; i++) {
		if (i>0&&a[i] == a[i - 1]) continue;
		int j = i + 1;
		int k = n-1;
		while (j < k) {
			while (j < k && j + 1 < n && a[j] == a[j + 1]) j++;
			while (j < k && k - 1 >= 0 && a[k] == a[k - 1]) k--;
			if (a[j] + a[k] < -a[i]) j++;
			else if (a[j] + a[k] > -a[i]) k--;
			else { 
				cout << "[ " << a[i] << ", " << a[j] << ", " << a[k] << " ]" << endl;
				j++;
				k--;
			}
		}
	}
}
void CreateArr(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

}
int main() {
	int a[N];
	int n;
	cin >> n;
	CreateArr(a, n);
	triplet(a, n);
	cout << endl;
	system("pause");
	return 0;
}