#include <iostream>
#include <vector>
//这里主要实现字符串匹配,通过BF、KMP两个算法实现
using namespace std;

int BF(string staple,string destination) {
    //BF算法基本思想：取整数i，j用于遍历，从staple和destination的首元素开始比较，元素相同就同时将i，j向后移动，
    //如果不相同就将i返回第一个相同的元素的后一个，将j返回destination的第一个位置
    int i=0,j=0;
    while(i<staple.length()) {
        if(staple[i]==destination[j]) {
            i++,j++;
        }else {
            i=i-j+1;
            j=0;
        }
        if(i>staple.length()-destination.length() && j==0)
            return -1;
        if(j==destination.length())
            return i-j;
    }
}
vector<int> Prefun(string destination) {   //这个函数用于返回任意下标为j时，最大的前后缀相同长度
    int M=destination.length();
    vector<int> lps(M,0);           //创建vector对象存储每个下标对应的长度相同值，并初始化全部是0
    int len=0;                           //第一个字符的前后缀相同长度最大值一定是0
    int i=1;
    while(i<M) {
        if (destination[i] == destination[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
int KMP(string staple,string destination) {
    int i=0,j=0;
    int N=staple.length();
    int M=destination.length();
    vector<int> lps=Prefun(destination);
    while(i<N) {
        if (destination[j] == staple[i]) {
            j++;
            i++;
        }

        if (j == M) {
            cout << "Found pattern at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < N && destination[j] != staple[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}



int main() {
    string str="hello world";
    //cout<<str[3]<<endl;
    cout<<BF("hello world","world")<<endl;
    KMP("hello world","world");
    return 0;
}
