#include <iostream>
#include <tuple>
using namespace std;

tuple <int> q = make_tuple(2);



int main() {
	get <0>(q) = 1;
	int y;
	tie(y) = q;
	cout << y << endl;
	return 0;
}
