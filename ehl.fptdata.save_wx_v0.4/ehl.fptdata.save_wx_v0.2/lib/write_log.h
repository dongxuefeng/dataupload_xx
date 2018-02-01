#ifndef __write_log_h__
#define __write_log_h__

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "c_time.h"
#include "check_file_path.h"

inline bool WriteLog(char *strInfo,char * logdir = "./log/",char * file_mark="LogSaveData",char * log_mark="Log")
{
	printf("\n");
	printf(strInfo);
	//写日志文件
	char spath[260];
	char fName[260];			//文件名
	char str[260];

	c_time mtime;
	mtime.get_local_time();
	sprintf(str,"\n%s[%s] msg:\n",mtime.get_datetime(),log_mark);
	sprintf(spath,"%s/%s/",logdir,mtime.get_date());
	check_file_path(spath);
	sprintf(fName,"%s/%s%002d.log", spath,file_mark,mtime.get_hour());

	int fh2 = _open( fName, _O_WRONLY | _O_CREAT | _O_TEXT | _O_APPEND , _S_IWRITE ); // C4996
	if( fh2 != -1 )
	{
		_write(fh2,str,strlen(str));
		_write(fh2,strInfo,strlen(strInfo));
		_write(fh2,"\r\n",2);
		_close( fh2 );
		return true;
	}
		
	else
	{
		return false;
	};
};

inline bool clear_log(int iday = 10,char * logdir = "./log/")
{
	return free_disk(logdir,iday);
};

#endif