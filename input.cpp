#include<iostream>
using namespace std;
inline int b_length()
{ system("color 3e");
int l;
cout << "Enter length of board" << endl;
cin >> l;
return l;
}
inline int b_width()
{ int w;
cout << "Enter width of board";
cin >> w;
return w;
}
inline char snk_sk()
{ char temp;
cout << "Enter character to be used as snake's body";
cin >> temp;
return temp;
}
