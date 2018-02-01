#ifndef _process_xxdatatostd__h__
#define _process_xxdatatostd__h__


bool getPassCarXmlInfo(const char * xml, string &filename, string &vdata, int &imgcoung, string &img1, string &img2, string &img3);
const char * get_default_cllx(const char * hpys);
bool get_datetime(const char * str, string &datetime);
bool getVioXmlInfo(const char * xml, string &filename, string &vdata, int &imgcoung, string &img1, string &img2, string &img3);

#endif