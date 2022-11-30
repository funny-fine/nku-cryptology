#include<iostream>
#include<map>
#include<string>
#include<stdio.h>
using namespace std;
map<char, char> p2cList,c2pList;
bool isk[26];char res[1000];
void getKey(char * CKey)
{
	int t = 0;
	for (int i = 0; i < strlen(CKey); i++)
	{
		CKey[i] = tolower(CKey[i]);
		if (CKey[i] >= 97 && CKey[i] <= 122 && !isk[CKey[i] - 'a'])
		{
			isk[CKey[i] - 'a'] = 1;
			p2cList[(char)('a' + t)] = CKey[i];
			c2pList[CKey[i]] = (char)('a' + t); t++;
		}
	}
	for (int j = t; j < 26; j++)
	{
		char temp = '\0';
		for (int k = 0; k < 26; k++)
		{
			if (isk[k] == 0) { isk[k] = 1;temp = (char)('a' + k);break;}
		}
		p2cList[(char)('a' + j)] = temp;c2pList[temp] = (char)('a' + j);
	}
	cout << endl << "替换表为：  " << endl;
	for (int j = 0; j < 26; j++)  cout << (char)('a' + j) << " "; cout << endl;
	for (int j = 0; j < 26; j++)  cout << p2cList[(char)('a' + j)] << " "; cout << endl;
}
void getRes(char* inTxt, int tag)
{
	int len = strlen(inTxt);
	for (int j = 0; j < len; j++)
	{
		inTxt[j] = tolower(inTxt[j]);
		if (inTxt[j] < 97 || inTxt[j] > 122) res[j] = inTxt[j];
		else 
		{
			if (tag == 0) { res[j] = p2cList.at((char)(inTxt[j])); }
			else { res[j] = c2pList.at((char)(inTxt[j])); }
		}
	}
	res[len] = '\0';cout << "结果： " << res << endl<<endl;
}
int main() 
{
	cout << "请输入一个数字，以选择您要进行的操作。" << endl;
	cout << "(操作提示：0加密，1解密，其余退出。两种操作均需先输入密钥)" << endl;
	while (1) 
	{
		int flag = 0; cout << "选择操作数： "; cin >> flag;
		if(flag>1) { cout << "【退出】程序结束。" << endl; return 0; }

		char CKey[100]; for (int i = 0; i < 26; i++) isk[i] = 0;
		//这里一开始用成memset了，导致程序只能正常运行一次，需要注意
		cout << "请输入您的密钥： "; cin.ignore(); cin.getline(CKey, 100);
		if (strlen(CKey) > 26) CKey[26] = '\0';
		getKey(CKey);//将密钥转换为密钥表
		char plaintext[1000]; char ciphertext[1000];
		if (flag == 0)
		{
			cout << "【加密】请输入需加密的明文： ";
			cin.getline(plaintext, 1000);
			getRes(plaintext, 0);
		}
		else if(flag == 1)
		{
			cout << "【解密】请输入需解密的密文： ";
			cin.getline(ciphertext, 1000);
			getRes(ciphertext, 1);
		}
		p2cList.clear(); c2pList.clear();
	}
	return 0;
}