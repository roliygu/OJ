/**
 * author: Roliy
 * pat 1010 https://www.patest.cn/contests/pat-a-practise/1010
 * 题目大概描述:
 * 给定源数source的string表达，和目标数target的string表达。及目标数的进制radix。求，源数是否在某个进制下，
 * 值等于目标数。
 * 关键点:
 *      1. n1,n2(n1和n2最多10位),radix都没有给定范围，所以radix得考虑是unsigned long long(逻辑上不会是负数。)
 *      且n1或者n2不能转成10进制数比较,会溢出。
 *      2. 寻找的时候需要采用二分搜索，不然会超时。
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


inline int char2int(char c) {
    return (c - '0' >= 49) ? (c - '0' - 39) : (c - '0');
}

inline char int2char(int i) {
    return (i < 9) ? i + '0' : i + 39 + '0';
}

// 假设借助unsigned long long能存下
string convert(string origin, int sourceRadix, int targetRadix) {
    if (sourceRadix == targetRadix) {
        return origin;
    }
    unsigned long long digitValue = 0;
    // string digitValue = *(new string());
    for (int i = 0; i != origin.length(); i++) {
        int d = char2int(origin[i]);
        if (d >= sourceRadix) {
            // n进制的串，某位的值肯定不能大于等于n
            return *(new string());
        }
        digitValue *= sourceRadix;
        digitValue += d;
    }
    string res = *(new string());
    while (digitValue != 0) {
        res.push_back(int2char(digitValue % targetRadix));
        digitValue /= targetRadix;
    }
    reverse(res.begin(), res.end());
    return res;
}

// 相等返回0，大于返回1，小于返回-1
int compare(string a, string b){
    if(a.length() == b.length()){
        return a.compare(b);
    } else if(a.length() < b.length()){
        return -1;
    }else{
        return 1;
    }
}

int main() {

    string n1, n2;
    int tag, radix;
    cin >> n1 >> n2 >> tag >> radix;

    string target = (tag==1)?n1:n2;
    string source = (tag==1)?n2:n1;

    // source 能否转成 target
    for(int i=2;i!=36;i++){
        string targetRadixString = convert(source, i, radix);
        if(targetRadixString.length() == 0){
            continue;
        }
        if(compare(targetRadixString, target) == 0){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<"Impossible"<<endl;

    return 0;
}