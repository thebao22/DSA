#include<iostream>
#define N 100
using namespace std;
int rotate_search_min(int a[], int L, int R) {
	if (L == R) return a[L]; 
	int mid = L + (R - L) / 2;
	if (a[mid] < a[R])
		return rotate_search_min(a, L, mid);
	else 
		return rotate_search_min(a, mid + 1, R);
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
	int index = rotate_search_min(a,0,n-1);
	cout << index << endl;
	system("pause");
	return 0;
}