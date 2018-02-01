#ifndef _ehl_ftpdata_save_h__
#define _ehl_ftpdata_save_h__

#define __data_save_api extern "C" __declspec(dllexport)

__data_save_api  void  __stdcall init_work_mode(int workmode /*= 0*/,const char * webserviceurl /*= "http://localhost/Ehl.Atms.Tgs.WebService/OpenInterface.asmx"*/);
__data_save_api  void  __stdcall plug_proc_data(int itype, const char * datastr, int * irescode, char * proc_msg,int imgcount,char * img1,char * img2,char *img3);

#endif  //#ifndef _ehl_ftpdata_save_h__