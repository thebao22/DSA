#include <iostream>
#include <algorithm>
#define N 100
using namespace std;
int sumarr(int a[], int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
	}
	return sum;
}
int minWeight(int a[], int n, int day) {
    int max = sumarr(a, n);
    int min = *max_element(a, a + n);

    while (min < max) {
        int cap = min + (max - min) / 2;
        int dayr = 1;
        int wpd = 0;
        for (int j = 0; j < n; j++) {
            if (wpd + a[j] > cap) {
                dayr++;
                wpd = 0;
            }
            wpd += a[j];
        }
        if (dayr <= day) {
            max = cap;
        }
        else {
            min = cap + 1;
        }
    }
    return min;
}
void CreateArr(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

}
int main() {
	int a[N];
	int n;
	int day;
	cin >> n;
	CreateArr(a, n);
	sort(a,a+n);
	cout << "nhap ngay can chuyen hang: "; cin >> day;
	cout << "khoi luong nho nhat can chuyen trong mot ngay la: " <<minWeight(a, n, day) << endl;
	system("pause");
	return 0;
}