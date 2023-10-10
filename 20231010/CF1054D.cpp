#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <unordered_map>
#define int long long
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
template <typename _Tp>
void write(_Tp x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int N = 2e5 + 5;
unordered_map <int, int> mp;
array <int, N> s;
signed main() {
	int n = read(), k = read();
	k = (1 << k) - 1;
	for (int i = 1; i <= n; i++)
		s[i] = read(), s[i] ^= s[i - 1];
	long long ans = 0;
	mp[0]++;
	for (int i = 1; i <= n; i++) {
		if (mp[s[i] ^ k] < mp[s[i]])
			s[i] ^= k;
		ans += mp[s[i]];
		mp[s[i]]++;
	}
	/* puts(""); */
	write(n * (n + 1) / 2 - ans), puts("");
	return 0;
}
