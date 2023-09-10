#include <iostream>
#include <string>
#include <ctype.h>
#include <math.h>

using namespace std;

string second_part(string num);
string second_part_to_base(long double num, int base);
string convert_to_base(string num, int base);
long double convert_second_part_to_decimal(string num, int base);
long double convert_to_decimal(string num, int base);
string base_sum(string num1, string num2, int base);
string base_multiplication(string num1, string num2, int base);
string base_sub(string num1, string num2, int base);

struct Number {
	string num;
	string exponent;
};

struct bytes_number {
	string fourbyte;
	string eightbyte;
	string hex_num;
};

string second_part(string num) {
	string result = "0";
	for (int i = num.find("."); i < num.size(); i++) {
		result += num[i];
	}
	return result;
}

string second_part_to_base(long double num, int base) {
	string result;
	string first;
	string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (num != 0) {
		num = num * base;
		for (int i = 0; i < to_string(num).find("."); i++) {
			first += to_string(num)[i];
		}
		result += digits[stoi(first)];
		num = num - stoi(first);
		first = "";
	}
	return result;
}

string convert_to_base(string num, int base) {
	bool flag = false, flag_minus = false;
	string result;
	long double second_part_num;
	int first_num;
	string result_base;
	string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (num.find("-") < num.size()) {
		flag_minus = true;
		num.erase(0, 1);
	}
	if (num.find(".") < num.size()) {
		flag = true;
		second_part_num = stod(second_part(num));
		result_base = second_part_to_base(second_part_num, base);
	}
	first_num = stoi(num);
	while (first_num > 0) {
		result = digits[first_num % base] + result;
		first_num = first_num / base;
	}
	if (flag == true) {
		if (flag_minus == true) {
			return "-" + result + "." + result_base;
		}
		return result + "." + result_base;
	}
	else {
		if (flag_minus == true) {
			return "-" + result + result_base;
		}
		return result + result_base;
	}
}

long double convert_second_part_to_decimal(string num, int base) {
	int j = -1;
	long double result = 0.0;
	for (int i = num.find(".") + 1; i < num.size(); i++) {
		int digit = num[i];
		if (isdigit(digit)) {
			result += (digit - '0') * pow(base, j);
		}
		else {
			result += (digit - 'A' + 10) * pow(base, j);
		}
		j--;
	}
	return result;
}

long double convert_to_decimal(string num, int base) {
	bool flag_minus = false;
	long double result = 0.0;
	int j = 0;
	string second_part_num;
	double result_second_part = 0.0;
	if (num.find("-") < num.size()) {

		flag_minus = true;
		num.erase(0, 1);
	}
	int start = num.size() - 1;
	if (num.find(".") < num.size()) {
		start = num.find(".") - 1;
		second_part_num = second_part(num);
		result_second_part = convert_second_part_to_decimal(second_part_num, base);
	}
	for (int i = start; i >= 0; i--) {
		int digit = num[j];

		if (isdigit(digit)) {
			result += (digit - '0') * pow(base, i);
		}
		else {
			result += (digit - 'A' + 10) * pow(base, i);
		}

		j++;
	}
	result += result_second_part;
	if (flag_minus) {
		result = -result;
	}
	return result;
}

string base_sum(string num1, string num2, int base) {
	long double number1 = convert_to_decimal(num1, base);
	long double number2 = convert_to_decimal(num2, base);
	long double sum_result = number1 + number2;
	return convert_to_base(to_string(sum_result), base);
}
string base_multiplication(string num1, string num2, int base) {
	long double number1 = convert_to_decimal(num1, base);
	long double number2 = convert_to_decimal(num2, base);
	long double sum_result = number1 * number2;
	return convert_to_base(to_string(sum_result), base);
}

string base_sub(string num1, string num2, int base) {
	long double number1 = convert_to_decimal(num1, base);
	long double number2 = convert_to_decimal(num2, base);
	long double sub_result = number1 - number2;
	return (sub_result < 0) ? "-" + convert_to_base(to_string(abs(sub_result)), base) : convert_to_base(to_string(sub_result), base);
}

Number normalize_number(string num) {
	Number result;
	if (num.find(".") < num.size()) {
		string bin_num = convert_to_base(num, 2);
		int dotpos = bin_num.find(".");
		string exponent = to_string(bin_num.find(".") - 1);
		result.exponent = exponent;
		bin_num.erase(dotpos, 1);
		bin_num.insert(1, ".");
		result.num = bin_num;
		return result;
	}
	else {
		result.num = num;
		result.exponent = "0";
		return result;
	}
}

bytes_number decimal_to_byte(string num) {
	string bin_num;
	bytes_number result;
	string fourbyte,eightbyte,decimal_num,hex_num;
	long double nums = abs(stod(num));
	num = to_string(nums);
	string base_num = convert_to_base(num, 2);
	string normalize_num = normalize_number(num).num;
	string exponent = normalize_number(num).exponent;
	string offset = convert_to_base(to_string(stoi(exponent) + 1023), 2);
	if (num.find("-") < num.size()) {
		bin_num = "0" + offset + normalize_num.erase(0,2);
	}
	else {
		bin_num = "1" + offset + normalize_num.erase(0,2);
	}
	while(bin_num.size() % 4 != 0){
		bin_num += "0";
	}
	decimal_num = to_string(convert_to_decimal(bin_num, 2));
	hex_num = convert_to_base(decimal_num, 16);
	if (hex_num.find(".") < hex_num.size()) {
		hex_num.erase(hex_num.find("."), 1);
	}
	while (bin_num.size() != 32) {
		bin_num += "0";
	}
	fourbyte = bin_num;
	while (bin_num.size() != 64) {
		bin_num += "0";
	}
	while (hex_num.size() != 16) {
		hex_num += "0";
	}
	result.hex_num = hex_num;
	eightbyte = bin_num;
	result.fourbyte = fourbyte;
	result.eightbyte = eightbyte;
	return result;
}

int main() {
	// cout << decimal_to_byte("123.5").hex_num << endl;
	// cout << normalize_number("123.5").num << endl;
	return 0;
}