#include "stdio.h"
#include "windows.h"
#include "oper_iniopen.h"

//config 


unsigned long get_ini_section_names(char * sreturn_buff,const long nsize,const char * sfilename)
{
	return GetPrivateProfileSectionNames(sreturn_buff,nsize,sfilename);
};

unsigned long get_ini_int(const char * section_name,const char * key_name,const long ndefault_value,const char * sfilename)
{
	return GetPrivateProfileInt(section_name,key_name,ndefault_value,sfilename);
};

void put_ini_int(const char * section_name,const char * key_name,const long n_value,const char * sfilename)
{
	char str[256];
	sprintf(str,"%d",n_value);
	put_ini_str(section_name,key_name,str,sfilename);
};

unsigned long get_ini_str(const char * section_name,const char * key_name,const char * ndefault_value,char * nreturn_value,long nsize,const char * sfilename)
{
	return GetPrivateProfileString(section_name,key_name,ndefault_value,nreturn_value,nsize,sfilename);
};

void put_ini_str(const char * section_name,const char * key_name,const char * s_value,const char * sfilename)
{
	WritePrivateProfileString(section_name,key_name,s_value,sfilename);
};

const char * get_ini_str(const char * section_name,const char * key_name,const char * ndefault_value,const char * sfilename)
{
	static char strtmp[256];
	get_ini_str(section_name,key_name,ndefault_value,strtmp,256,sfilename);
	return strtmp;
};





