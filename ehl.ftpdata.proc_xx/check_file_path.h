
#ifndef _check_file_path_h__
#define _check_file_path_h__




#include <stdio.h>
#include <string>
using namespace std;

//若bAddSpec 为真，则确保szDst路径末尾带有"\", 若bAddSpec为假，则去除lpszPath末尾的"\"或"/"  
void ModifyPathSpec( char  * szDst, bool  bAddSpec )  ;
string& replace_all_distinct(string& str,const string& old_value,const string& new_value);

bool get_parent_dir(string &strdir );
bool check_file_path(const char * lpszDir);


#endif