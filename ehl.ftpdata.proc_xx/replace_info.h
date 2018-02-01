#ifndef _replace_info_h__
#define _replace_info_h__
#include <string>
using namespace std;
inline string& replace_all_distinct(string& str,const string& old_value,const string& new_value) 
{ 
	for (string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) 
	{ 
		if( (pos=str.find(old_value,pos))!=string::npos ) 
			str.replace(pos,old_value.length(),new_value); 
		else break; 
	} 
	return str; 
} ;


inline char * replace_str (char  *source, char  *result,  char  *sub,  char  *rep) 
{ 
 
 /*pc1  是复制到结果result的扫描指针*/
 /*pc2  是扫描 source 的辅助指针*/
 /*pc3  寻找子串时,为检查变化中的source是否与子串相等,是指向sub的扫描指针 */
 /*找到匹配后,为了复制到结果串,是指向rep的扫描指针*/
 char  *pc1,  *pc2,  *pc3;     
 int  isource,  isub,  irep; 
 isub  = strlen(sub);   /*对比字符串的长度*/
 irep  = strlen(rep);   /*替换字符串的长度*/
 isource= strlen(source); /*源字符串的长度*/ 
 if(NULL == *sub)  
  return strdup(source); 
 /*申请结果串需要的空间*/
 //result  = (char *)malloc(( (irep > isub) ? (float)strlen(source) / isub* irep+ 1:isource ) * sizeof(char));
 pc1  =  result; /*为pc1依次复制结果串的每个字节作准备*/
 while(*source  !=  NULL) 
 { 
  /*为检查source与sub是否相等作准备,为pc2,pc3 赋初值*/
	 pc2  =  source;
	 pc3  =  sub;
  /* 出循环的（任一）条件是： 
      *  *pc2 不等于 *pc3 （与子串不相等） 
      *  pc2  到源串结尾 
      *  pc3  到源串结尾 （此时,检查了全部子串,source处与sub相等） 
      *****************************************************/
	 while(*pc2  ==  *pc3  &&  *pc3  !=  NULL  &&  *pc2  !=  NULL)
		 pc2++,  pc3++;// [Page]
	 /* 如果找到了子串,进行以下处理工作*/
	 if(NULL  ==  *pc3)
	 {
		 pc3=rep;
		 /*将替代串追加到结果串*/
		 while(*pc3!=NULL)
			 *pc1++=*pc3++;
		 pc2--;
		 source=pc2;
		 /*   检查 source与sub相等的循环结束后， 
        * pc2 对应的位置是在 sub 中串结束符处。该是源串中下一个位置。 
        * 将 source 指向其前面一个字符。 
        ***************************************************/
	 }
	 else	/*如果没找到子串,下面复制source所指的字节到结果串*/
		 *pc1++ = *source;
	 source++; /* 将source向后移一个字符*/
 }
 *pc1 = NULL;
 return result;
};

#endif // _replace_info_h__