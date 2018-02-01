#ifndef _ehl_wx_webref_h__
#define _ehl_wx_webref_h__

#include <string>
extern char soap_endpointwx[256];



//int wx_upload_data_inpasscar(struct _ns1__WriteVehicleInfo InPassCarInfo, struct _ns1__WriteVehicleInfoResponse InPassCarInfoResponse);


//int wx_upload_data_inpasscar(const char * xml, char * refxml);
int call_wx_upload_data_inpasscar(std::string kkbh, std::string fxlx, long  cdh,  std::string hphm, std::string hpzl
			, std::string gcsj, long  clsd, long  clxs, std::string wfdm, long  cwkc, std::string hpys, std::string cllx
			, std::string fzhpzl, std::string fzhphm, std::string fzhpys, std::string clpp, std::string clwx, std::string csys
			, std::string tplj, std::string tp1, std::string tp2, std::string tp3, std::string tztp);
int call_wx_upload_data_inittrans(std::string kkbh, std::string fxlx, long cdh, std::string info,std::string hostip);

#endif