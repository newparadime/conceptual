#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;
		cout << setw(0);
        cout << "0x" << nouppercase << hex << (int)A << endl;
        cout << setw(15) << dec << right << showpos << setfill('_') << fixed << setprecision(2) << B << endl;
        cout << noshowpos << uppercase << scientific << setprecision(9) << C << endl;
	}
	return 0;

}
