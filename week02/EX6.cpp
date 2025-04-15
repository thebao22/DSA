#include <iostream>
#include <vector>
#define N 100
using namespace std;
bool sum_equal_target(int a[], int left, int right, int target) {
	int j = left;
	int k = right;
	while (j < k) {
		if (a[j] + a[k] < target)j++;
		else if (a[j] + a[k] > target) k--;
		else return true;
	}
	return false;
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
	bool check = sum_equal_target(a, 0, n - 1, k);
	if (check) cout << "yes";
	else cout << "No";
	cout << endl;
	system("pause");
	return 0;
}