#pragma comment(lib, "shell32.lib")

//#define DEBUG

#ifdef DEBUG
#include <fstream> 
#include <iostream>
#endif

#include <string> 
#include <tchar.h>
#include <Windows.h>

using namespace std;

string urlDecode(const string &src);

int _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpCmdLine, int cmdShow)
{

    string url = lpCmdLine;
	url = urlDecode(url);
    
    if(url[0] == '"')
        url = url.substr(1, url.length()-2); // zbavim se uvozovek
        
    if(url.find("sourcetree://cloneRepo/?cloneUrl=") == 0)
        url = url.replace(0,33,"github-windows://openRepo/");
                
    if(url.find("sourcetree://") == 0)
        url = url.replace(0,13,"github-windows://");
        
	if(url.find("&type=") > 0) 
		url = url.substr(0, url.find("&type="));

	
    #ifdef DEBUG
    ofstream out("c:\\Users\\Uzivatel\\Documents\\Visual Studio 2010\\Projects\\C++ - Console\\browser_sourcetree_github\\debug.txt"); 
    out << url.c_str() << "\norig: " << lpCmdLine;
    out.close();
	#else
		
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
    
	#endif
    
    
    return 0;
}



string urlDecode(const string &src) {
    string ret;
    unsigned int chcode;
    unsigned char ch;
	
    for (std::string::size_type i=0; i < src.length(); i++) 
	{
        if(src[i]=='%') 
		{
            sscanf(src.substr(i+1,2).c_str(), "%x", &chcode);
            ch = static_cast<unsigned char>(chcode);
            ret += ch;
            i += 2;
        } 
		else 
		{
            ret += src[i];
        }
    }
    return ret;
}