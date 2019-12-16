#include <iostream>

void modifica_char(char & toModify, const char toCopy)
{
    toModify = toCopy;
}
int main()
{
    using namespace std;
    char toModify = '0',toCopy;
    cin >> toCopy;
    modifica_char(toModify,toCopy);
    cout << toModify << std::endl;

    return 1;
}