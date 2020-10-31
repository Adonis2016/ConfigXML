/////////////////////////////�����ļ�˵��//////////////////////////////////////
//[#01-00] �ļ����ƣ�ConfigXML.h
//[#01-01] �ļ�˵��������֧��XML��ʽ�������ļ�
//[#01-02] �������ڣ�2006.02.03
//[#01-03] �޸����ڣ�2015.08.10
//[#01-04] �����������Ը� MRZG
//[#01-05] ���ߵ�λ��
//[#01-06] ��ǰ�汾��v3.2
//[#01-07] ��ʷ�汾��v1.0, v1.1, v1.2, v2.0, v2.1, v2.2, v2.3, v2.4, v2.5, v3.0, v3.1
//[#01-08] ����������
//[#01-09] �ļ��ߴ磺
//[#01-10] ����˵�����ṩ����INI�÷���API
//[#01-11] �ı�LOGO��-=MYLOGO=-
//[#01-12] ��Ȩ������
//[#01-!!] ˵������
///////////////////////////////////////////////////////////////////////////////
/**
 * @file ConfigXML.h
 * @brief ����֧��XML��ʽ�������ļ�
 * @date 2015.08.10
 * @author �Ը� MRZG
 * @version v3.2
*/
#pragma once
#ifndef _CONFIGXML_H_2006_02_03_13_14_45_R19073_
#define _CONFIGXML_H_2006_02_03_13_14_45_R19073_

#pragma warning( disable : 4018 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4305 )

///////////////////////////////�ļ�����////////////////////////////////////////
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <io.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <direct.h>
#include <vector>

///ʹ��C++��׼��
using namespace std;

////////////////////////////////�궨��/////////////////////////////////////////
#ifndef MAX_PATH
#define MAX_PATH  260
#endif
#define CONFIGXML_FORMAT    1
#define CONFIGXML_VERSION   320
#define CONFIGXML_MAX_ELEM  512
#define CONFIGXML_MAX_VALUE 1024
#define CONFIGXML_ROOT "__ConfigXML__"

#ifdef CONFIGXML_EXPORTS
#define _EXPORT_ENGINE __declspec(dllexport)
#else
#define _EXPORT_ENGINE __declspec(dllimport)
#endif
///////////////////////////////////////////////////////////////////////////////
//------------------------------��˵��-----------------------------------------
//[#02-00] �������ƣ�
//[#02-01] ���๦�ܣ�
//[#02-02] �ڴ����ģ�
//[#02-03] �������ڣ�
//[#02-04] �޸����ڣ�
//[#02-05] ����˵����
//[#02-!!] ˵������
//-----------------------------------------------------------------------------
//------------------------------�����-----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�
//[#03-01] �������ܣ�
//[#03-02] ����˵����
//[#03-03] ����˵����
//[#03-04] �������ڣ�
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief @n
 *
 *  @b ˵��: @n@n
 *  @b ע��: @n
 *
 *  @param
 *  @param
 *  @return
 *  @see
 *
 *  @b ʵ��:
    @code
    @endcode
*/
//-----------------------------��������----------------------------------------

//-----------------------------�ṹ˵��----------------------------------------
//[#04-00] �ṹ���ƣ�
//[#04-01] �ṹ���ܣ�
//[#04-02] �ڴ����ģ�
//[#04-03] �������ڣ�
//[#04-04] �޸����ڣ�
//[#04-05] ����˵����
//[#04-!!] ˵������
//-----------------------------------------------------------------------------
//-----------------------------�ṹ����----------------------------------------
class ConfigXML;
///////////////////////////////��������////////////////////////////////////////

/////////////////////////////�ڲ�������ʼ//////////////////////////////////////
inline int ConfigXML_AnsiToUnicode(const char* ansi, wchar_t* unicode, int size)
{
	setlocale(LC_ALL,"");
	return (int)mbstowcs(unicode,ansi,size);
}
inline int ConfigXML_UnicodeToAnsi(const wchar_t* unicode, char* ansi, int size)
{
	setlocale(LC_ALL,"");
	return (int)wcstombs(ansi,unicode,size);
}
const char ConfigXML_fast_ftoa_table[]={'0','1','2','3','4','5','6','7','8','9'};
inline void ConfigXML_fast_ftoa(char* a, float f, int n)
{
	if(n>6) n=6;
	if(n<0) n=0;

	bool neg=false;
	if(f<0.0f)
	{
		f*=-1.0f;
		neg=true;
	}

    int i,j=0,s=0,k=0,m=1,sm=1;
	for(i=0; i<n; i++)
	{
		if(n>0&&i==n-1)
			sm=m;
		m*=10;
	}

	unsigned __int64 x=(unsigned __int64)(f*m);

	if(x==0)
	{
        a[0]='0';
		a[1]=0;
		return;
	}

	bool add=false;
	if(n>0&&x<sm)
	{
	   x+=sm;
	   add=true;
	}

	int b[32];
	while(x>0)
	{
       b[s]=(int)(x%10);
	   x/=10;
	   s++;
	}
	s--;

	for(i=0; i<n; i++)
	if(b[i]>0) break;

	k=i;

	if(neg)
	{
        a[0]='-';
		j=1;
	}

	for(i=s; i>=k; i--)
	{
		if(n>0&&k<n&&i==n-1)
		{
			a[j]='.';
			j++;
		}
		if(add&&i==s)
			a[j]='0';
		else a[j]=ConfigXML_fast_ftoa_table[b[i]];
		j++;
	}
	a[j]=0;
}
const float ConfigXML_fast_atof_table[] =
{
	0.f,
	0.1f,
	0.01f,
	0.001f,
	0.0001f,
	0.00001f,
	0.000001f,
	0.0000001f,
	0.00000001f,
	0.000000001f,
	0.0000000001f,
	0.00000000001f,
	0.000000000001f,
	0.0000000000001f,
	0.00000000000001f,
	0.000000000000001f
};
inline unsigned int ConfigXML_strtol10(const char* in, const char** out=0)
{
	unsigned int value=0;

	while(1)
	{
		if(*in<'0'||*in>'9')
			break;

		value=(value*10)+(*in-'0');
		++in;
	}
	if(out)	*out=in;
	return value;
}
//! Provides a fast function for converting a string into a float,
//! about 6 times faster than atof in win32.
// If you find any bugs, please send them to me, niko (at) irrlicht3d.org.
inline const char* ConfigXML_fast_atof_move(const char* c, float& out)
{
	bool inv=false;
	const char *t;
	float f;

	if(*c=='-')
	{
		++c;
		inv=true;
	}

	f=(float)ConfigXML_strtol10(c,&c);

	if(*c=='.')
	{
		++c;

		float pl=(float)ConfigXML_strtol10(c,&t);
		pl*=ConfigXML_fast_atof_table[t-c];

		f+=pl;
		c=t;

		if(*c=='e')
		{
			++c;
			bool einv=(*c=='-');
			if(einv) ++c;

			float exp=(float)ConfigXML_strtol10(c,&c);
			if(einv) exp*=-1.0f;

			f*=(float)pow(10.0f,exp);
		}
	}

	if(inv) f*=-1.0f;

	out=f;
	return c;
}
inline float ConfigXML_fast_atof(const char* c)
{
	float ret;
	ConfigXML_fast_atof_move(c,ret);
	return ret;
}
inline bool ConfigXML_isFloatEqual(const float* f, int n, int precision)
{
	for(int i=1; i<n; i++)
	if(fabs(f[0]-f[i])>=ConfigXML_fast_atof_table[precision])
		return false;

	return true;
}
inline bool ConfigXML_isPathExist(const char* path)
{
	if(!path) return false;

    long hf;
	_finddata_t fd;

    hf=_findfirst(path,&fd);
    if(hf==-1) return false;

    if(fd.attrib&_A_SUBDIR)
    {
        _findclose(hf);
        return true;
    }

    for(;;)
    {
        if(_findnext(hf,&fd))
        {
            _findclose(hf);
            return false;
        }
        if(fd.attrib&_A_SUBDIR)
        {
            _findclose(hf);
            return true;
        }
    }

    return false;
}
inline void ConfigXML_createPath(const char* path)
{
	if(!path) return;

	int i,len=strlen(path);
	if(len==0||len>=MAX_PATH) return;

	char dir[MAX_PATH];
	strcpy(dir,path);

    for(i=0; i<len; i++)
	if(dir[i]=='/') dir[i]='\\';

	char *p=strrchr(dir,'\\');
	if(p)
	{
		*p=0;
		if(strlen(dir)<2) return;

		if(!ConfigXML_isPathExist(dir))
		{
			ConfigXML_createPath(dir);
#ifdef _WIN32
		_mkdir(dir);
#else
		_mkdir(dir,0744);
#endif
		}
	}
}
/////////////////////////////�ڲ���������//////////////////////////////////////

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�SearchElemInXML
//[#03-01] �������ܣ�����ָ����ǩ
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//[#03-03] ����˵����void* �����������
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������element�����ڣ�����NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ�����������ָ����ǩ@n
 *
 *  @b ˵��: ��ָ����XML�ļ�����������ָ���ı�ǩ��element������ǩ�ı�ʾ�þ���@n
 *  ·����ʽ�����Ӹ���ǩ��ʼһֱ��Ŀ�ı�ǩ���м���"\"��"/"���ָ��ǩ��������@n
 *  ��ĸ��ͷ���м���Ի�����ֺ���ĸ������ʹ�����ı�ǩ��������:@n
 *  element="��ͼ/·��/����"�����ʾһ��������Ϊ3��ı�ǩ����ǩ����Ϊ:"����"@n
 *  һ������ǩΪ:"·��"����������ǩΪ:"��ͼ"������ǩ����@n
 *  SearchElemInXML��������ȷ��ָ����XML�ļ����Ƿ����ָ���ı�ǩ����������򷵻�@n
 *  �ñ�ǩ�����û����ԶԸñ�ǩ�����һ�����������򷵻�NULL��ʾָ����ǩ��ָ��@n
 *  XML�ļ��в����ڡ�@n@n
 *  @b ע��: XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @return TiXmlElement* ��ǩ�����NULL
 *  @see splitElement
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    TiXmlElement* element=(TiXmlElement*)SearchElemInXML(xml,"��ͼ/·��/����");
    if(!element)
        MessageBox(NULL,"ָ����ǩ�����ڣ�","����",MB_OK);
    else
    {
        ��element������в���...
    }
    @endcode
*/
_EXPORT_ENGINE void* SearchElemInXML(ConfigXML& xml, void* root, void* element);
_EXPORT_ENGINE void* SearchElemInXML(ConfigXML& xml, void* root, const char* element);
_EXPORT_ENGINE void* SearchElemInXML(ConfigXML& xml, void* root, const wchar_t* element);
_EXPORT_ENGINE void* SearchElemInXMLByAttr(ConfigXML& xml, void* root, const char* attribute, const char* content);
_EXPORT_ENGINE void* SearchElemInXMLByAttr(ConfigXML& xml, void* root, const wchar_t* attribute, const wchar_t* content);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�SearchAttrInXML
//[#03-01] �������ܣ�����ָ����ǩ��ָ������
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//[#03-03] ����˵����void* �����������
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������attribute�����ڣ�����NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ĵ�����������ָ����ǩ��ָ������@n
 *
 *  @b ˵��: ��ָ����XML�ļ�����������ָ���ı�ǩ��element����ָ�����ԣ�attribute��@n
 *  ��ǩ�ı�ʾ�þ���·����ʽ�����Ӹ���ǩ��ʼһֱ��Ŀ�ı�ǩ���м���"\"��"/"���ָ@n
 *  ��ǩ����������ĸ��ͷ���м���Ի�����ֺ���ĸ������ʹ�����ı�ǩ��������:@n
 *  element="��ͼ/·��/����"�����ʾһ��������Ϊ3��ı�ǩ����ǩ����Ϊ:"����"@n
 *  һ������ǩΪ:"·��"����������ǩΪ:"��ͼ"������ǩ�����������ַ�����ʾ��@n
 *  SearchAttrInXML��������ȷ��ָ����XML�ļ����Ƿ����ָ���ı�ǩ��ָ���ı�ǩ���Ƿ�@n
 *  ����ָ�������ԣ���������򷵻ظ����Զ����û����ԶԸ����Զ����һ��������@n
 *  ���򷵻�NULL��ʾָ����ǩ��ָ��������ָ����XML�ļ��в����ڡ�@n@n
 *  @b ע��: XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @return TiXmlAttribute* ���Զ����NULL
 *  @see SearchElement
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    TiXmlAttribute* attribute=(TiXmlAttribute*)SearchAttrInXML(xml,"��ͼ/·��/����","����");
    if(!attribute)
        MessageBox(NULL,"ָ�����Բ����ڣ�","����",MB_OK);
    else
    {
        ��attribute������в���...
    }
    @endcode
*/
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, void* element, const char* attribute);
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, void* element, const wchar_t* attribute);
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, const char* element, const char* attribute);
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, const wchar_t* element, const wchar_t* attribute);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�RemoveElemFromXML
//[#03-01] �������ܣ���XML�ļ����Ƴ�ָ����ǩ
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//[#03-03] ����˵����bool �Ƴ��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ��������Ƴ�ָ����ǩ@n
 *
 *  @b ˵��: RemoveElemFromXML������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ���������ָ����XML�ļ��������Ƴ�������true��ʾ@n
 *     �Ƴ��ɹ�������ñ�ǩ�����ڣ������κβ�������false��ʾ��ǩ�����ڡ�@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *           3) ���Ƴ���ǩ�������ӱ�ǩҲ��ȫ���Ƴ���@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @return �Ƴ��ɹ�����true��ָ����ǩ�����ڷ���false
 *  @see SearchElement
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool removeok=RemoveElemFormXML(xml,"��ͼ/·��/����");
    if(removeok==true)
    {
        MessageBox(NULL,"ָ����ǩ�ɹ��Ƴ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ����ǩ�����ڣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool RemoveElemFromXML(ConfigXML& xml, void* root, void* element);
_EXPORT_ENGINE bool RemoveElemFromXML(ConfigXML& xml, void* root, const char* element);
_EXPORT_ENGINE bool RemoveElemFromXML(ConfigXML& xml, void* root, const wchar_t* element);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteElemToXML
//[#03-01] �������ܣ���ĳelementд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//[#03-03] ����˵����
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ���ı�ǩд��ָ����XML�ļ�������@n
 *
 *  @b ˵��: WriteElemToXML������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ���������κβ�������false��ʾ��ǩ�Ѿ����ڣ�����@n
 *     ��ָ����ǩд��ָ��XML�ļ������У�����ñ�ǩ�ĸ���ǩҲ��������ݹ���ñ�����@n
 *     ������Ӧ�ĸ���ǩ��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param bCheckRepeat=true �Ƿ����ظ���ǩ��������ظ���ǩ�п���д���ظ���ǩ��@n
 *                           �����û��Ѿ��ܹ�ȷ����ǩ���ظ���
 *  @return TiXmlElement* д��ɹ����ر�ǩָ�룬ʧ�ܷ���NULL��
 *  @see SearchElement
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    TiXmlElement* pEle=WriteElemToXML(xml,"��ͼ/·��/����");
    if(pEle)
    {
        MessageBox(NULL,"ָ����ǩд��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ����ǩ�Ѿ����ڣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE void* WriteElemToXML(ConfigXML& xml, void* root, const char* element, bool bCheckRepeat=true);
_EXPORT_ENGINE void* WriteElemToXML(ConfigXML& xml, void* root, const wchar_t* element, bool bCheckRepeat=true);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�RemoveAttrFromXML
//[#03-01] �������ܣ���XML�ļ����Ƴ�ĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//[#03-03] ����˵����bool �Ƴ��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ��������Ƴ�ָ����ǩ��ָ������@n
 *
 *  @b ˵��: RemoveAttrFromXML������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ��������ָ����XML�ļ��������Ƴ�������true��ʾ@n
 *     �Ƴ��ɹ�����������Բ����ڣ������κβ�������false��ʾ���Բ����ڡ�@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @return �Ƴ��ɹ�����true��ָ�����Բ����ڷ���false
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool removeok=RemoveAttrFormXML(xml,"��ͼ/·��/����","����");
    if(removeok==true)
    {
        MessageBox(NULL,"ָ�����Գɹ��Ƴ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ�����Բ����ڣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, void* element, const char* attribute);
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, void* element, const wchar_t* attribute);
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, const char* element, const char* attribute);
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, const wchar_t* element, const wchar_t* attribute);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_str
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   const char* value ����ֵ
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧���ַ�������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ�ַ�������@n
 *
 *  @b ˵��: WriteAttrToXML_str������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ���ַ������ͣ�
 *  @param defaul=NULL ȱʡֵ���ַ������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_str(xml,"��ͼ/·��/����","����","GIF");
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_str(ConfigXML& xml,
                                       const char* element,
                                       const char* attribute,
                                       const char* value,
					                   const char* defaul=NULL);
_EXPORT_ENGINE bool WriteAttrToXML_str(ConfigXML& xml,
									   const wchar_t* element,
									   const wchar_t* attribute,
									   const wchar_t* value,
									   const wchar_t* defaul=NULL);
_EXPORT_ENGINE bool WriteAttrToXML_str(ConfigXML& xml,
									   void* element,
									   const char* attribute,
									   const char* value,
									   const char* defaul=NULL);
_EXPORT_ENGINE bool WriteAttrToXML_str(ConfigXML& xml,
									   void* element,
									   const wchar_t* attribute,
									   const wchar_t* value,
									   const wchar_t* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_str_ref
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   const char* value ����ֵ
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧���ַ�������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ�ַ�������@n
 *
 *  @b ˵��: WriteAttrToXML_str������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ���ַ������ͣ�
 *  @param defaul=NULL ȱʡֵ���ַ������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_str(xml,"��ͼ/·��/����","����","GIF");
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_str_ref(ConfigXML& xml,
										   const char* element,
										   const char* attribute,
										   const char* value,
										   const char* defaul=NULL);
_EXPORT_ENGINE bool WriteAttrToXML_str_ref(ConfigXML& xml,
										   const wchar_t* element,
										   const wchar_t* attribute,
										   const wchar_t* value,
										   const wchar_t* defaul=NULL);
_EXPORT_ENGINE bool WriteAttrToXML_str_ref(ConfigXML& xml,
										   void* element,
										   const char* attribute,
										   const char* value,
										   const char* defaul=NULL);
_EXPORT_ENGINE bool WriteAttrToXML_str_ref(ConfigXML& xml,
										   void* element,
										   const wchar_t* attribute,
										   const wchar_t* value,
										   const wchar_t* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_int
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   int value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧����������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ��������@n
 *
 *  @b ˵��: WriteAttrToXML_int������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ���������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"��ͼ/·��/����","����",2);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_int(ConfigXML& xml,
									   const char* element,
									   const char* attribute,
									   int value);
_EXPORT_ENGINE bool WriteAttrToXML_int(ConfigXML& xml,
									   const wchar_t* element,
									   const wchar_t* attribute,
									   int value);
_EXPORT_ENGINE bool WriteAttrToXML_int(ConfigXML& xml,
									   void* element,
									   const char* attribute,
									   int value);
_EXPORT_ENGINE bool WriteAttrToXML_int(ConfigXML& xml,
									   void* element,
									   const wchar_t* attribute,
									   int value);
_EXPORT_ENGINE bool WriteAttrToXML_int_n(ConfigXML& xml,
									     const char* element,
										 const char* attribute,
										 const int* value,
										 int n);
_EXPORT_ENGINE bool WriteAttrToXML_int_n(ConfigXML& xml,
										 const wchar_t* element,
										 const wchar_t* attribute,
										 const int* value,
										 int n);
_EXPORT_ENGINE bool WriteAttrToXML_int_n(ConfigXML& xml,
										 void* element,
										 const char* attribute,
										 const int* value,
										 int n);
_EXPORT_ENGINE bool WriteAttrToXML_int_n(ConfigXML& xml,
										 void* element,
										 const wchar_t* attribute,
										 const int* value,
										 int n);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_hex
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   long value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧��ʮ����������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ����������@n
 *
 *  @b ˵��: WriteAttrToXML_hex������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ�����������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_hex(xml,"��ͼ/·��/����","����",2);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_hex(ConfigXML& xml,
									   const char* element,
									   const char* attribute,
									   int value);
_EXPORT_ENGINE bool WriteAttrToXML_hex(ConfigXML& xml,
									   const wchar_t* element,
									   const wchar_t* attribute,
									   int value);
_EXPORT_ENGINE bool WriteAttrToXML_hex(ConfigXML& xml,
									   void* element,
									   const char* attribute,
									   int value);
_EXPORT_ENGINE bool WriteAttrToXML_hex(ConfigXML& xml,
									   void* element,
									   const wchar_t* attribute,
									   int value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_int64
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   __int64 value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧�ֳ���������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ64λ��������@n
 *
 *  @b ˵��: WriteAttrToXML_int64������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ��64λ�������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int64(xml,"��ͼ/·��/����","����",2);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_int64(ConfigXML& xml,
									     const char* element,
									     const char* attribute,
									     __int64 value);
_EXPORT_ENGINE bool WriteAttrToXML_int64(ConfigXML& xml,
									     const wchar_t* element,
									     const wchar_t* attribute,
									     __int64 value);
_EXPORT_ENGINE bool WriteAttrToXML_int64(ConfigXML& xml,
									     void* element,
									     const char* attribute,
									     __int64 value);
_EXPORT_ENGINE bool WriteAttrToXML_int64(ConfigXML& xml,
									     void* element,
									     const wchar_t* attribute,
									     __int64 value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_bool
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   bool value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧�ֳ���������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ��������@n
 *
 *  @b ˵��: WriteAttrToXML_bool������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ���������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"��ͼ/·��/����","����",true);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_bool(ConfigXML& xml,
									    const char* element,
									    const char* attribute,
									    bool value);
_EXPORT_ENGINE bool WriteAttrToXML_bool(ConfigXML& xml,
										const wchar_t* element,
										const wchar_t* attribute,
										bool value);
_EXPORT_ENGINE bool WriteAttrToXML_bool(ConfigXML& xml,
										void* element,
										const char* attribute,
										bool value);
_EXPORT_ENGINE bool WriteAttrToXML_bool(ConfigXML& xml,
										void* element,
										const wchar_t* attribute,
										bool value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_float
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   float value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧�ֵ����ȸ�������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ�����ȸ�������@n
 *
 *  @b ˵��: WriteAttrToXML_float������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ�������ȸ������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"��ͼ/·��/����","�ߴ�",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_float(ConfigXML& xml,
									     const char* element,
									     const char* attribute,
									     float value);
_EXPORT_ENGINE bool WriteAttrToXML_float(ConfigXML& xml,
										 const wchar_t* element,
										 const wchar_t* attribute,
										 float value);
_EXPORT_ENGINE bool WriteAttrToXML_float(ConfigXML& xml,
										 void* element,
										 const char* attribute,
										 float value);
_EXPORT_ENGINE bool WriteAttrToXML_float(ConfigXML& xml,
										 void* element,
										 const wchar_t* attribute,
										 float value);
_EXPORT_ENGINE bool WriteAttrToXML_float_n(ConfigXML& xml,
										   const char* element,
										   const char* attribute,
										   const float* value,
										   int n);
_EXPORT_ENGINE bool WriteAttrToXML_float_n(ConfigXML& xml,
										   const wchar_t* element,
										   const wchar_t* attribute,
										   const float* value,
										   int n);
_EXPORT_ENGINE bool WriteAttrToXML_float_n(ConfigXML& xml,
										   void* element,
										   const char* attribute,
										   const float* value,
										   int n);
_EXPORT_ENGINE bool WriteAttrToXML_float_n(ConfigXML& xml,
										   void* element,
										   const wchar_t* attribute,
										   const float* value,
										   int n);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_double
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   double value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧��˫���ȸ�������
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: WriteAttrToXML_double������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ��˫���ȸ������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"��ͼ/·��/����","�ߴ�",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_double(ConfigXML& xml,
										  const char* element,
										  const char* attribute,
										  double value);
_EXPORT_ENGINE bool WriteAttrToXML_double(ConfigXML& xml,
										  const wchar_t* element,
										  const wchar_t* attribute,
										  double value);
_EXPORT_ENGINE bool WriteAttrToXML_double(ConfigXML& xml,
										  void* element,
										  const char* attribute,
										  double value);
_EXPORT_ENGINE bool WriteAttrToXML_double(ConfigXML& xml,
										  void* element,
										  const wchar_t* attribute,
										  double value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_uuid
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   unsigned int* value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧��uuid����4��32λ�޷�������ʾ
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: WriteAttrToXML_double������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ��32λ�޷��������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"��ͼ/·��/����","�ߴ�",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_uuid(ConfigXML& xml,
										const char* element,
										const char* attribute,
										const unsigned int* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid(ConfigXML& xml,
										const wchar_t* element,
										const wchar_t* attribute,
										const unsigned int* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid(ConfigXML& xml,
										void* element,
										const char* attribute,
										const unsigned int* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid(ConfigXML& xml,
										void* element,
										const wchar_t* attribute,
										const unsigned int* value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_uuid_ref
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   unsigned int* value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧��uuid����4��32λ�޷�������ʾ
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: WriteAttrToXML_double������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ��32λ�޷��������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"��ͼ/·��/����","�ߴ�",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
											const char* element,
											const char* attribute,
											const unsigned int* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
											const wchar_t* element,
											const wchar_t* attribute,
											const unsigned int* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
											void* element,
											const char* attribute,
											const unsigned int* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
											void* element,
											const wchar_t* attribute,
											const unsigned int* value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_uuid_str
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   unsigned int* value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧��uuid����4��32λ�޷�������ʾ
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: WriteAttrToXML_double������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ��32λ�޷��������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"��ͼ/·��/����","�ߴ�",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_uuid_str(ConfigXML& xml,
											const char* element,
											const char* attribute,
											const unsigned char* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid_str(ConfigXML& xml,
											const wchar_t* element,
											const wchar_t* attribute,
											const unsigned char* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid_str(ConfigXML& xml,
											void* element,
											const char* attribute,
											const unsigned char* value);
_EXPORT_ENGINE bool WriteAttrToXML_uuid_str(ConfigXML& xml,
											void* element,
											const wchar_t* attribute,
											const unsigned char* value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_color
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   int value ����ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����֧����ɫ���� 0xffffffff
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ��������д��ָ����XML�ļ������У�����ֵΪ��������@n
 *
 *  @b ˵��: WriteAttrToXML_color������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ������ָ������д�벢����true��ʾ�����Ѿ�д�룬����@n
 *     �ȵ���WriteElemToXML������Ӧ�ı�ǩ��Ȼ����д�����ԣ����������ǩʧ�ܷ���false��@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param value ����ֵ���������ͣ�
 *  @return д��ɹ�����true��д��ʧ�ܷ���false
 *  @see WriteElemToXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_color(xml,"��ͼ/·��/��ɫ","��ֵ",0x00ffffff);
    if(writeok==true)
    {
        MessageBox(NULL,"ָ������д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ������д��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool WriteAttrToXML_color(ConfigXML& xml,
										 const char* element,
										 const char* attribute,
										 unsigned int value);
_EXPORT_ENGINE bool WriteAttrToXML_color(ConfigXML& xml,
										 const wchar_t* element,
										 const wchar_t* attribute,
										 unsigned int value);
_EXPORT_ENGINE bool WriteAttrToXML_color(ConfigXML& xml,
										 void* element,
										 const char* attribute,
										 unsigned int value);
_EXPORT_ENGINE bool WriteAttrToXML_color(ConfigXML& xml,
										 void* element,
										 const wchar_t* attribute,
										 unsigned int value);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_str
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����const char* ��������Ϣ���ַ������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ�ַ�������@n
 *
 *  @b ˵��: ReadAttrFromXML_str������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ��ַ���ָ�룩�����򷵻�NULL@n@n
 *  @b ע��: XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return const char* ��������Ϣ���ַ������ͣ�
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    const char* str=ReadAttrFromeXML_str(xml,"��ͼ/·��/����","����","PNG");
    if(str)
    {
        MessageBox(NULL,str,"�������Ե�����",MB_OK);
    }
    else
    {
        MessageBox(NULL,"ָ�������Բ�����","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE const char* ReadAttrFromXML_str(ConfigXML& xml,
											   const char* element,
											   const char* attribute,
											   const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadAttrFromXML_str(ConfigXML& xml,
												  const wchar_t* element,
												  const wchar_t* attribute,
												  const wchar_t* defaul=NULL);
_EXPORT_ENGINE const char* ReadAttrFromXML_str(ConfigXML& xml,
											   void* element,
											   const char* attribute,
											   const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadAttrFromXML_str(ConfigXML& xml,
											      void* element,
											      const wchar_t* attribute,
											      const wchar_t* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_str_ref
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����const char* ��������Ϣ���ַ������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ�ַ�������@n
 *
 *  @b ˵��: ReadAttrFromXML_str������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ��ַ���ָ�룩�����򷵻�NULL@n@n
 *  @b ע��: XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return const char* ��������Ϣ���ַ������ͣ�
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    const char* str=ReadAttrFromeXML_str(xml,"��ͼ/·��/����","����","PNG");
    if(str)
    {
        MessageBox(NULL,str,"�������Ե�����",MB_OK);
    }
    else
    {
        MessageBox(NULL,"ָ�������Բ�����","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE const char* ReadAttrFromXML_str_ref(ConfigXML& xml,
												   const char* element,
												   const char* attribute,
												   const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadAttrFromXML_str_ref(ConfigXML& xml,
													  const wchar_t* element,
													  const wchar_t* attribute,
													  const wchar_t* defaul=NULL);
_EXPORT_ENGINE const char* ReadAttrFromXML_str_ref(ConfigXML& xml,
												   void* element,
												   const char* attribute,
												   const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadAttrFromXML_str_ref(ConfigXML& xml,
												      void* element,
												      const wchar_t* attribute,
												      const wchar_t* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_int
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   int defaul ȱʡֵ
//[#03-03] ����˵����int ��������Ϣ���������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ��������@n
 *
 *  @b ˵��: ReadAttrFromXML_int������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return int ��������Ϣ��������
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    int num=ReadAttrFromeXML_int(xml,"��ͼ/·��/����","����",0);
    @endcode
*/
_EXPORT_ENGINE int ReadAttrFromXML_int(ConfigXML& xml,
									   const char* element,
									   const char* attribute,
									   int defaul=0);
_EXPORT_ENGINE int ReadAttrFromXML_int(ConfigXML& xml,
									   const wchar_t* element,
									   const wchar_t* attribute,
									   int defaul=0);
_EXPORT_ENGINE int ReadAttrFromXML_int(ConfigXML& xml,
									   void* element,
									   const char* attribute,
									   int defaul=0);
_EXPORT_ENGINE int ReadAttrFromXML_int(ConfigXML& xml,
									   void* element,
									   const wchar_t* attribute,
									   int defaul=0);
_EXPORT_ENGINE bool ReadAttrFromXML_int_n(ConfigXML& xml,
										  const char* element,
										  const char* attribute,
										  int* value,
										  const int* defaul=NULL,
										  int n=1);
_EXPORT_ENGINE bool ReadAttrFromXML_int_n(ConfigXML& xml,
										  const wchar_t* element,
										  const wchar_t* attribute,
										  int* value,
										  const int* defaul=NULL,
										  int n=1);
_EXPORT_ENGINE bool ReadAttrFromXML_int_n(ConfigXML& xml,
										  void* element,
										  const char* attribute,
										  int* value,
										  const int* defaul=NULL,
										  int n=1);
_EXPORT_ENGINE bool ReadAttrFromXML_int_n(ConfigXML& xml,
									  	  void* element,
										  const wchar_t* attribute,
										  int* value,
										  const int* defaul=NULL,
										  int n=1);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_hex
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   int defaul ȱʡֵ
//[#03-03] ����˵����int ��������Ϣ���������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ��������@n
 *
 *  @b ˵��: ReadAttrFromXML_hex������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ��������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return int ��������Ϣ��������
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    int num=ReadAttrFromeXML_hex(xml,"��ͼ/·��/����","����",0);
    @endcode
*/
_EXPORT_ENGINE int ReadAttrFromXML_hex(ConfigXML& xml,
									   const char* element,
									   const char* attribute,
									   int defaul=0);
_EXPORT_ENGINE int ReadAttrFromXML_hex(ConfigXML& xml,
									   const wchar_t* element,
									   const wchar_t* attribute,
									   int defaul=0);
_EXPORT_ENGINE int ReadAttrFromXML_hex(ConfigXML& xml,
									   void* element,
									   const char* attribute,
									   int defaul=0);
_EXPORT_ENGINE int ReadAttrFromXML_hex(ConfigXML& xml,
									   void* element,
									   const wchar_t* attribute,
									   int defaul=0);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_int64
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   __int64 defaul ȱʡֵ
//[#03-03] ����˵����__int64 ��������Ϣ��64λ�������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ����������@n
 *
 *  @b ˵��: ReadAttrFromXML_int64������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ��������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return __int64 ��������Ϣ��64λ������
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    long num=ReadAttrFromeXML_long(xml,"��ͼ/·��/����","����",0);
    @endcode
*/
_EXPORT_ENGINE __int64 ReadAttrFromXML_int64(ConfigXML& xml,
											 const char* element,
											 const char* attribute,
											 __int64 defaul=0);
_EXPORT_ENGINE __int64 ReadAttrFromXML_int64(ConfigXML& xml,
											 const wchar_t* element,
											 const wchar_t* attribute,
											 __int64 defaul=0);
_EXPORT_ENGINE __int64 ReadAttrFromXML_int64(ConfigXML& xml,
											 void* element,
											 const char* attribute,
											 __int64 defaul=0);
_EXPORT_ENGINE __int64 ReadAttrFromXML_int64(ConfigXML& xml,
											 void* element,
											 const wchar_t* attribute,
											 __int64 defaul=0);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_bool
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   bool defaul ȱʡֵ
//[#03-03] ����˵����bool ��������Ϣ���������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ��������@n
 *
 *  @b ˵��: ReadAttrFromXML_bool������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ��������ͣ������򷵻�false @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return bool ��������Ϣ���������ͣ�
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool earth=ReadAttrFromeXML_bool(xml,"��ͼ/·��/����","����",false);
    @endcode
*/
_EXPORT_ENGINE bool ReadAttrFromXML_bool(ConfigXML& xml,
										 const char* element,
										 const char* attribute,
										 bool defaul=false);
_EXPORT_ENGINE bool ReadAttrFromXML_bool(ConfigXML& xml,
										 const wchar_t* element,
										 const wchar_t* attribute,
										 bool defaul=false);
_EXPORT_ENGINE bool ReadAttrFromXML_bool(ConfigXML& xml,
										 void* element,
										 const char* attribute,
										 bool defaul=false);
_EXPORT_ENGINE bool ReadAttrFromXML_bool(ConfigXML& xml,
										 void* element,
										 const wchar_t* attribute,
										 bool defaul=false);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_float
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   float defaul
//[#03-03] ����˵����float ��������Ϣ�������ȸ������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ�����ȸ�������@n
 *
 *  @b ˵��: ReadAttrFromXML_float������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ������ȸ������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return float ��������Ϣ�������ȸ�������
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    float size=ReadAttrFromeXML_float(xml,"��ͼ/·��/����","�ߴ�",256);
    @endcode
*/
_EXPORT_ENGINE float ReadAttrFromXML_float(ConfigXML& xml,
										   const char* element,
										   const char* attribute,
										   float defaul=0.0f);
_EXPORT_ENGINE float ReadAttrFromXML_float(ConfigXML& xml,
										   const wchar_t* element,
										   const wchar_t* attribute,
										   float defaul=0.0f);
_EXPORT_ENGINE float ReadAttrFromXML_float(ConfigXML& xml,
										   void* element,
										   const char* attribute,
										   float defaul=0.0f);
_EXPORT_ENGINE float ReadAttrFromXML_float(ConfigXML& xml,
										   void* element,
										   const wchar_t* attribute,
										   float defaul=0.0f);
_EXPORT_ENGINE bool ReadAttrFromXML_float_n(ConfigXML& xml,
											const char* element,
											const char* attribute,
											float* value,
											const float* defaul=NULL,
											int n=1);
_EXPORT_ENGINE bool ReadAttrFromXML_float_n(ConfigXML& xml,
											const wchar_t* element,
											const wchar_t* attribute,
											float* value,
											const float* defaul=NULL,
											int n=1);
_EXPORT_ENGINE bool ReadAttrFromXML_float_n(ConfigXML& xml,
											void* element,
											const char* attribute,
											float* value,
											const float* defaul=NULL,
											int n=1);
_EXPORT_ENGINE bool ReadAttrFromXML_float_n(ConfigXML& xml,
											void* element,
											const wchar_t* attribute,
											float* value,
											const float* defaul=NULL,
											int n=1);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_double
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   double defaul ȱʡֵ
//[#03-03] ����˵����double ��������Ϣ��˫���ȸ������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�0
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: ReadAttrFromXML_float������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ�˫���ȸ������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return double��������Ϣ��˫���ȸ�������
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"��ͼ/·��/����","�ߴ�",256);
    @endcode
*/
_EXPORT_ENGINE double ReadAttrFromXML_double(ConfigXML& xml,
											 const char* element,
											 const char* attribute,
											 double defaul=0.0);
_EXPORT_ENGINE double ReadAttrFromXML_double(ConfigXML& xml,
											 const wchar_t* element,
											 const wchar_t* attribute,
											 double defaul=0.0);
_EXPORT_ENGINE double ReadAttrFromXML_double(ConfigXML& xml,
											 void* element,
											 const char* attribute,
											 double defaul=0.0);
_EXPORT_ENGINE double ReadAttrFromXML_double(ConfigXML& xml,
											 void* element,
											 const wchar_t* attribute,
											 double defaul=0.0);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_uuid
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   unsigned int* value ֵ
//                   unsigned int* defaul ȱʡֵ
//[#03-03] ����˵����
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: ReadAttrFromXML_float������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ�˫���ȸ������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"��ͼ/·��/����","�ߴ�",256);
    @endcode
*/
_EXPORT_ENGINE bool ReadAttrFromXML_uuid(ConfigXML& xml,
										 const char* element,
										 const char* attribute,
										 unsigned int* value,
										 const unsigned int* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid(ConfigXML& xml,
										 const wchar_t* element,
										 const wchar_t* attribute,
										 unsigned int* value,
										 const unsigned int* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid(ConfigXML& xml,
										 void* element,
										 const char* attribute,
										 unsigned int* value,
										 const unsigned int* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid(ConfigXML& xml,
										 void* element,
										 const wchar_t* attribute,
										 unsigned int* value,
										 const unsigned int* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_uuid_ref
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   unsigned int* value ֵ
//                   unsigned int* defaul ȱʡֵ
//[#03-03] ����˵����
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: ReadAttrFromXML_float������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ�˫���ȸ������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"��ͼ/·��/����","�ߴ�",256);
    @endcode
*/
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
											 const char* element,
											 const char* attribute,
											 unsigned int* value,
											 const unsigned int* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
											 const wchar_t* element,
											 const wchar_t* attribute,
											 unsigned int* value,
											 const unsigned int* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
											 void* element,
											 const char* attribute,
											 unsigned int* value,
											 const unsigned int* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
											 void* element,
											 const wchar_t* attribute,
											 unsigned int* value,
											 const unsigned int* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_uuid_str
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   unsigned int* value ֵ
//                   unsigned int* defaul ȱʡֵ
//[#03-03] ����˵����
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ˫���ȸ�������@n
 *
 *  @b ˵��: ReadAttrFromXML_float������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ�˫���ȸ������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"��ͼ/·��/����","�ߴ�",256);
    @endcode
*/
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
											 const char* element,
											 const char* attribute,
											 unsigned char* value,
											 const unsigned char* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
										     const wchar_t* element,
										     const wchar_t* attribute,
										     unsigned char* value,
										     const unsigned char* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
											 void* element,
											 const char* attribute,
											 unsigned char* value,
											 const unsigned char* defaul=NULL);
_EXPORT_ENGINE bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
											 void* element,
											 const wchar_t* attribute,
											 unsigned char* value,
											 const unsigned char* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_color
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* attribute ָ������
//                   int defaul ȱʡֵ
//[#03-03] ����˵����unsigned int ��������Ϣ���������ͣ�
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ��ָ�����ԣ�����ֵΪ��������@n
 *
 *  @b ˵��: ReadAttrFromXML_int������ָ����XML�ļ������е���SearchAttribute��������@n
 *     ָ�������Զ�����������Դ�������������Ե�ֵ���أ������������򷵻�0 @n@n
 *  @b ע��: @n
 *          1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *          2) ���ָ�����Զ��󲻴��ں���Ҳ���ܷ���һ�������ֵ��@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param attribute ָ������
 *  @param defaul ȱʡֵ
 *  @return int ��������Ϣ��������
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    unsigned int color=ReadAttrFromeXML_int(xml,"��ͼ/·��/��ɫ","��ֵ",0x00ffffff);
    @endcode
*/
_EXPORT_ENGINE unsigned int ReadAttrFromXML_color(ConfigXML& xml,
												  const char* element,
												  const char* attribute,
												  unsigned int defaul=0);
_EXPORT_ENGINE unsigned int ReadAttrFromXML_color(ConfigXML& xml,
												  const wchar_t* element,
												  const wchar_t* attribute,
												  unsigned int defaul=0);
_EXPORT_ENGINE unsigned int ReadAttrFromXML_color(ConfigXML& xml,
												  void* element,
												  const char* attribute,
												  unsigned int defaul=0);
_EXPORT_ENGINE unsigned int ReadAttrFromXML_color(ConfigXML& xml,
												  void* element,
												  const wchar_t* attribute,
												  unsigned int defaul=0);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�RemoveTextFromXML
//[#03-01] �������ܣ���XML�ļ����Ƴ�ĳText
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//[#03-03] ����˵����bool �Ƴ��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ��������Ƴ�ָ����ǩ���ı�@n
 *
 *  @b ˵��: RemoveTextFromXML������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ������ñ�ǩ���������ı���ָ����XML�ļ��������Ƴ�������true��ʾ@n
 *     �Ƴ��ɹ�������ñ�ǩ�����ڣ������κβ�������false��ʾ��ǩ�����ڡ����ָ��@n
 *     ��ǩ�������ı��������κβ�������false��ʾ��ǩ�ı������ڡ�@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @return �Ƴ��ɹ�����true��ָ����ǩ�����ڻ�ָ����ǩ�������ı�����false
 *  @see SearchAttribute
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    bool removeok=RemoveTextFormXML(xml,"��ͼ/·��/����");
    if(removeok==true)
    {
        MessageBox(NULL,"ָ����ǩ���ı��ɹ��Ƴ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ���ı������ڣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool RemoveTextFromXML(ConfigXML& xml, const char* element);
_EXPORT_ENGINE bool RemoveTextFromXML(ConfigXML& xml, const wchar_t* element);
_EXPORT_ENGINE bool RemoveTextFromXML(ConfigXML& xml, void* element);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteTextToXML
//[#03-01] �������ܣ���ĳTextд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* text �ı�
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ���ı�д��ָ����XML�ļ������е�ָ����ǩ@n
 *
 *  @b ˵��: WriteTextToXML������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ�������ȵ���RemoveTextFromXML�������ñ�ǩԭ�ȵ�@n
 *     �ı��Ƴ����ٽ�ָ���ı�д��ñ�ǩ������true��ʾд��ɹ������򷵻�false��ʾ@n
 *     ָ���ı�ǩ�����ڡ�@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param text ��ǩ�ı�
 *  @param defaul ȱʡֵ
 *  @return TiXmlText* д��ɹ����ر�ǩ�ı�ָ�룬ʧ�ܷ���NULL��
 *  @see SearchElement, RemoveTextFromXML
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    TiXmlText* pTxt=WriteTextToXML(xml,"��ͼ/·��/����","��ͼ��ͼ���ļ�����");
    if(pTxt)
    {
        MessageBox(NULL,"ָ����ǩ���ı�д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"ָ����ǩ�����ڣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE void* WriteTextToXML(ConfigXML& xml,
					                const char* element,
					                const char* text,
					                const char* defaul=NULL);
_EXPORT_ENGINE void* WriteTextToXML(ConfigXML& xml,
					                const wchar_t* element,
					                const wchar_t* text,
					                const wchar_t* defaul=NULL);
_EXPORT_ENGINE void* WriteTextToXML(ConfigXML& xml,
					                void* element,
					                const char* text,
					                const char* defaul=NULL);
_EXPORT_ENGINE void* WriteTextToXML(ConfigXML& xml,
					                void* element,
					                const wchar_t* text,
					                const wchar_t* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadTextFromXML
//[#03-01] �������ܣ���ȡĳText
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element ָ����ǩ
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����const char* ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�Text�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ָ����XML�ļ������ж�ȡָ����ǩ���ı�@n
 *
 *  @b ˵��: ReadAttrFromXML_str������ָ����XML�ļ������е���SearchElement��������@n
 *     ָ���ı�ǩ��������ñ�ǩ����������ñ�ǩ���ı����أ��ַ���ָ�룩�����򷵻�NULL@n@n
 *  @b ע��: XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *
 *  @param xml XML�ļ�����
 *  @param element ָ����ǩ
 *  @param defaul ȱʡֵ
 *  @return const char* ��������Ϣ���ַ������ͣ�
 *  @see SearchElement
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    const char* str=ReadTextFromeXML(xml,"��ͼ/·��/����");
    if(str)
    {
        MessageBox(NULL,str,"�����ı�������",MB_OK);
    }
    else
    {
        MessageBox(NULL,"ָ���ı�ǩ������","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE const char* ReadTextFromXML(ConfigXML& xml,	const char* element, const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadTextFromXML(ConfigXML& xml, const wchar_t* element, const wchar_t* defaul=NULL);
_EXPORT_ENGINE const char* ReadTextFromXML(ConfigXML& xml, void* element, const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadTextFromXML(ConfigXML& xml, void* element, const wchar_t* defaul=NULL);

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteCommentToXML
//[#03-01] �������ܣ���ĳComment��ע�ͣ�д��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* comment ָ��ע��
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief ��ע��д��ָ����XML�ļ������е�ָ����ǩ@n
 *
 *  @b ˵��: WriteCommentToXML������ָ��ע��д��XML�����С�@n@n
 *  @b ע��: @n
 *           1) XML�ļ��ĸ�ʽ��һ�������ƣ��������Ʋμ�������ҳ;@n
 *           2) Ҫ�����ı�����е�XML�ļ����ݻ���Ҫִ��xml.SaveFile()@n
 *              �����XML����ָ���Զ��洢���ԣ�����XML����ʱ������Զ�ִ�д��̹��ܣ���@n
 *              ����ֻ��Ӱ�쵽�ڴ��е�XML�ļ�����@n
 *
 *  @param xml XML�ļ�����
 *  @param comment ָ��ע��
 *  @param defaul ȱʡֵ
 *  @return TiXmlComment* д��ɹ�����ע��ָ�룬ʧ�ܷ���NULL��
 *  @see SearchElement
 *
 *  @b ʵ��:
    @code
    ConfigXML xml("Config.xml");
    TiXmlComment* pComment=WriteCommentToXML(xml,"��ͼ��ͼ���ļ�����");
    if(pComment)
    {
        MessageBox(NULL,"ָ��ע��д��ɹ���","�ɹ�",MB_OK);
        xml.SaveFile(); //���Ҫ��������ִ�иú��������Զ����棩
    }
    else
    {
        MessageBox(NULL,"д��ע��ʧ�ܣ�","����",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE void* WriteCommentToXML(ConfigXML& xml, const char* comment, const char* defaul=NULL);
_EXPORT_ENGINE void* WriteCommentToXML(ConfigXML& xml, const wchar_t* comment, const wchar_t* defaul=NULL);

//-----------------------------�ṹ˵��----------------------------------------
//[#04-00] �ṹ���ƣ�ConfigXML
//[#04-01] �ṹ���ܣ������ļ�����
//[#04-02] �ڴ����ģ�
//[#04-03] �������ڣ�2006.6.21
//[#04-04] �޸����ڣ�
//[#04-05] ����˵����
//[#04-!!] ˵������
//-----------------------------------------------------------------------------
/** @brief �����ļ�����
 * 
 * @b ˵��: ���ڲٿ������ļ����൱���ļ������@n
*/
class _EXPORT_ENGINE ConfigXML
{
public:
	enum eCreateType ///���󴴽�����
	{
		ECT_READ   =0, ///��ȡ
		ECT_WRITE  =1, ///д��
		ECT_MODIFY =2, ///�޸�
	};
	int m_nVersion;           ///<�ĵ��汾������汾��
	int m_nFormat;            ///<�ĵ���ʽ�����ݰ汾��
	//int m_nLength;          ///<�ļ����ȣ��ֽڣ�
	bool m_bOK;               ///<�Ƿ��ʼ���ɹ�
	bool m_bDoNotSave;        ///<�Ƿ���������ĵ�
	bool m_bLowPrecision;     ///<�Ƿ�͸��㾫�ȣ�����6λ����3λ��
	bool m_bFixLengthUUID;    ///<�Ƿ�UUID���͹̶����ȣ�8*4+3=35λ��
	eCreateType m_iType;      ///<���ͣ�0,��ȡ,1д��,2�޸ģ�
	char m_chFile[MAX_PATH];  ///<�ļ���������·����
    wchar_t m_wch[1024];      ///<���ַ�����
	int m_nRefCodeUUID;       ///<uuid���ñ��
	int m_nRefCodeString;     ///<string���ñ��
	void* m_pRefUUID;         ///<uuid���ýڵ�
	void* m_pRefString;       ///<string���ýڵ�
	void* m_lastElement;      ///<�ϴδ����element����
	TiXmlElement* m_rootElement; ///<��element����
	TiXmlDocument* m_pDoc;    ///<tinyXML�ĵ�����

	void* m_cacheRoot[2];
	void* m_cacheElem;
	char  m_cacheName[MAX_PATH];
	void* m_cacheResultP;
	void* m_cacheResultA;
	int m_cacheNum;
	int m_shootNum;

public:
	ConfigXML()               ///<�չ��캯��������
	{
		m_nVersion=CONFIGXML_VERSION;
		m_nFormat=CONFIGXML_FORMAT;
		//m_nLength=0;
		m_nRefCodeUUID=0;
		m_nRefCodeString=0;
		m_pRefUUID=0;
		m_pRefString=0;
		m_lastElement=0;
		m_rootElement=0;
		m_iType=ECT_READ;
		m_bDoNotSave=false;
		m_bLowPrecision=false;
		m_bFixLengthUUID=true;
		strcpy(m_chFile,"noname.txt");
		m_pDoc=new TiXmlDocument(m_chFile);

		if(m_pDoc)
		{
			TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
			TiXmlNode* node=m_pDoc->LinkEndChild(e);
			m_rootElement=node->ToElement();
			WriteAttrToXML_int(*this,"__DOC__","version",m_nVersion);
			WriteAttrToXML_int(*this,"__DOC__","format",m_nFormat);
			m_bOK=true;
		}
		else m_bOK=false;

		m_cacheNum=0;
		m_shootNum=0;
		m_cacheResultP=0;
		m_cacheResultA=0;
	}
	ConfigXML(const char* p_chName, eCreateType p_iType=ECT_READ, int p_nFormat=CONFIGXML_FORMAT) ///<���������캯��
	{
		m_nVersion=CONFIGXML_VERSION;
		m_nFormat=p_nFormat;
		//m_nLength=0;
		m_nRefCodeUUID=0;
		m_nRefCodeString=0;
		m_pRefUUID=0;
		m_pRefString=0;
		m_lastElement=0;
		m_rootElement=0;
		m_iType=p_iType;
		m_bDoNotSave=false;
		m_bLowPrecision=false;
		m_bFixLengthUUID=true;
		if(p_chName)
			strncpy(m_chFile,p_chName,MAX_PATH-1);
		else strcpy(m_chFile,"noname.txt");
		m_pDoc=new TiXmlDocument(m_chFile);
		if(m_pDoc) m_bOK=true;
		else m_bOK=false;

		m_cacheNum=0;
		m_shootNum=0;
		m_cacheResultP=0;
		m_cacheResultA=0;

		if(m_pDoc)
		{
			if(p_iType==ECT_READ
				||p_iType==ECT_MODIFY)
			{
				if(!m_pDoc->LoadFile()&&p_iType==ECT_READ)
					m_bOK=false;
				if(m_bOK)
				{
					m_rootElement=m_pDoc->FirstChildElement(CONFIGXML_ROOT);
					if(!m_rootElement)
					{
						TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
                        TiXmlElement* f=m_pDoc->FirstChildElement();
						TiXmlNode* node=m_pDoc->LinkEndChild(e);
						m_rootElement=node->ToElement();
						while(f)
						{
							m_rootElement->InsertEndChild(*f);
							f=f->NextSiblingElement();
						}
					}
					//m_nLength=m_pDoc->FileLength();
					m_nVersion=ReadAttrFromXML_int(*this,"__DOC__","version",0);
					m_nFormat=ReadAttrFromXML_int(*this,"__DOC__","format",0);
					if(m_nVersion==0)
						m_nVersion=CONFIGXML_VERSION;
					if(m_nFormat==0)
						m_nFormat=CONFIGXML_FORMAT;
				}
			}
			else
			{
				TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
				TiXmlNode* node=m_pDoc->LinkEndChild(e);
				m_rootElement=node->ToElement();
			}
			if(m_bOK)
			{
			    WriteAttrToXML_int(*this,"__DOC__","version",m_nVersion);
			    WriteAttrToXML_int(*this,"__DOC__","format",m_nFormat);
			}
		}
	}
	ConfigXML(const wchar_t* p_chName, eCreateType p_iType=ECT_READ, int p_nFormat=CONFIGXML_FORMAT) ///<���������캯��
	{
		m_nVersion=CONFIGXML_VERSION;
		m_nFormat=p_nFormat;
		//m_nLength=0;
		m_nRefCodeUUID=0;
		m_nRefCodeString=0;
		m_pRefUUID=0;
		m_pRefString=0;
		m_lastElement=0;
		m_rootElement=0;
		m_iType=p_iType;
		m_bDoNotSave=false;
		m_bLowPrecision=false;
		m_bFixLengthUUID=true;
		if(p_chName)
            ConfigXML_UnicodeToAnsi(p_chName,m_chFile,MAX_PATH-1);
		else strcpy(m_chFile,"noname.txt");
		m_pDoc=new TiXmlDocument(m_chFile);
		if(m_pDoc) m_bOK=true;
		else m_bOK=false;

		m_cacheNum=0;
		m_shootNum=0;
		m_cacheResultP=0;
		m_cacheResultA=0;

		if(m_pDoc)
		{
			if(p_iType==ECT_READ
				||p_iType==ECT_MODIFY)
			{
				if(!m_pDoc->LoadFile()&&p_iType==ECT_READ)
					m_bOK=false;
				if(m_bOK)
				{
					m_rootElement=m_pDoc->FirstChildElement(CONFIGXML_ROOT);
					if(!m_rootElement)
					{
						TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
                        TiXmlElement* f=m_pDoc->FirstChildElement();
						TiXmlNode* node=m_pDoc->LinkEndChild(e);
						m_rootElement=node->ToElement();
						while(f)
						{
							m_rootElement->InsertEndChild(*f);
							f=f->NextSiblingElement();
						}
					}
					//m_nLength=m_pDoc->FileLength();
					m_nVersion=ReadAttrFromXML_int(*this,"__DOC__","version",0);
					m_nFormat=ReadAttrFromXML_int(*this,"__DOC__","format",0);
					if(m_nVersion==0)
						m_nVersion=CONFIGXML_VERSION;
					if(m_nFormat==0)
						m_nFormat=CONFIGXML_FORMAT;
				}
			}
			else
			{
				TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
				TiXmlNode* node=m_pDoc->LinkEndChild(e);
				m_rootElement=node->ToElement();
			}
			if(m_bOK)
			{
			    WriteAttrToXML_int(*this,"__DOC__","version",m_nVersion);
			    WriteAttrToXML_int(*this,"__DOC__","format",m_nFormat);
			}
		}
	}
	virtual ~ConfigXML() ///<��������
	{
		if(m_pDoc)
		{
			if(m_iType==ECT_WRITE||m_iType==ECT_MODIFY)
			{
				if(!m_bDoNotSave)
				{
					ConfigXML_createPath(m_chFile);
					m_pDoc->SaveFile();
				}
			}
			delete m_pDoc;
		}
	}
	void Clear(int p_nFormat=CONFIGXML_FORMAT)
	{
		if(m_pDoc)
			m_pDoc->Clear();
		ClearCache();
		m_nVersion=CONFIGXML_VERSION;
		m_nFormat=p_nFormat;
		TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
		TiXmlNode* node=m_pDoc->LinkEndChild(e);
		m_rootElement=node->ToElement();
		WriteAttrToXML_int(*this,"__DOC__","version",m_nVersion);
		WriteAttrToXML_int(*this,"__DOC__","format",m_nFormat);
		if(m_pRefUUID)
		{
			m_nRefCodeUUID=0;
			m_pRefUUID=WriteElemToXML(*this,0,"__UUID__",false);
		}
		if(m_pRefString)
		{
			m_nRefCodeString=0;
			m_pRefString=WriteElemToXML(*this,0,"__STRING__",false);
		}
	}
	bool LoadFromMemory(const char* data, int length)
	{
		if(!m_pDoc||!data||length==0) return false;

	    m_pDoc->Clear();
		ClearCache();
		m_bOK=m_pDoc->LoadFromMemory(data,length);
		if(m_bOK)
		{
			TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
		    TiXmlNode* node=m_pDoc->LinkEndChild(e);
		    m_rootElement=node->ToElement();
			WriteAttrToXML_int(*this,"__DOC__","version",m_nVersion);
		    WriteAttrToXML_int(*this,"__DOC__","format",m_nFormat);
			if(m_pRefUUID)
			{
				m_pRefUUID=WriteElemToXML(*this,0,"__UUID__");
				m_nRefCodeUUID=ReadAttrFromXML_int(*this,m_pRefUUID,"code",0);
			}
			if(m_pRefString)
			{
				m_pRefString=WriteElemToXML(*this,0,"__STRING__");
				m_nRefCodeString=ReadAttrFromXML_int(*this,m_pRefString,"code",0);
			}
		}
		return m_bOK;
	}
	bool LoadFile(const char* p_chName)
	{
		if(!m_pDoc||!p_chName) return false;

		m_pDoc->Clear();
		ClearCache();
		strncpy(m_chFile,p_chName,MAX_PATH-1);
		m_bOK=m_pDoc->LoadFile(p_chName);
		if(m_bOK)
		{
			TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
		    TiXmlNode* node=m_pDoc->LinkEndChild(e);
		    m_rootElement=node->ToElement();
			WriteAttrToXML_int(*this,"__DOC__","version",m_nVersion);
		    WriteAttrToXML_int(*this,"__DOC__","format",m_nFormat);
			if(m_pRefUUID)
			{
				m_pRefUUID=WriteElemToXML(*this,0,"__UUID__");
				m_nRefCodeUUID=ReadAttrFromXML_int(*this,m_pRefUUID,"code",0);
			}
			if(m_pRefString)
			{
				m_pRefString=WriteElemToXML(*this,0,"__STRING__");
				m_nRefCodeString=ReadAttrFromXML_int(*this,m_pRefString,"code",0);
			}
		}
		return m_bOK;
	}
	bool LoadFile(const wchar_t* p_chName)
	{
		if(!m_pDoc||!p_chName) return false;

		m_pDoc->Clear();
		ClearCache();
		ConfigXML_UnicodeToAnsi(p_chName,m_chFile,MAX_PATH-1);
		m_bOK=m_pDoc->LoadFile(m_chFile);
		if(m_bOK)
		{
			TiXmlElement* e=new TiXmlElement(CONFIGXML_ROOT);
		    TiXmlNode* node=m_pDoc->LinkEndChild(e);
		    m_rootElement=node->ToElement();
			WriteAttrToXML_int(*this,"__DOC__","version",m_nVersion);
		    WriteAttrToXML_int(*this,"__DOC__","format",m_nFormat);
			if(m_pRefUUID)
			{
				m_pRefUUID=WriteElemToXML(*this,0,"__UUID__");
				m_nRefCodeUUID=ReadAttrFromXML_int(*this,m_pRefUUID,"code",0);
			}
			if(m_pRefString)
			{
				m_pRefString=WriteElemToXML(*this,0,"__STRING__");
				m_nRefCodeString=ReadAttrFromXML_int(*this,m_pRefString,"code",0);
			}
		}
		return m_bOK;
	}
	bool SaveFile() ///<�ֶ������ļ�����
	{
		if(m_pDoc)
		{
			ConfigXML_createPath(m_chFile);
			bool ret=m_pDoc->SaveFile();
			//m_nLength=m_pDoc->FileLength();
			return ret;
		}
		return false;
	}
	bool SaveAs(const char* p_chName) ///<���Ϊ����
	{
		if(m_pDoc&&p_chName)
		{
			ConfigXML_createPath(p_chName);
			bool ret=m_pDoc->SaveFile(p_chName);
			//m_nLength=m_pDoc->FileLength();
			return ret;
		}
		return false;
	}
	bool SaveAs(const wchar_t* p_chName) ///<���Ϊ����
	{
		if(m_pDoc&&p_chName)
		{
			char chNameAnsi[MAX_PATH];
			ConfigXML_UnicodeToAnsi(p_chName,chNameAnsi,MAX_PATH);
			ConfigXML_createPath(chNameAnsi);
			bool ret=m_pDoc->SaveFile(chNameAnsi);
			//m_nLength=m_pDoc->FileLength();
			return ret;
		}
		return false;
	}
	void ClearCache() { m_cacheResultP=0; m_cacheResultA=0; }
	void SetRefUUID(bool enable)
	{
		if(enable)
		{
			if(!m_pRefUUID)
			{
			    m_pRefUUID=WriteElemToXML(*this,0,"__UUID__");
				m_nRefCodeUUID=ReadAttrFromXML_int(*this,m_pRefUUID,"code",0);
			}
		}
		else
		{
			if(m_pRefUUID)
			{
				RemoveElemFromXML(*this,0,m_pRefUUID);
				m_nRefCodeUUID=0;
				m_pRefUUID=0;
			}
		}
	}
	void SetRefString(bool enable)
	{
		if(enable)
		{
			if(!m_pRefString)
			{
			    m_pRefString=WriteElemToXML(*this,0,"__STRING__");
				m_nRefCodeString=ReadAttrFromXML_int(*this,m_pRefString,"code",0);
			}
		}
		else
		{
            if(m_pRefString)
			{
				RemoveElemFromXML(*this,0,m_pRefString);
				m_nRefCodeString=0;
				m_pRefString=0;
			}
		}
	}
	int Grab_UUID_Ref(const unsigned int* value)
	{
		if(!m_pRefUUID) return 0;
		char str[64];
		if(m_bFixLengthUUID)
			sprintf(str,"%08x.%08x.%08x.%08x",value[0],value[1],value[2],value[3]);
		else sprintf(str,"%x.%x.%x.%x",value[0],value[1],value[2],value[3]);
		void* elem=SearchElemInXMLByAttr(*this,m_pRefUUID,"uu",str);
		if(elem)
		{
			int ref=ReadAttrFromXML_int(*this,elem,"re",1);
			int code=ReadAttrFromXML_int(*this,elem,"co",1);
            WriteAttrToXML_int(*this,elem,"re",++ref);
			return code;
		}
		else
		{
			elem=WriteElemToXML(*this,m_pRefUUID,"uui",false);
            WriteAttrToXML_str(*this,elem,"uu",str);
			WriteAttrToXML_int(*this,elem,"re",1);
			WriteAttrToXML_int(*this,elem,"co",++m_nRefCodeUUID);
			WriteAttrToXML_int(*this,m_pRefUUID,"code",m_nRefCodeUUID);
			return m_nRefCodeUUID;
		}
	}
	int Drop_UUID_Ref(const unsigned int* value)
	{
		if(!m_pRefUUID) return 0;
        char str[64];
		if(m_bFixLengthUUID)
			sprintf(str,"%08x.%08x.%08x.%08x",value[0],value[1],value[2],value[3]);
		else sprintf(str,"%x.%x.%x.%x",value[0],value[1],value[2],value[3]);
		void* elem=SearchElemInXMLByAttr(*this,m_pRefUUID,"uu",str);
		if(elem)
		{
			int ref=ReadAttrFromXML_int(*this,elem,"re",1);
			int code=ReadAttrFromXML_int(*this,elem,"co",1);
			if(ref==1)
				RemoveElemFromXML(*this,0,elem);
			else WriteAttrToXML_int(*this,elem,"re",--ref);
			return code;
		}
		return 0;
	}
	bool Read_UUID_Ref(int code, unsigned int* value, const unsigned int* defaul)
	{
		if(!m_pRefUUID||!value) return false;
		char str[16];
        sprintf(str,"%d",code);
		void* elem=SearchElemInXMLByAttr(*this,m_pRefUUID,"co",str);
		if(elem)
			return ReadAttrFromXML_uuid(*this,elem,"uu",value,defaul);
		return false;
	}
	int Grab_String_Ref(const char* value)
	{
		if(!m_pRefString||!value) return 0;
		void* elem=SearchElemInXMLByAttr(*this,m_pRefString,"st",value);
		if(elem)
		{
			int ref=ReadAttrFromXML_int(*this,elem,"re",1);
			int code=ReadAttrFromXML_int(*this,elem,"co",1);
            WriteAttrToXML_int(*this,elem,"re",++ref);
			return code;
		}
		else
		{
			elem=WriteElemToXML(*this,m_pRefString,"str",false);
            WriteAttrToXML_str(*this,elem,"st",value);
			WriteAttrToXML_int(*this,elem,"re",1);
			WriteAttrToXML_int(*this,elem,"co",++m_nRefCodeString);
			WriteAttrToXML_int(*this,m_pRefString,"code",m_nRefCodeString);
			return m_nRefCodeString;
		}
	}
	int Drop_String_Ref(const char* value)
	{
		if(!m_pRefString||!value) return 0;
        void* elem=SearchElemInXMLByAttr(*this,m_pRefString,"st",value);
		if(elem)
		{
			int ref=ReadAttrFromXML_int(*this,elem,"re",1);
			int code=ReadAttrFromXML_int(*this,elem,"co",1);
			if(ref==1)
				RemoveElemFromXML(*this,0,elem);
			else WriteAttrToXML_int(*this,elem,"re",--ref);
			return code;
		}
		return 0;
	}
	const char* Read_String_Ref(int code, const char* defaul)
	{
		if(!m_pRefString) return false;
		char str[16];
        sprintf(str,"%d",code);
		void* elem=SearchElemInXMLByAttr(*this,m_pRefString,"co",str);
		if(elem)
			return ReadAttrFromXML_str(*this,elem,"st",defaul);
		return false;
	}
	int GetElementNum(void* element, const char* attribute=0, bool recur=false)
	{
		vector<void*> list;
		_childElement(&list,element,attribute,recur);
		return list.size();
	}
	int GetElementNum(void* element, const wchar_t* attribute=0, bool recur=false)
	{
		vector<void*> list;
		_childElement(&list,element,attribute,recur);
		return list.size();
	}
	int GetElementAll(vector<void*>* list, void* element, const char* attribute=0, bool recur=false)
	{
		if(!list) return 0;
		_childElement(list,element,attribute,recur);
		return list->size();
	}
	int GetElementAll(vector<void*>* list, void* element, const wchar_t* attribute=0, bool recur=false)
	{
		if(!list) return 0;
		_childElement(list,element,attribute,recur);
		return list->size();
	}
	int GetChildElementList(vector<void*>* list, void* element)
	{
		if(!list) return 0;

		list->clear();
		TiXmlElement* child;
	    if(element)
			child=((TiXmlElement*)element)->FirstChildElement();
	    else child=m_pDoc->FirstChildElement();

		while(child)
		{
			list->push_back(child);
			child=child->NextSiblingElement();
		}
		return list->size();
	}
    int GetChildElementList(vector<void*>* list, const char* element)
	{
		if(!list) return 0;

		list->clear();
		TiXmlElement* child;
	    if(element)
		{
			child=(TiXmlElement*)SearchElemInXML(*this,NULL,element);
			if(child) child=child->FirstChildElement();
		}
	    else child=m_pDoc->FirstChildElement();

		while(child)
		{
			list->push_back(child);
			child=child->NextSiblingElement();
		}
		return list->size();
	}
	int GetChildElementList(vector<void*>* list, const wchar_t* element)
	{
		if(!list) return 0;

		list->clear();
		TiXmlElement* child;
	    if(element)
		{
			child=(TiXmlElement*)SearchElemInXML(*this,NULL,element);
			if(child) child=child->FirstChildElement();
		}
	    else child=m_pDoc->FirstChildElement();

		while(child)
		{
			list->push_back(child);
			child=child->NextSiblingElement();
		}
		return list->size();
	}

private:
	void _childElement(vector<void*>* list, void* element, const char* attribute=0, bool recur=false)
	{
        if(!list) return;

		TiXmlElement* child;
	    if(element)
			child=((TiXmlElement*)element)->FirstChildElement();
	    else child=m_pDoc->FirstChildElement();

		while(child)
		{
			if(!attribute||SearchAttrInXML(*this,child,attribute))
			    list->push_back(child);
			if(recur)
				_childElement(list,child,attribute,true);
			child=child->NextSiblingElement();
		}
	}
	void _childElement(vector<void*>* list, void* element, const wchar_t* attribute=0, bool recur=false)
	{
        if(!list) return;

		TiXmlElement* child;
	    if(element)
			child=((TiXmlElement*)element)->FirstChildElement();
	    else child=m_pDoc->FirstChildElement();

		while(child)
		{
			if(!attribute||SearchAttrInXML(*this,child,attribute))
				list->push_back(child);
			if(recur)
				_childElement(list,child,attribute,true);
			child=child->NextSiblingElement();
		}
	}
	void _childElementCount(vector<void*>* list, const char* element, const char* attribute=0, bool recur=false)
	{
		if(!list) return;

		TiXmlElement* child;
	    if(element)
		{
			child=(TiXmlElement*)SearchElemInXML(*this,NULL,element);
			if(child) child=child->FirstChildElement();
		}
	    else child=m_pDoc->FirstChildElement();

		while(child)
		{
			if(!attribute||SearchAttrInXML(*this,child,attribute))
				list->push_back(child);
			if(recur)
				_childElement(list,child,attribute,true);
			child=child->NextSiblingElement();
		}
	}
	void _childElementCount(vector<void*>* list, const wchar_t* element, const wchar_t* attribute=0, bool recur=false)
	{
		if(!list) return;

		TiXmlElement* child;
	    if(element)
		{
			child=(TiXmlElement*)SearchElemInXML(*this,NULL,element);
			if(child) child=child->FirstChildElement();
		}
	    else child=m_pDoc->FirstChildElement();

		while(child)
		{
			if(!attribute||SearchAttrInXML(*this,child,attribute))
				list->push_back(child);
			if(recur)
				_childElement(list,child,attribute,true);
			child=child->NextSiblingElement();
		}
	}

public:

#define WA_RA_INTERFACE(_name,_type,_def) \
	inline bool wa_##_name(const char* element, const char* attribute, _type value)\
	{ return WriteAttrToXML_##_name(*this,element,attribute,value); }\
	inline bool wa_##_name(const wchar_t* element, const wchar_t* attribute, _type value)\
	{ return WriteAttrToXML_##_name(*this,element,attribute,value); }\
	inline bool wa_##_name(void* element, const char* attribute, _type value)\
	{ return WriteAttrToXML_##_name(*this,element,attribute,value); }\
    inline bool wa_##_name(void* element, const wchar_t* attribute, _type value)\
	{ return WriteAttrToXML_##_name(*this,element,attribute,value); }\
	inline _type ra_##_name(const char* element, const char* attribute, _type defaul=_def)\
	{ return ReadAttrFromXML_##_name(*this,element,attribute,defaul); }\
    inline _type ra_##_name(const wchar_t* element, const wchar_t* attribute, _type defaul=_def)\
	{ return ReadAttrFromXML_##_name(*this,element,attribute,defaul); }\
    inline _type ra_##_name(void* element, const char* attribute, _type defaul=_def)\
	{ return ReadAttrFromXML_##_name(*this,element,attribute,defaul); }\
    inline _type ra_##_name(void* element, const wchar_t* attribute, _type defaul=_def)\
	{ return ReadAttrFromXML_##_name(*this,element,attribute,defaul); }\

	//string
	bool wa_str(const char* element, const char* attribute, const char* value, const char* defaul=NULL)
	{ return WriteAttrToXML_str(*this,element,attribute,value,defaul); }
    bool wa_str(const wchar_t* element, const wchar_t* attribute, const wchar_t* value, const wchar_t* defaul=NULL)
	{ return WriteAttrToXML_str(*this,element,attribute,value,defaul); }
    bool wa_str(void* element, const char* attribute, const char* value, const char* defaul=NULL)
	{ return WriteAttrToXML_str(*this,element,attribute,value,defaul); }
    bool wa_str(void* element, const wchar_t* attribute, const wchar_t* value, const wchar_t* defaul=NULL)
	{ return WriteAttrToXML_str(*this,element,attribute,value,defaul); }
	const char* ra_str(const char* element, const char* attribute, const char* defaul=NULL)
	{ return ReadAttrFromXML_str(*this,element,attribute,defaul); }
    const wchar_t* ra_str(const wchar_t* element, const wchar_t* attribute, const wchar_t* defaul=NULL)
	{ return ReadAttrFromXML_str(*this,element,attribute,defaul); }
    const char* ra_str(void* element, const char* attribute, const char* defaul=NULL)
	{ return ReadAttrFromXML_str(*this,element,attribute,defaul); }
    const wchar_t* ra_str(void* element, const wchar_t* attribute, const wchar_t* defaul=NULL)
	{ return ReadAttrFromXML_str(*this,element,attribute,defaul); }

	WA_RA_INTERFACE(bool,bool,false)
	WA_RA_INTERFACE(int,int,0)
	WA_RA_INTERFACE(hex,int,0)
	WA_RA_INTERFACE(int64,__int64,0)
	WA_RA_INTERFACE(float,float,0.0f)
	WA_RA_INTERFACE(double,double,0.0)
	WA_RA_INTERFACE(color,unsigned int,0)

	//text
	void* wt_str(const char* element, const char* text, const char* defaul=NULL)
	{ return WriteTextToXML(*this,element,text,defaul); }
    void* wt_str(const wchar_t* element, const wchar_t* text, const wchar_t* defaul=NULL)
	{ return WriteTextToXML(*this,element,text,defaul); }
    void* wt_str(void* element, const char* text, const char* defaul=NULL)
	{ return WriteTextToXML(*this,element,text,defaul); }
    void* wt_str(void* element, const wchar_t* text, const wchar_t* defaul=NULL)
	{ return WriteTextToXML(*this,element,text,defaul); }
	const char* rt_str(const char* element, const char* defaul=NULL)
	{ return ReadTextFromXML(*this,element,defaul); }
    const wchar_t* rt_str(const wchar_t* element, const wchar_t* defaul=NULL)
	{ return ReadTextFromXML(*this,element,defaul); }
    const char* rt_str(void* element, const char* defaul=NULL)
	{ return ReadTextFromXML(*this,element,defaul); }
    const wchar_t* rt_str(void* element, const wchar_t* defaul=NULL)
	{ return ReadTextFromXML(*this,element,defaul); }

#undef WA_RA_INTERFACE

#define CF_XML_WA(_t,_v) xml.wa_##_t(#_v,"a",_v);
#define CF_XML_RA(_t,_v) _v=xml.ra_##_t(#_v,"a");

#define CF_XML_WA_ARRAY(_t,_v) \
	{\
		char str[32];\
		s32 n=sizeof(_v)/sizeof(_t);\
		for(s32 i=0; i<n; i++)\
		{\
			sprintf(str,"a_%d",i);\
			xml.wa_##_t(#_v,str,_v[i]);\
		}\
	}

#define CF_XML_RA_ARRAY(_t,_v) \
	{\
		char str[32];\
		s32 n=sizeof(_v)/sizeof(_t);\
		for(s32 i=0; i<n; i++)\
		{\
			sprintf(str,"a_%d",i);\
			_v[i]=xml.ra_##_t(#_v,str);\
		}\
	}

#define VIRTUAL_CONFIG_XML_SAVE_DATA \
virtual bool saveData(CONFIGXML_TYPE& xml, const char* element); \
virtual bool loadData(CONFIGXML_TYPE& xml, const char* element);

#define VIRTUAL_CONFIG_XML_SAVE_FILE \
virtual bool saveFile(const char* file); \
virtual bool loadFile(const char* file);

};
//-----------------------------�ṹ����----------------------------------------

#endif //_CONFIGXML_H_2006_02_03_13_14_45_R19073_
//-----------------------------------------------------------------------------
///////////////////////////////�ļ�����////////////////////////////////////////