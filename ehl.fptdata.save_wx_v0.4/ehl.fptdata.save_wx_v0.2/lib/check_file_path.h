
#ifndef _check_file_path_h__
#define _check_file_path_h__

#include "replace_info.h"
#include "iostream"
#include <shlwapi.h>
#include <winbase.h>
//shlwapi.lib
using namespace std;


//若bAddSpec 为真，则确保szDst路径末尾带有"\", 若bAddSpec为假，则去除lpszPath末尾的"\"或"/"  

inline void ModifyPathSpec( TCHAR * szDst, BOOL  bAddSpec )  
{  
    int nLen = lstrlen(szDst);  

    TCHAR  ch  = szDst[ nLen - 1 ];  
    if( ( ch == ('\\') ) || ( ch == ('/') ) )  
    {  
        if(!bAddSpec )  
        {  
            szDst[ nLen - 1 ] = ('\0');  
        }
    }
    else  
    {
        if( bAddSpec )  
        {
            szDst[ nLen ] = ('\\');  
            szDst[ nLen + 1 ] = ('\0');  
        }
    }
};


inline bool get_parent_dir(string &strdir )
 {
	 //strdir.replace(strdir.begin(),strdir.end(),'\\','/');
	  replace_all_distinct(strdir,"\\","/") ;
	 int itmp = strdir.rfind('/');
	
	 strdir.at(itmp) = '\0';
	 return true;

 }

inline bool get_parent_dir1(string &strdir)
{
	//strdir.replace(strdir.begin(),strdir.end(),'\\','/');
	replace_all_distinct(strdir, "\\", "/");
	int itmp = strdir.rfind('/');

	strdir.at(itmp) = '\0';
	return true;

}

inline bool get_parent_dir(const char * strdir,  char * pardir)
{
	string strtmp = strdir;
	bool bresult = get_parent_dir1(strtmp);
	sprintf(pardir, strtmp.c_str());
	return bresult;
};

inline bool check_file_path(char * lpszDir)
{
	//验证文件目录是否存在
    if( ::PathIsDirectory( lpszDir ) ) return TRUE;  
  
    TCHAR   szPreDir[ MAX_PATH ];  
    sprintf( szPreDir, lpszDir );  
    //确保路径末尾没有反斜杠  
    ModifyPathSpec( szPreDir, FALSE );  
  
    //获取上级目录  
   // BOOL  bGetPreDir  = ::PathRemoveFileSpec( szPreDir );  

	string strtmp = szPreDir;
	BOOL  bGetPreDir = get_parent_dir(strtmp);
    if( !bGetPreDir ) return FALSE;  
  
    //如果上级目录不存在,则递归创建上级目录  
    if( !::PathIsDirectory( strtmp.c_str() ) )  
    {  
        check_file_path( (char *)strtmp.c_str());  
    }  
    return ::CreateDirectory( lpszDir, NULL );  
};

#include <direct.h>

#include <io.h>

inline bool DeleteDirectory(char* sDirName)  
{  
	//CFileFind tempFind;  
	char sTempFileFind[256] ; 
	sprintf(sTempFileFind,"%s/*.*",sDirName); 
	struct _finddata_t c_file;
	long hFile;

   // Find first .c file in current directory 
   if( (hFile = _findfirst( sTempFileFind, &c_file )) == -1L )
      printf( "No *.* files in current directory!\n" );
   else
   {

	   do {
		   char sFoundFileName[260];  
			//strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(256)); 
		   strcpy(sFoundFileName,c_file.name); 
		   if (c_file.attrib & _A_SUBDIR  )
		   {
				//目录
			    if((strcmp(sFoundFileName,".")&&strcmp(sFoundFileName,"..")))
				{
					char sf[256];
					sprintf(sf,"%s/%s",sDirName,sFoundFileName);
					DeleteDirectory(sf);
				}
		   }
		   else
		   {
			   //文件
			   		char sf[256];
					sprintf(sf,"%s/%s",sDirName,sFoundFileName);
					cout << "delete file succ:" << sf << endl;
					remove(sf);
		   }

	   } while( _findnext( hFile, &c_file ) == 0 );
	   _findclose( hFile );
	   rmdir(sDirName);
	   cout << "delete dir succ:" << sDirName << endl;
   };
	return true;
} 

#include "c_time.h"
inline bool free_disk(char * datapath,int daycount)
{
	c_time mtime;
	mtime.get_local_time();
	mtime.addday(-daycount);

	char deletefilepath[200];
	sprintf(deletefilepath, "%s",mtime.get_date());

	cout << "删除"<<deletefilepath<<"前的数据"<<endl;

	//查找当前目录下的子目录
	char sTempFileFind[256] ; 
	sprintf(sTempFileFind,"%s/*.*",datapath); 
	struct _finddata_t c_file;
	long hFile;
	 // Find first .c file in current directory 
	if( (hFile = _findfirst( sTempFileFind, &c_file )) == -1L )
	{
      printf( "No *.* files in current directory!\n" );
	}
	else
	{

	   do {
		   char sFoundFileName[260];  
			//strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(256)); 
		   strcpy(sFoundFileName,c_file.name); 
		   if (c_file.attrib & _A_SUBDIR  )
		   {
			    if((strcmp(sFoundFileName,".")&&strcmp(sFoundFileName,"..")))
				{
				
					if(strcmp(deletefilepath,sFoundFileName)>=0)
					{
						//时间早
						char dd[256];
						sprintf(dd,"%s/%s",datapath,sFoundFileName);
						cout << "正在删除目录:"<< dd <<endl;
						DeleteDirectory(dd);
					}
				}
		   }


	   } while( _findnext( hFile, &c_file ) == 0 );
	}
	//
	   _findclose( hFile );
	return true;
}

#endif