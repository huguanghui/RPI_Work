#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
#if 0
    {
    char info[100];
//    cin >> info;
//    cin.getline(info, 100);
    cin.get(info, 100);
    cout << info << '\n';
    }
#endif
#if 0
    string stuff;
//    cin >> stuff;
    getline(cin, stuff, ':');
    cout << stuff << '\n';
#endif
#if 1
    ifstream fin;
    fin.open("tobuy.txt");
    if (fin.is_open() == false)
    {
        cerr << "Can't open file. Bye.\n";
        exit(EXIT_FAILURE);
    }
    string item;
    int count = 0;
    getline(fin, item, ':');
    while (fin)
    {
        ++count;
        cout << count << ": " << item << endl;
        getline(fin, item, ':');
    }
    cout << "Done\n";
    fin.close();
#endif

    return 0;
}
