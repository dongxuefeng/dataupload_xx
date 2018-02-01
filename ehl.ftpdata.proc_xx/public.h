#ifndef _public_h__
#define _public_h__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <process.h>
#include <windows.h>
#include <io.h>

#define max_find_count	50

using namespace std;




#define _ftp_config_file		"./config/proc_config.ini"

//ftp 操作基本类
//#include "..\..\..\lib_src\lib\libftp\lib_ftpget.h"
#include "xxlib\libini\ini_oper.h"
#include "check_file_path.h"

class _local_dir
{
public:
	string m_datafile;
	string m_backdir;
	string m_faildir;
	_local_dir()
	{
		m_datafile = get_ini_str_ex("local_dir","datafile","d:/datafile",_ftp_config_file);
		m_backdir = get_ini_str_ex("local_dir", "back_dir", "d:/datafile_bak", _ftp_config_file);
		m_faildir = get_ini_str_ex("local_dir", "fail_dir", "d:/datafile_fail", _ftp_config_file);
		/*
		put_ini_str("local_dir","datafile",m_datafile.c_str(),_ftp_config_file);
		put_ini_str("local_dir", "back_dir", m_backdir.c_str(), _ftp_config_file);
		put_ini_str("local_dir", "fail_dir", m_faildir.c_str(), _ftp_config_file);
		*/
	};
} ;


extern _local_dir g_local_dir;

#endif