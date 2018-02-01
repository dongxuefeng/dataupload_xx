#ifndef _ini_oper_h__
#define _ini_oper_h__


#ifdef INI_OPER_EXPORTS
#define INI_OPER_API __declspec(dllexport)
#else
#define INI_OPER_API __declspec(dllimport)
#endif

extern "C"
{
INI_OPER_API unsigned long get_ini_section_names( char * sreturn_buff,const long nsize,const char * sfilename);
INI_OPER_API unsigned long get_ini_int(const char * section_name,const char * key_name,const long ndefault_value,const char * sfilename);
INI_OPER_API void put_ini_int(const char * section_name,const char * key_name,const long n_value,const char * sfilename);
INI_OPER_API unsigned long get_ini_str(const char * section_name,const char * key_name,const char * ndefault_value,char * nreturn_value,const long nsize,const char * sfilename);
INI_OPER_API const char * get_ini_str_ex(const char * section_name,const char * key_name,const char * ndefault_value,const char * sfilename);
INI_OPER_API void put_ini_str(const char * section_name,const char * key_name,const char * s_value,const char * sfilename);
}

#endif
