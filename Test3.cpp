/*

 Test #3

 패턴을 이용하여 0부터 n까지의 1의 개수를 셉니다.
 이진수 표에서 
 0번째 자리는 0,1,0,1 ... 이 반복
 1번째 자리는 0,0,1,1 ... 이 반복,
 2번째 자리는 0,0,0,0,1,1,1,1의 패턴이 반복되는 성질을 이용합니다.

 양수인 경우는 1의 개수지만, 동일한 알고리즘을 음수에 적용할 경우엔 0의 개수를 의미합니다.
 때문에 입력값이 음수인 경우, 총 가능한 숫자 개수(N * 32)에서 0의 개수를 빼줌으로서
 필요한 결과값을 얻을 수 있습니다.
 2의 보수이므로, 주어진 음수의 절대값에서 1을 빼야 합니다.

 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define BITS 32
typedef long long ll;

void convert_minus_result(ll& num, ll& result) {
	
	ll sum = BITS * (num);
	result = sum - result;
}
// 입력값이 음수인 경우 값을 반전시킵니다.

int count_binaryDigit(ll n) {
	
	int count = 0;

	while (n > 0) {
		n = n >> 1;
		count++;
	}
	return count;
}
// n의 이진수 표현 최대 자리수를 리턴합니다.


ll count_one(ll num) {
	
	bool pos = true;

	if (num < 0) {
		num = -(++num);
		pos = false;
	} // 2의 보수 표현에선 음수는 절대값에서 1을 빼고 시작해야 양수 알고리즘과 동일한 결과를 얻을 수 있습니다.

	ll quot, rem;
	ll divider = 2;
	ll result = 0;

	num += 1; // 패턴은 항상 0부터 시작하므로, 숫자에 1을 더하고 시작하는게 더욱 직관적입니다.
	int count = count_binaryDigit(num);

	while (count > 0) {

		quot = num / divider;
		rem = num % divider;

		result += divider / 2 * quot; // 몫은 패턴의 수행 횟수를 의미합니다.
		result += (rem > (divider / 2)) ? rem - divider / 2 : 0; // 나머지는 패턴이 끊긴 시점을 의미합니다.

		divider *= 2;
		count--;
	}

	if (!pos) convert_minus_result(num, result); // 입력값이 -인 경우 결과값을 반전시킵니다.
	
	return result;
}


void main() {

	ll a, b;

	cin >> a;
	cin >> b;

	ll result = 0;
	if (a > b) cout << "wrong input" << endl;
	else {

		if(a==0) result = count_one(b);
		else if (a < 0 && b >= 0) result = count_one(a) + count_one(b);
		else if (a > 0 && b >= 0) result = count_one(b) - count_one(a - 1);
		else if (a < 0 && b < 0) result = count_one(a) - count_one(b + 1);
	}
	
	cout << endl <<"Result : "<< result << endl;

	system("PAUSE");
}