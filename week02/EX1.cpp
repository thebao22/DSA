#include <iostream>
#define N 100
using namespace std;
int Linearsearch(int a[], int n, int k) {
	int index = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == k) {
			index = i;
			break;
		}
	}
	return index;
}
void CreateArr( int a[],int n){
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
	int index = Linearsearch(a, n, k);
	cout << index << endl;
	system("pause");
	return 0;
}