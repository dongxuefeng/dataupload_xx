
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "user_plug_prcdata.h"



typedef void (__stdcall* _plug_proc_data)(int itype, const char * datastr, int * irescode, char  * proc_msg,int imgcount,char * img1,char * img2,char * img3);
typedef void (__stdcall* _init_work_mode)(int workmode /*= 0*/, const char * webserviceurl /*= "http://localhost/Ehl.Atms.Tgs.WebService/OpenInterface.asmx"*/);


//HINSTANCE  hdll = NULL;							
//_plug_proc_data  pplug_proc_data = NULL;		
//_init_work_mode pinit_work_mode = NULL;			

#include "../libini/ini_oper.h";
#include <string>
using namespace std;
#include "../../public.h"
#include "../../write_log.h"
//ehl.ftpdata.save.dll
//构造函数传入库名，动态加载.传入配置文件名
class c_plug_proc_data
{
public:
	HINSTANCE  hdll;
	_plug_proc_data  pplug_proc_data;
	_init_work_mode pinit_work_mode;
public:
	//dllname   不解释
	//inifile   不解释
	//fun       执行函数指针
	//wmode     工作模式
	//hdll      加载库句柄
	c_plug_proc_data(char * dllname, char * inifile)
	{
		pplug_proc_data = NULL;
		hdll = NULL;
		pinit_work_mode = NULL;
		hdll = LoadLibrary(dllname);
		if (hdll == NULL)
		{
			printf("load %s error", dllname);
			getchar();
			FreeLibrary(hdll);
		}
		else
		{
			pplug_proc_data = (_plug_proc_data)GetProcAddress(hdll, "plug_proc_data");
		
			if (pplug_proc_data == NULL)
			{
				if (hdll != NULL)
					FreeLibrary(hdll);
			}
			pinit_work_mode = (_init_work_mode)GetProcAddress(hdll, "init_work_mode");
			if (pinit_work_mode != NULL)
			{
				int iworkmode = get_ini_int("upload_param", "work_mode", 0, inifile);
				string str = get_ini_str_ex("upload_param", "datawebservice", "http://localhost/Ehl.Atms.Tgs.WebService/OpenInterface.asmx", inifile);
				pinit_work_mode(iworkmode, str.c_str());
				put_ini_int("upload_param", "work_mode", iworkmode, inifile);
				put_ini_str("upload_param", "datawebservice", str.c_str(), inifile);
			}
		}
	}
	~c_plug_proc_data()
	{
		pplug_proc_data = NULL;
		if (hdll != NULL)
		   FreeLibrary(hdll);
		hdll = NULL;

	}


} ;
c_plug_proc_data * p_plug_proc_data = NULL;
int UnicodeToANSI(const wchar_t * strw,char * stra)
{
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		strw,
		-1,
		NULL,
		0,
		NULL,
		NULL);
	::WideCharToMultiByte(CP_ACP,
		0,
		strw,
		-1,
		stra,
		iTextLen,
		NULL,
		NULL);
	return iTextLen;
};

int ANSIToUnicode(const char * stra,wchar_t * strw)
{
	int  len = 0;
	len =strlen(stra);
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		stra,
		-1,
		NULL,
		0);
	
	::MultiByteToWideChar(CP_ACP,
		0,
		stra,
		-1,
		(LPWSTR)strw,
		unicodeLen);
	return  unicodeLen;
}




c_plug_proc_data g_plug_proc_data("ehl.ftpdata.ehlsave.dll", "./config/proc_config.ini");		//ehl库

c_plug_proc_data g_plug_proc_wxsdata("ehl.wxsdata.save.dll", "./config/wxs_config.ini");		//wxs库

void  plug_proc_data(const char * datastr, int * iresult_code, char * proc_msg, int imgcount, char * img1, char * img2, char * img3)
{
	char  datastra[1024];
	char  proc_msga[2048];
	char  proc_msgwxs[1024];
	int res = 0;
	//UnicodeToANSI(datastr, datastra);
	//sprintf(proc_msga, datastra);
	//ANSIToUnicode(proc_msga, proc_msg);
	sprintf(datastra, datastr);
	//gmux.lock();

	bool bresult = false;
	if (g_plug_proc_data.pplug_proc_data != NULL && g_plug_proc_wxsdata.pplug_proc_data != NULL)
	{
		
			g_plug_proc_data.pplug_proc_data(0, datastra, iresult_code, proc_msga, imgcount, img1, img2, img3);
		

		//ANSIToUnicode(proc_msga, proc_msg);
		WriteLog((char *)datastr);
		char con[24] = {0};
		sprintf(con, "%d", imgcount);

		g_plug_proc_wxsdata.pplug_proc_data(0, datastr, &res, proc_msgwxs, imgcount, img1, img2, img3);
		sprintf(proc_msg,proc_msga);
//		sprintf(proc_msg, proc_msgwxs);

	}
	else
	{
		if (g_plug_proc_data.hdll != NULL && g_plug_proc_wxsdata.hdll != NULL)
			//wsprintf(proc_msg, _T("load proc func is fail."));
			sprintf(proc_msg, "load proc func is fail.");
		else
			//wsprintf(proc_msg, _T("load dll is fail."));
			sprintf(proc_msg, "load dll is fail.");

	}
	//

	//gmux.unlock();

};