/*

 Test #3

 ������ �̿��Ͽ� 0���� n������ 1�� ������ ���ϴ�.
 ������ ǥ���� 
 0��° �ڸ��� 0,1,0,1 ... �� �ݺ�
 1��° �ڸ��� 0,0,1,1 ... �� �ݺ�,
 2��° �ڸ��� 0,0,0,0,1,1,1,1�� ������ �ݺ��Ǵ� ������ �̿��մϴ�.

 ����� ���� 1�� ��������, ������ �˰����� ������ ������ ��쿣 0�� ������ �ǹ��մϴ�.
 ������ �Է°��� ������ ���, �� ������ ���� ����(N * 32)���� 0�� ������ �������μ�
 �ʿ��� ������� ���� �� �ֽ��ϴ�.
 2�� �����̹Ƿ�, �־��� ������ ���밪���� 1�� ���� �մϴ�.

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
// �Է°��� ������ ��� ���� ������ŵ�ϴ�.

int count_binaryDigit(ll n) {
	
	int count = 0;

	while (n > 0) {
		n = n >> 1;
		count++;
	}
	return count;
}
// n�� ������ ǥ�� �ִ� �ڸ����� �����մϴ�.


ll count_one(ll num) {
	
	bool pos = true;

	if (num < 0) {
		num = -(++num);
		pos = false;
	} // 2�� ���� ǥ������ ������ ���밪���� 1�� ���� �����ؾ� ��� �˰���� ������ ����� ���� �� �ֽ��ϴ�.

	ll quot, rem;
	ll divider = 2;
	ll result = 0;

	num += 1; // ������ �׻� 0���� �����ϹǷ�, ���ڿ� 1�� ���ϰ� �����ϴ°� ���� �������Դϴ�.
	int count = count_binaryDigit(num);

	while (count > 0) {

		quot = num / divider;
		rem = num % divider;

		result += divider / 2 * quot; // ���� ������ ���� Ƚ���� �ǹ��մϴ�.
		result += (rem > (divider / 2)) ? rem - divider / 2 : 0; // �������� ������ ���� ������ �ǹ��մϴ�.

		divider *= 2;
		count--;
	}

	if (!pos) convert_minus_result(num, result); // �Է°��� -�� ��� ������� ������ŵ�ϴ�.
	
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