#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct sig2freq{char sig='a'; int num=0;}txtList[26];
bool cmp(sig2freq a, sig2freq b)
{
	return a.num > b.num;
}
int main() 
{
	char re[27];
	cout << "请输入待破译的密文串： " << endl;char text[1000];cin.getline(text, 1000);
	int len = strlen(text);
	
	double num = 0;//所有字母出现的总次数
	for (int i = 0; i < len; i++) 
	{
		text[i] = tolower(text[i]);
		if (text[i] >= 97 && text[i] <= 122) 
		{num++; txtList[text[i] - 'a'].num++;}
	}
	cout << "\n这段文本的字符频率信息统计如下： " << endl;
	for (int i = 0; i < 26; i++) 
	{
		txtList[i].sig='a' + i;
		cout << (char)('a' + i) << "   " << (double)(txtList[i].num/ num) << endl;
	}
	char freq[26] = { 'e','t','o','i','a','n','s','r','h','l','d','u','c','m','p','y','f','g','w','b','v','k','x','j','q','z' };
	sort(txtList, txtList + 26,cmp);
	for (int i = 0; i < 26; i++)  re[freq[i] - 'a'] = txtList[i].sig;
	re[26] = '\0';cout << "\n据此得到的密钥为： " << re << endl;
	return 0;
}