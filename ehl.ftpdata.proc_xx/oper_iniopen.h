#ifndef _oper_iniopen_h__
#define _oper_iniopen_h__

unsigned long get_ini_section_names( char * sreturn_buff,const long nsize,const char * sfilename);
unsigned long get_ini_int(const char * section_name,const char * key_name,const long ndefault_value,const char * sfilename);
void put_ini_int(const char * section_name,const char * key_name,const long n_value,const char * sfilename);
unsigned long get_ini_str(const char * section_name,const char * key_name,const char * ndefault_value,char * nreturn_value,const long nsize,const char * sfilename);
const char * get_ini_str(const char * section_name,const char * key_name,const char * ndefault_value,const char * sfilename);
void put_ini_str(const char * section_name,const char * key_name,const char * s_value,const char * sfilename);

#endif




