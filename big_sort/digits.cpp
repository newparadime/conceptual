#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main (void)
{
    int digits = 0;
    char c;
    char* buf = (char*)malloc(16*1024*1024);
    cin >> buf;
    int length = strlen(buf);
/*
    do {
        c = getc(stdin);
        digits++;
        cout << digits << endl;
    } while (c != EOF);
    cout << digits;
*/
    cout << "length=" << length << endl;
    for (int i = 10; i > 0; --i)
    {
        cout << buf[length-i];
    }
}
