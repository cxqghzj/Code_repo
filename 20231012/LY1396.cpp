#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <ctime>
#include <vector>
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int _N = 5e7 + 5, N = 2e6 + 5;
/* array <int, _N> ksl; */

vector <int> isl;
int main() {
	/* int* isl = new int[_N]; */
	int cnt = 0;
	for (int i = 700; i <= 7072; i++)
		for (int j = i * i + i; j <= 50000000; j += i)
			isl.push_back(j);
	sort(isl.begin(), isl.end());
	auto it = unique(isl.begin(), isl.end());
	isl.erase(it, isl.end());
	write(isl.size()), puts("");
	/* for (auto x : isl) */
		/* write(x), putchar(32); */

	/* write(isl[114514]), puts(""); */
	/* write(cnt), puts(""); */
	for (int i = 1; i <= 5000000; i++) {
		if (isl[i])
			cnt++;
	}
	/* } */
	write(cnt), puts("");
	cout << clock() << endl;
	/* system("pause"); */

	return 0;
}
