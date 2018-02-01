#ifndef TMRIAGENT_H
#define TMRIAGENT_H

class TmriAgent {
public:
    TmriAgent();

    long InitTrans(const char *kkbh,const char *fxlx,long cdh,const char *info,const char *hostport);
    
    long WriteVehicleInfo(const char *kkbh,const char *fxlx,long cdh,const char *hphm,const char *hpzl,const char *gcsj,long clsd,long clxs,const char *wfdm,long cwkc,const char *hpys,const char *cllx,const char *fzhpzl,const char *fzhphm,const char *fzhpys,const char *clpp,const char *clwx,const char *csys,const char *tplj,const char *tp1,const char *tp2,const char *tp3,const char *tztp);
    
    long SaveTzPicture(const char *kkbh,const char *fxlx,long cdh,const char *hphm,const char *gcsj,const char *file);
    
    long SaveTzPicStream(const char * kkbh,const char *fxlx,long cdh,const char *hphm,const char *gcsj,const void * pbuf,long size);
    
    long SavePicture(const char *kkbh,const char *fxlx,long cdh,const char *hphm,const char *gcsj,long tpxh,const char *file);

    long SavePicStream(const char * kkbh,const char *fxlx,long cdh,const char *hphm,const char *gcsj,long tpxh,const void * pbuf,long size);

    long QueryLimitSpeed(const char *kkbh,const char *fxlx,long cdh,const char *cllx);
    
    const char *QuerySyncTime();
    
    const char *GetLastMessage();
    
    const char * m_hostport;
    
    void * m_pagentSocket;
};

#endif // TMRIAGENT_H
