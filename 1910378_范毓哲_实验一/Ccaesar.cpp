#include<iostream>
#include<string>
using namespace std;
char res[100];
void JieMi(char *txt, int offset, int tag)
{
	int real_offset = (offset % 26)*tag;
	int length = strlen(txt);
	for (int i = 0; i < length; i++) 
	{
		if (txt[i] >= 65 && txt[i] <= 90) 
		{
			int temp = txt[i] + real_offset;
			if (temp < 65) temp += 26;
			if (temp > 90) temp -= 26;
			res[i] = (char)temp;
			continue;
		}
		if (txt[i] >= 97 && txt[i] <= 122) 
		{
			int temp = txt[i] + real_offset;
			if (temp < 97) temp += 26;
			if (temp > 122) temp -= 26;
			res[i] = (char)temp;
			continue;
		}
		res[i] = txt[i];
	}
	res[length] = '\0';
	cout << "结果为： " << res<< endl;
}

int main()
{
	int flag, offset = 0;
	cout << "请输入一个数字，以选择您要进行的操作。" << endl;
	cout << "(操作提示：0加密，1解密，2攻击，其余退出)" << endl;
	while (1) 
	{
		char txt[100]; cout << "选择操作数： "; cin >> flag;
		switch (flag)
		{
			case 0: cout << "【加密】请输入明文和偏移量： "; cin >> txt >> offset; JieMi(txt, offset, 1); break; 
			case 1: cout << "【解密】请输入密文和偏移量： "; cin >> txt >> offset; JieMi(txt, offset, -1); break; 
			case 2: cout << "【攻击】请输入待破解的密文： "; cin >> txt; cout << "可能的明文情况如下。" << endl;
				for (int i = 0; i < 26; i++) { cout << "移位为  " << i << "  时的明文"; JieMi(txt, i, -1); } break; 
			default: return 0;
		}
	}
	return 0;
}