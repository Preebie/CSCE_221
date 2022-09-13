#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int power_two(int num) {
	int last = 0;
	int rem = num % 2;
	
	last += rem;
	if (num != 1) {
		
		last += (power_two(num / 2)*10);
		cout << last << endl;
		
	}

	return last;
}

bool prime(int x) {
	for (int n = 2; n < x / 2; n++) {
		if (x % n == 0) {
			return false;
		}
		return true;
	}
}

long long power(long long x, int n) {
	int number = x;
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return x;
	}

	if (n % 2 == 0)
		for (int i = 0; i < n / 2; i++)
			x *= x;
	else {
		for (int i = 0; i < n / 2; i++) {
			cout << n << endl;
			x *= x;
		}
		x *= number;
	}
	return x;
}

int main() {
	cout << power(17, 3);
}