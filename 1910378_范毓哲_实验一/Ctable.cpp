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
	cout << endl << "�滻��Ϊ��  " << endl;
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
	res[len] = '\0';cout << "����� " << res << endl<<endl;
}
int main() 
{
	cout << "������һ�����֣���ѡ����Ҫ���еĲ�����" << endl;
	cout << "(������ʾ��0���ܣ�1���ܣ������˳������ֲ���������������Կ)" << endl;
	while (1) 
	{
		int flag = 0; cout << "ѡ��������� "; cin >> flag;
		if(flag>1) { cout << "���˳������������" << endl; return 0; }

		char CKey[100]; for (int i = 0; i < 26; i++) isk[i] = 0;
		//����һ��ʼ�ó�memset�ˣ����³���ֻ����������һ�Σ���Ҫע��
		cout << "������������Կ�� "; cin.ignore(); cin.getline(CKey, 100);
		if (strlen(CKey) > 26) CKey[26] = '\0';
		getKey(CKey);//����Կת��Ϊ��Կ��
		char plaintext[1000]; char ciphertext[1000];
		if (flag == 0)
		{
			cout << "�����ܡ�����������ܵ����ģ� ";
			cin.getline(plaintext, 1000);
			getRes(plaintext, 0);
		}
		else if(flag == 1)
		{
			cout << "�����ܡ�����������ܵ����ģ� ";
			cin.getline(ciphertext, 1000);
			getRes(ciphertext, 1);
		}
		p2cList.clear(); c2pList.clear();
	}
	return 0;
}