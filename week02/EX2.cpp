#include<iostream>
#define N 100
using namespace std;
int Linearsearch_With_sentinel(int a[], int n, int k) {
	int tmp = a[n - 1];
	a[n - 1] = k;
	int i = 0;
	while (i < n - 1) {
		if (a[i] != k) {
			i++;
		}else break;
	}
	a[n - 1] = tmp;
	if (i < n - 1 || tmp == k) {
		return i;
	}
	return -1;
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
	int k;
	cout << "nhap key muon tim: "; cin >> k;
	int index = Linearsearch_With_sentinel(a, n, k);
	cout << index << endl;
	system("pause");
	return 0;
}