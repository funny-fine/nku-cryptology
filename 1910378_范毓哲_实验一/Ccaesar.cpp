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
	cout << "���Ϊ�� " << res<< endl;
}

int main()
{
	int flag, offset = 0;
	cout << "������һ�����֣���ѡ����Ҫ���еĲ�����" << endl;
	cout << "(������ʾ��0���ܣ�1���ܣ�2�����������˳�)" << endl;
	while (1) 
	{
		char txt[100]; cout << "ѡ��������� "; cin >> flag;
		switch (flag)
		{
			case 0: cout << "�����ܡ����������ĺ�ƫ������ "; cin >> txt >> offset; JieMi(txt, offset, 1); break; 
			case 1: cout << "�����ܡ����������ĺ�ƫ������ "; cin >> txt >> offset; JieMi(txt, offset, -1); break; 
			case 2: cout << "����������������ƽ�����ģ� "; cin >> txt; cout << "���ܵ�����������¡�" << endl;
				for (int i = 0; i < 26; i++) { cout << "��λΪ  " << i << "  ʱ������"; JieMi(txt, i, -1); } break; 
			default: return 0;
		}
	}
	return 0;
}