#include"tables.h"
using namespace std;
//明文初始置换
int plaintext_64[64], plaintext_64_IP[64], mode = 0, key[64], key_56[56];
void hex2bin(int x,int txt[],int tag)
{
    for (int i = 0; i < 8; i++)
    {
        int a = cases[x].txt[i],j = 0;
        if (tag == 1) a = cases[x].key[i];
        while (a > 0) {txt[8*i+7-j]=a%2;a/=2;j++;}
    }
}                

int mkidkey[16][56],tp[4]={26,27,54,55},kidkey[16][48];   
void shiftkey()
{
    for (int j = 0; j < 27; j++)
    {
        mkidkey[0][j] = key_56[j + 1];
        mkidkey[0][j + 28] = key_56[j + 29];
    }
    mkidkey[0][27] = key_56[0]; mkidkey[0][55] = key_56[28];

    for (int i = 1; i < 16; i++)
    {
        if (shift[i] == 1)
        {
            for (int j = 0; j < 27; j++)
            {
                mkidkey[i][j] = mkidkey[i - 1][j + 1];
                mkidkey[i][j + 28] = mkidkey[i - 1][j + 29];
            }
            mkidkey[i][27] = mkidkey[i - 1][0];
            mkidkey[i][55] = mkidkey[i - 1][28];
        }
        if (shift[i] == 2)
        {
            for (int j = 0; j < 26; j++)
            {
                mkidkey[i][j] = mkidkey[i - 1][j + 2];
                mkidkey[i][j + 28] = mkidkey[i - 1][j + 30];
            }
            for (int j = 0; j < 4; j++) mkidkey[i][tp[j]] = mkidkey[i - 1][tp[j] - 26];
        }
    }
}

void lun(int temp[])
{
    int sum = 0, Lturn[17][64],Eres[16][48], S_res[16][32], P_res[16][32];
    memset(S_res,0, sizeof(S_res));
    for (int i = 0; i < 64; i++) Lturn[0][i] = plaintext_64_IP[i];
    for (int i = 1; i < 17; i++)
    {
        for (int j = 0; j < 32; j++) Lturn[i][j] = Lturn[i - 1][j + 32];
        //E扩展+异或
        for (int j = 0; j < 48; j++)
        {
            int te= Lturn[i - 1][E[j] - 1 + 32];
            if (mode == 0) Eres[i - 1][j] = te ^ kidkey[i - 1][j];
            if (mode == 1) Eres[i - 1][j] = te ^ kidkey[16 - i][j];
        }
        //S盒置换
        for (int j = 0; j < 8; j++)
        {
            int a = Eres[i - 1][6 * j] * 2 + Eres[i - 1][6 * j + 5];
            int b = Eres[i - 1][6 * j + 1] * 8 + Eres[i - 1][6 * j + 2] * 4 + Eres[i - 1][6 * j + 3] * 2 + Eres[i - 1][6 * j + 4];
            int c = S[j][a][b]; int ji = 0;
            while (c > 0) { S_res[i - 1][4 * j + 3 - ji] = c % 2; c /= 2; ji++; }
        }
        //P置换
        for (int j = 0; j < 32; j++) P_res[i - 1][j] = S_res[i - 1][P[j] - 1];
        for (int j = 0; j < 32; j++) Lturn[i][j + 32] = Lturn[i - 1][j] ^ P_res[i - 1][j];
    }//最后一次对换
    for (int i = 0; i < 32; i++) { temp[i] = Lturn[16][i + 32]; temp[i + 32] = Lturn[16][i]; }
}

int main()
{
    int idx = 0,cipher[64], temp[64];
    cout << "请输入加解密的mode和测试组别，用空格分开(mode为0表示加密，1解密)." << endl;
    cout << "(输负数则可直接退出程序)\n"; int ii = 0;
    //cout << "二十组加解密测试结果如下：\n"; 
    while (ii<20)
    {
        cout << "输入mode和组别："; cin >> mode >> idx;
        //idx = ii; ii++; if (idx > 9) mode = 1;
        memset(plaintext_64, 0, sizeof(plaintext_64)); memset(plaintext_64_IP, 0, sizeof(plaintext_64_IP)); 
        memset(key, 0, sizeof(key)); memset(key_56, 0, sizeof(key_56));
        idx = 10 * mode + idx; if(mode<0||idx<0) {cout<<"【退出】程序结束\n";return 0; }
        hex2bin(idx, plaintext_64, 0);//得到IP置换后的文本
        for (int i = 0; i < 64; i++) plaintext_64_IP[i] = plaintext_64[IP[i] - 1];
        hex2bin(idx, key, 1); //得到密钥PC-1置换后的文本
        for (int i = 0; i < 56; i++) key_56[i] = key[PC_1[i] - 1];
        shiftkey();//子秘钥移位
        for (int i = 0; i < 16; i++) for (int j = 0; j < 48; j++) kidkey[i][j] = mkidkey[i][PC_2[j] - 1];
        lun(temp);
        for (int i = 0; i < 64; i++) cipher[i] = temp[IP_1[i] - 1];//逆置换
        for (int i = 0; i < 16; i++)
        {
            int resi = cipher[4 * i] * 8 + cipher[4 * i + 1] * 4 + cipher[4 * i + 2] * 2 + cipher[4 * i + 3];
            if (i % 2 == 0) { printf("0x%X", resi); continue; }
            printf("%X", resi); if (i != 15)  cout << ",";
        }
        cout << endl;
    }
}