#ifndef _ehl_webref_h__
#define _ehl_webref_h__

extern char soap_endpoint[256];
int upload_data_inpasscar(const char * xml, char * refxml);
int upload_data_inviocar(const char * xml, char * refxml);

#endif

