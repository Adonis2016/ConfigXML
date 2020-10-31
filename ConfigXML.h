/////////////////////////////程序文件说明//////////////////////////////////////
//[#01-00] 文件名称：ConfigXML.h
//[#01-01] 文件说明：用于支持XML格式的配置文件
//[#01-02] 建立日期：2006.02.03
//[#01-03] 修改日期：2015.08.10
//[#01-04] 作者姓名：赵刚 MRZG
//[#01-05] 作者单位：
//[#01-06] 当前版本：v3.2
//[#01-07] 历史版本：v1.0, v1.1, v1.2, v2.0, v2.1, v2.2, v2.3, v2.4, v2.5, v3.0, v3.1
//[#01-08] 程序行数：
//[#01-09] 文件尺寸：
//[#01-10] 其他说明：提供类似INI用法的API
//[#01-11] 文本LOGO：-=MYLOGO=-
//[#01-12] 版权声明：
//[#01-!!] 说明结束
///////////////////////////////////////////////////////////////////////////////
/**
 * @file ConfigXML.h
 * @brief 用于支持XML格式的配置文件
 * @date 2015.08.10
 * @author 赵刚 MRZG
 * @version v3.2
*/
#pragma once
#ifndef _CONFIGXML_H_2006_02_03_13_14_45_R19073_
#define _CONFIGXML_H_2006_02_03_13_14_45_R19073_

#pragma warning( disable : 4018 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4305 )

///////////////////////////////文件包含////////////////////////////////////////
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <io.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <direct.h>
#include <vector>

///使用C++标准库
using namespace std;

////////////////////////////////宏定义/////////////////////////////////////////
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
//------------------------------类说明-----------------------------------------
//[#02-00] 本类名称：
//[#02-01] 本类功能：
//[#02-02] 内存消耗：
//[#02-03] 建立日期：
//[#02-04] 修改日期：
//[#02-05] 其他说明：
//[#02-!!] 说明结束
//-----------------------------------------------------------------------------
//------------------------------类结束-----------------------------------------

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：
//[#03-01] 函数功能：
//[#03-02] 参数说明：
//[#03-03] 返回说明：
//[#03-04] 建立日期：
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief @n
 *
 *  @b 说明: @n@n
 *  @b 注意: @n
 *
 *  @param
 *  @param
 *  @return
 *  @see
 *
 *  @b 实例:
    @code
    @endcode
*/
//-----------------------------函数结束----------------------------------------

//-----------------------------结构说明----------------------------------------
//[#04-00] 结构名称：
//[#04-01] 结构功能：
//[#04-02] 内存消耗：
//[#04-03] 建立日期：
//[#04-04] 修改日期：
//[#04-05] 其他说明：
//[#04-!!] 说明结束
//-----------------------------------------------------------------------------
//-----------------------------结构结束----------------------------------------
class ConfigXML;
///////////////////////////////程序正文////////////////////////////////////////

/////////////////////////////内部函数开始//////////////////////////////////////
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
/////////////////////////////内部函数结束//////////////////////////////////////

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：SearchElemInXML
//[#03-01] 函数功能：搜索指定标签
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//[#03-03] 返回说明：void* 搜索结果返回
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果element不存在，返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 在指定的XML文件对象中搜索指定标签@n
 *
 *  @b 说明: 在指定的XML文件对象中搜索指定的标签（element），标签的表示用绝对@n
 *  路径方式，即从根标签开始一直到目的标签，中间用"\"或"/"符分割，标签的名称用@n
 *  字母开头，中间可以混合数字和字母，可以使用中文标签名，比如:@n
 *  element="地图/路径/名称"，则表示一个层次深度为3层的标签，标签名称为:"名称"@n
 *  一级父标签为:"路径"，二级父标签为:"地图"（根标签）。@n
 *  SearchElemInXML函数可以确定指定的XML文件中是否包含指定的标签，如果存在则返回@n
 *  该标签对象，用户可以对该标签对象进一步操作，否则返回NULL表示指定标签在指定@n
 *  XML文件中不存在。@n@n
 *  @b 注意: XML文件的格式有一定的限制，具体限制参见帮助首页。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @return TiXmlElement* 标签对象或NULL
 *  @see splitElement
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    TiXmlElement* element=(TiXmlElement*)SearchElemInXML(xml,"地图/路径/名称");
    if(!element)
        MessageBox(NULL,"指定标签不存在！","出错",MB_OK);
    else
    {
        对element对象进行操作...
    }
    @endcode
*/
_EXPORT_ENGINE void* SearchElemInXML(ConfigXML& xml, void* root, void* element);
_EXPORT_ENGINE void* SearchElemInXML(ConfigXML& xml, void* root, const char* element);
_EXPORT_ENGINE void* SearchElemInXML(ConfigXML& xml, void* root, const wchar_t* element);
_EXPORT_ENGINE void* SearchElemInXMLByAttr(ConfigXML& xml, void* root, const char* attribute, const char* content);
_EXPORT_ENGINE void* SearchElemInXMLByAttr(ConfigXML& xml, void* root, const wchar_t* attribute, const wchar_t* content);

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：SearchAttrInXML
//[#03-01] 函数功能：搜索指定标签的指定属性
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//[#03-03] 返回说明：void* 搜索结果返回
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果attribute不存在，返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 在指定的XML文档对象中搜索指定标签的指定属性@n
 *
 *  @b 说明: 在指定的XML文件对象中搜索指定的标签（element）的指定属性（attribute）@n
 *  标签的表示用绝对路径方式，即从根标签开始一直到目的标签，中间用"\"或"/"符分割，@n
 *  标签的名称用字母开头，中间可以混合数字和字母，可以使用中文标签名，比如:@n
 *  element="地图/路径/名称"，则表示一个层次深度为3层的标签，标签名称为:"名称"@n
 *  一级父标签为:"路径"，二级父标签为:"地图"（根标签），属性用字符串表示。@n
 *  SearchAttrInXML函数可以确定指定的XML文件中是否包含指定的标签，指定的标签中是否@n
 *  包含指定的属性，如果存在则返回该属性对象，用户可以对该属性对象进一步操作，@n
 *  否则返回NULL表示指定标签的指定属性在指定的XML文件中不存在。@n@n
 *  @b 注意: XML文件的格式有一定的限制，具体限制参见帮助首页。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @return TiXmlAttribute* 属性对象或NULL
 *  @see SearchElement
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    TiXmlAttribute* attribute=(TiXmlAttribute*)SearchAttrInXML(xml,"地图/路径/名称","类型");
    if(!attribute)
        MessageBox(NULL,"指定属性不存在！","出错",MB_OK);
    else
    {
        对attribute对象进行操作...
    }
    @endcode
*/
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, void* element, const char* attribute);
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, void* element, const wchar_t* attribute);
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, const char* element, const char* attribute);
_EXPORT_ENGINE void* SearchAttrInXML(ConfigXML& xml, const wchar_t* element, const wchar_t* attribute);

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：RemoveElemFromXML
//[#03-01] 函数功能：从XML文件中移除指定标签
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//[#03-03] 返回说明：bool 移除成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中移除指定标签@n
 *
 *  @b 说明: RemoveElemFromXML函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将其从指定的XML文件对象中移除并返回true表示@n
 *     移除成功，如果该标签不存在，则不做任何操作返回false表示标签不存在。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *           3) 被移除标签的所有子标签也会全部移除。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @return 移除成功返回true，指定标签不存在返回false
 *  @see SearchElement
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool removeok=RemoveElemFormXML(xml,"地图/路径/名称");
    if(removeok==true)
    {
        MessageBox(NULL,"指定标签成功移除！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定标签不存在！","出错",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool RemoveElemFromXML(ConfigXML& xml, void* root, void* element);
_EXPORT_ENGINE bool RemoveElemFromXML(ConfigXML& xml, void* root, const char* element);
_EXPORT_ENGINE bool RemoveElemFromXML(ConfigXML& xml, void* root, const wchar_t* element);

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteElemToXML
//[#03-01] 函数功能：将某element写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//[#03-03] 返回说明：
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的标签写入指定的XML文件对象中@n
 *
 *  @b 说明: WriteElemToXML函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则不做任何操作返回false表示标签已经存在，否则@n
 *     将指定标签写入指定XML文件对象中，如果该标签的父标签也不存在则递归调用本函数@n
 *     建立相应的父标签。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param bCheckRepeat=true 是否检测重复标签，不检测重复标签有可能写入重复标签，@n
 *                           除非用户已经能够确定标签不重复。
 *  @return TiXmlElement* 写入成功返回标签指针，失败返回NULL。
 *  @see SearchElement
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    TiXmlElement* pEle=WriteElemToXML(xml,"地图/路径/名称");
    if(pEle)
    {
        MessageBox(NULL,"指定标签写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定标签已经存在！","出错",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE void* WriteElemToXML(ConfigXML& xml, void* root, const char* element, bool bCheckRepeat=true);
_EXPORT_ENGINE void* WriteElemToXML(ConfigXML& xml, void* root, const wchar_t* element, bool bCheckRepeat=true);

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：RemoveAttrFromXML
//[#03-01] 函数功能：从XML文件中移除某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//[#03-03] 返回说明：bool 移除成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中移除指定标签的指定属性@n
 *
 *  @b 说明: RemoveAttrFromXML函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则将其从指定的XML文件对象中移除并返回true表示@n
 *     移除成功，如果该属性不存在，则不做任何操作返回false表示属性不存在。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @return 移除成功返回true，指定属性不存在返回false
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool removeok=RemoveAttrFormXML(xml,"地图/路径/名称","类型");
    if(removeok==true)
    {
        MessageBox(NULL,"指定属性成功移除！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性不存在！","出错",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, void* element, const char* attribute);
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, void* element, const wchar_t* attribute);
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, const char* element, const char* attribute);
_EXPORT_ENGINE bool RemoveAttrFromXML(ConfigXML& xml, const wchar_t* element, const wchar_t* attribute);

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_str
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   const char* value 属性值
//                   const char* defaul 缺省值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持字符串类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为字符串类型@n
 *
 *  @b 说明: WriteAttrToXML_str函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（字符串类型）
 *  @param defaul=NULL 缺省值（字符串类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_str(xml,"地图/路径/名称","类型","GIF");
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_str_ref
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   const char* value 属性值
//                   const char* defaul 缺省值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持字符串类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为字符串类型@n
 *
 *  @b 说明: WriteAttrToXML_str函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（字符串类型）
 *  @param defaul=NULL 缺省值（字符串类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_str(xml,"地图/路径/名称","类型","GIF");
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_int
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   int value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持整数类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为整数类型@n
 *
 *  @b 说明: WriteAttrToXML_int函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（整数类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"地图/路径/名称","数量",2);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_hex
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   long value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持十六进制类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为长整数类型@n
 *
 *  @b 说明: WriteAttrToXML_hex函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（长整数类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_hex(xml,"地图/路径/名称","数量",2);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_int64
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   __int64 value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持长整数类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为64位整数类型@n
 *
 *  @b 说明: WriteAttrToXML_int64函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（64位整数类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int64(xml,"地图/路径/名称","数量",2);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_bool
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   bool value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持长整数类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为布尔类型@n
 *
 *  @b 说明: WriteAttrToXML_bool函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（布尔类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"地图/路径/名称","地面",true);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_float
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   float value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持单精度浮点类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为单精度浮点类型@n
 *
 *  @b 说明: WriteAttrToXML_float函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（单精度浮点类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"地图/路径/名称","尺寸",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_double
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   double value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持双精度浮点类型
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为双精度浮点类型@n
 *
 *  @b 说明: WriteAttrToXML_double函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（双精度浮点类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"地图/路径/名称","尺寸",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_uuid
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   unsigned int* value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2008.8.30
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持uuid，由4个32位无符号数表示
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为双精度浮点类型@n
 *
 *  @b 说明: WriteAttrToXML_double函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（32位无符号整数型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"地图/路径/名称","尺寸",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_uuid_ref
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   unsigned int* value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2008.8.30
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持uuid，由4个32位无符号数表示
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为双精度浮点类型@n
 *
 *  @b 说明: WriteAttrToXML_double函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（32位无符号整数型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"地图/路径/名称","尺寸",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_uuid_str
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   unsigned int* value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2008.8.30
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持uuid，由4个32位无符号数表示
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为双精度浮点类型@n
 *
 *  @b 说明: WriteAttrToXML_double函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（32位无符号整数型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_int(xml,"地图/路径/名称","尺寸",128.0);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteAttrToXML_color
//[#03-01] 函数功能：将某attribute写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   int value 属性值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：支持颜色类型 0xffffffff
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将指定的属性写入指定的XML文件对象中，属性值为整数类型@n
 *
 *  @b 说明: WriteAttrToXML_color函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则将指定属性写入并返回true表示属性已经写入，否则@n
 *     先调用WriteElemToXML建立相应的标签，然后再写入属性，如果建立标签失败返回false。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param value 属性值（整数类型）
 *  @return 写入成功返回true，写入失败返回false
 *  @see WriteElemToXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool writeok=WriteAttrToXML_color(xml,"地图/路径/颜色","数值",0x00ffffff);
    if(writeok==true)
    {
        MessageBox(NULL,"指定属性写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定属性写入失败！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_str
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   const char* defaul 缺省值
//[#03-03] 返回说明：const char* 读出的信息（字符串类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为字符串类型@n
 *
 *  @b 说明: ReadAttrFromXML_str函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（字符串指针），否则返回NULL@n@n
 *  @b 注意: XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return const char* 读出的信息（字符串类型）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    const char* str=ReadAttrFromeXML_str(xml,"地图/路径/名称","类型","PNG");
    if(str)
    {
        MessageBox(NULL,str,"读出属性的内容",MB_OK);
    }
    else
    {
        MessageBox(NULL,"指定的属性不存在","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_str_ref
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   const char* defaul 缺省值
//[#03-03] 返回说明：const char* 读出的信息（字符串类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为字符串类型@n
 *
 *  @b 说明: ReadAttrFromXML_str函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（字符串指针），否则返回NULL@n@n
 *  @b 注意: XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return const char* 读出的信息（字符串类型）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    const char* str=ReadAttrFromeXML_str(xml,"地图/路径/名称","类型","PNG");
    if(str)
    {
        MessageBox(NULL,str,"读出属性的内容",MB_OK);
    }
    else
    {
        MessageBox(NULL,"指定的属性不存在","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_int
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   int defaul 缺省值
//[#03-03] 返回说明：int 读出的信息（整数类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为整数类型@n
 *
 *  @b 说明: ReadAttrFromXML_int函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（整数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return int 读出的信息（整数）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    int num=ReadAttrFromeXML_int(xml,"地图/路径/名称","数量",0);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_hex
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   int defaul 缺省值
//[#03-03] 返回说明：int 读出的信息（整数类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为整数类型@n
 *
 *  @b 说明: ReadAttrFromXML_hex函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（长整数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return int 读出的信息（整数）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    int num=ReadAttrFromeXML_hex(xml,"地图/路径/名称","数量",0);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_int64
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   __int64 defaul 缺省值
//[#03-03] 返回说明：__int64 读出的信息（64位整数类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为长整数类型@n
 *
 *  @b 说明: ReadAttrFromXML_int64函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（长整数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return __int64 读出的信息（64位整数）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    long num=ReadAttrFromeXML_long(xml,"地图/路径/名称","数量",0);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_bool
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   bool defaul 缺省值
//[#03-03] 返回说明：bool 读出的信息（布尔类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为布尔类型@n
 *
 *  @b 说明: ReadAttrFromXML_bool函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（布尔类型），否则返回false @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return bool 读出的信息（布尔类型）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool earth=ReadAttrFromeXML_bool(xml,"地图/路径/名称","地面",false);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_float
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   float defaul
//[#03-03] 返回说明：float 读出的信息（单精度浮点类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为单精度浮点类型@n
 *
 *  @b 说明: ReadAttrFromXML_float函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（单精度浮点数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return float 读出的信息（单精度浮点数）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    float size=ReadAttrFromeXML_float(xml,"地图/路径/名称","尺寸",256);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_double
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   double defaul 缺省值
//[#03-03] 返回说明：double 读出的信息（双精度浮点类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回0
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为双精度浮点类型@n
 *
 *  @b 说明: ReadAttrFromXML_float函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（双精度浮点数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return double读出的信息（双精度浮点数）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"地图/路径/名称","尺寸",256);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_uuid
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   unsigned int* value 值
//                   unsigned int* defaul 缺省值
//[#03-03] 返回说明：
//[#03-04] 建立日期：2008.8.30
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为双精度浮点类型@n
 *
 *  @b 说明: ReadAttrFromXML_float函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（双精度浮点数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"地图/路径/名称","尺寸",256);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_uuid_ref
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   unsigned int* value 值
//                   unsigned int* defaul 缺省值
//[#03-03] 返回说明：
//[#03-04] 建立日期：2008.8.30
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为双精度浮点类型@n
 *
 *  @b 说明: ReadAttrFromXML_float函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（双精度浮点数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"地图/路径/名称","尺寸",256);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_uuid_str
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   unsigned int* value 值
//                   unsigned int* defaul 缺省值
//[#03-03] 返回说明：
//[#03-04] 建立日期：2008.8.30
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为双精度浮点类型@n
 *
 *  @b 说明: ReadAttrFromXML_float函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（双精度浮点数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    double size=ReadAttrFromeXML_double(xml,"地图/路径/名称","尺寸",256);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadAttrFromXML_color
//[#03-01] 函数功能：读取某attribute
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* attribute 指定属性
//                   int defaul 缺省值
//[#03-03] 返回说明：unsigned int 读出的信息（整数类型）
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该attribute则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的指定属性，属性值为整数类型@n
 *
 *  @b 说明: ReadAttrFromXML_int函数在指定的XML文件对象中调用SearchAttribute函数搜索@n
 *     指定的属性对象，如果该属性存在则读出该属性的值返回（整数），否则返回0 @n@n
 *  @b 注意: @n
 *          1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *          2) 如果指定属性对象不存在函数也可能返回一个合理的值。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param attribute 指定属性
 *  @param defaul 缺省值
 *  @return int 读出的信息（整数）
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    unsigned int color=ReadAttrFromeXML_int(xml,"地图/路径/颜色","数值",0x00ffffff);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：RemoveTextFromXML
//[#03-01] 函数功能：从XML文件中移除某Text
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//[#03-03] 返回说明：bool 移除成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中移除指定标签的文本@n
 *
 *  @b 说明: RemoveTextFromXML函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签，如果该标签存在则将其文本从指定的XML文件对象中移除并返回true表示@n
 *     移除成功，如果该标签不存在，则不做任何操作返回false表示标签不存在。如果指定@n
 *     标签不存在文本，则不做任何操作返回false表示标签文本不存在。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @return 移除成功返回true，指定标签不存在或指定标签不存在文本返回false
 *  @see SearchAttribute
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    bool removeok=RemoveTextFormXML(xml,"地图/路径/名称");
    if(removeok==true)
    {
        MessageBox(NULL,"指定标签的文本成功移除！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定文本不存在！","出错",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE bool RemoveTextFromXML(ConfigXML& xml, const char* element);
_EXPORT_ENGINE bool RemoveTextFromXML(ConfigXML& xml, const wchar_t* element);
_EXPORT_ENGINE bool RemoveTextFromXML(ConfigXML& xml, void* element);

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteTextToXML
//[#03-01] 函数功能：将某Text写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* text 文本
//                   const char* defaul 缺省值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将文本写入指定的XML文件对象中的指定标签@n
 *
 *  @b 说明: WriteTextToXML函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则先调用RemoveTextFromXML函数将该标签原先的@n
 *     文本移除，再将指定文本写入该标签并返回true表示写入成功，否则返回false表示@n
 *     指定的标签不存在。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param text 标签文本
 *  @param defaul 缺省值
 *  @return TiXmlText* 写入成功返回标签文本指针，失败返回NULL。
 *  @see SearchElement, RemoveTextFromXML
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    TiXmlText* pTxt=WriteTextToXML(xml,"地图/路径/名称","地图的图像文件名称");
    if(pTxt)
    {
        MessageBox(NULL,"指定标签的文本写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"指定标签不存在！","出错",MB_OK);
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

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：ReadTextFromXML
//[#03-01] 函数功能：读取某Text
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* element 指定标签
//                   const char* defaul 缺省值
//[#03-03] 返回说明：const char* 读出的信息
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：如果没有该Text则返回NULL
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 从指定的XML文件对象中读取指定标签的文本@n
 *
 *  @b 说明: ReadAttrFromXML_str函数在指定的XML文件对象中调用SearchElement函数搜索@n
 *     指定的标签对象，如果该标签存在则读出该标签的文本返回（字符串指针），否则返回NULL@n@n
 *  @b 注意: XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *
 *  @param xml XML文件对象
 *  @param element 指定标签
 *  @param defaul 缺省值
 *  @return const char* 读出的信息（字符串类型）
 *  @see SearchElement
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    const char* str=ReadTextFromeXML(xml,"地图/路径/名称");
    if(str)
    {
        MessageBox(NULL,str,"读出文本的内容",MB_OK);
    }
    else
    {
        MessageBox(NULL,"指定的标签不存在","出错",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE const char* ReadTextFromXML(ConfigXML& xml,	const char* element, const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadTextFromXML(ConfigXML& xml, const wchar_t* element, const wchar_t* defaul=NULL);
_EXPORT_ENGINE const char* ReadTextFromXML(ConfigXML& xml, void* element, const char* defaul=NULL);
_EXPORT_ENGINE const wchar_t* ReadTextFromXML(ConfigXML& xml, void* element, const wchar_t* defaul=NULL);

//-----------------------------函数说明----------------------------------------
//[#03-00] 函数名称：WriteCommentToXML
//[#03-01] 函数功能：将某Comment（注释）写入XML文件中
//[#03-02] 参数说明：ConfigXML& xml XML文件对象
//                   const char* comment 指定注释
//                   const char* defaul 缺省值
//[#03-03] 返回说明：bool 写入成功返回true，否则false
//[#03-04] 建立日期：2006.2.1
//[#03-05] 修改日期：
//[#03-06] 执行时间：
//[#03-07] 内存消耗：
//[#03-08] 函数行数：
//[#03-09] 其他说明：
//[#03-10] 应用实例：
//[#03-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 将注释写入指定的XML文件对象中的指定标签@n
 *
 *  @b 说明: WriteCommentToXML函数将指定注释写入XML对象中。@n@n
 *  @b 注意: @n
 *           1) XML文件的格式有一定的限制，具体限制参见帮助首页;@n
 *           2) 要真正改变磁盘中的XML文件内容还需要执行xml.SaveFile()@n
 *              （如果XML对象指定自动存储属性，则在XML销毁时程序会自动执行存盘功能），@n
 *              否则只是影响到内存中的XML文件对象。@n
 *
 *  @param xml XML文件对象
 *  @param comment 指定注释
 *  @param defaul 缺省值
 *  @return TiXmlComment* 写入成功返回注释指针，失败返回NULL。
 *  @see SearchElement
 *
 *  @b 实例:
    @code
    ConfigXML xml("Config.xml");
    TiXmlComment* pComment=WriteCommentToXML(xml,"地图的图像文件名称");
    if(pComment)
    {
        MessageBox(NULL,"指定注释写入成功！","成功",MB_OK);
        xml.SaveFile(); //如果要保存结果，执行该函数（或自动保存）
    }
    else
    {
        MessageBox(NULL,"写入注释失败！","出错",MB_OK);
    }
    @endcode
*/
_EXPORT_ENGINE void* WriteCommentToXML(ConfigXML& xml, const char* comment, const char* defaul=NULL);
_EXPORT_ENGINE void* WriteCommentToXML(ConfigXML& xml, const wchar_t* comment, const wchar_t* defaul=NULL);

//-----------------------------结构说明----------------------------------------
//[#04-00] 结构名称：ConfigXML
//[#04-01] 结构功能：配置文件对象
//[#04-02] 内存消耗：
//[#04-03] 建立日期：2006.6.21
//[#04-04] 修改日期：
//[#04-05] 其他说明：
//[#04-!!] 说明结束
//-----------------------------------------------------------------------------
/** @brief 配置文件对象
 * 
 * @b 说明: 用于操控配置文件，相当于文件句柄。@n
*/
class _EXPORT_ENGINE ConfigXML
{
public:
	enum eCreateType ///对象创建类型
	{
		ECT_READ   =0, ///读取
		ECT_WRITE  =1, ///写入
		ECT_MODIFY =2, ///修改
	};
	int m_nVersion;           ///<文档版本（程序版本）
	int m_nFormat;            ///<文档格式（数据版本）
	//int m_nLength;          ///<文件长度（字节）
	bool m_bOK;               ///<是否初始化成功
	bool m_bDoNotSave;        ///<是否放弃保存文档
	bool m_bLowPrecision;     ///<是否低浮点精度（正常6位，低3位）
	bool m_bFixLengthUUID;    ///<是否UUID类型固定长度（8*4+3=35位）
	eCreateType m_iType;      ///<类型（0,读取,1写入,2修改）
	char m_chFile[MAX_PATH];  ///<文件名（包含路径）
    wchar_t m_wch[1024];      ///<宽字符缓存
	int m_nRefCodeUUID;       ///<uuid引用编号
	int m_nRefCodeString;     ///<string引用编号
	void* m_pRefUUID;         ///<uuid引用节点
	void* m_pRefString;       ///<string引用节点
	void* m_lastElement;      ///<上次处理的element对象
	TiXmlElement* m_rootElement; ///<根element对象
	TiXmlDocument* m_pDoc;    ///<tinyXML文档对象

	void* m_cacheRoot[2];
	void* m_cacheElem;
	char  m_cacheName[MAX_PATH];
	void* m_cacheResultP;
	void* m_cacheResultA;
	int m_cacheNum;
	int m_shootNum;

public:
	ConfigXML()               ///<空构造函数，无用
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
	ConfigXML(const char* p_chName, eCreateType p_iType=ECT_READ, int p_nFormat=CONFIGXML_FORMAT) ///<带参数构造函数
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
	ConfigXML(const wchar_t* p_chName, eCreateType p_iType=ECT_READ, int p_nFormat=CONFIGXML_FORMAT) ///<带参数构造函数
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
	virtual ~ConfigXML() ///<析构函数
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
	bool SaveFile() ///<手动保存文件函数
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
	bool SaveAs(const char* p_chName) ///<另存为函数
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
	bool SaveAs(const wchar_t* p_chName) ///<另存为函数
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
//-----------------------------结构结束----------------------------------------

#endif //_CONFIGXML_H_2006_02_03_13_14_45_R19073_
//-----------------------------------------------------------------------------
///////////////////////////////文件结束////////////////////////////////////////