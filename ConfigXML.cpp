/////////////////////////////�����ļ�˵��//////////////////////////////////////
//[#01-00] �ļ����ƣ�ConfigXML.cpp
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
 * @file ConfigXML.cpp
 * @brief ����֧��XML��ʽ�������ļ�
 * @date 2015.08.10
 * @author �Ը� MRZG
 * @version v3.2
*/
///////////////////////////////�ļ�����////////////////////////////////////////
#include "ConfigXML.h"

///////////////////////////////��������////////////////////////////////////////

/////////////////////////////ȫ�ֱ�������//////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
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
//-----------------------------��������----------------------------------------

///////////////////////////////��������////////////////////////////////////////

/////////////////////////////�ڲ�������ʼ//////////////////////////////////////
//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�splitIP
//[#03-01] �������ܣ����ַ�������"."�ָ���ָ�
//[#03-02] ����˵����const char* ip �ַ���
//                   vector<std::string>* sv �ַ�������
//[#03-03] ����˵����unsigned int �ַ����ָ��ĸ���
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
extern unsigned int splitIP(const char* ip, vector<std::string>* sv=NULL)
{
    if(!ip) return 0;

    std::string str;
    unsigned int num=0,i,len;

    len=strlen(ip);
    if(len==0) return 0;

    if(sv) sv->clear();

    for(i=0; i<len; i++)
    {
        if(ip[i]!='.')
        {
            str+=ip[i];
        }
        else if(str.length()>0)
        {
            if(sv) sv->push_back(str);
            str.clear();
            num++;
        }
    }
    if(str.length()>0)
    {
        if(sv) sv->push_back(str);
        str.clear();
        num++;
    }

    return num;
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�splitElement
//[#03-01] �������ܣ����ַ�������"\"��/"�ָ���ָ�
//[#03-02] ����˵����const char* element �ַ���
//                   vector<std::string>* sv �ַ�������
//[#03-03] ����˵����unsigned int �ַ����ָ��ĸ���
//[#03-04] �������ڣ�2006.1.31
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵��������">"��"<"�ַ�
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
extern unsigned int splitElement(const char* element, vector<std::string>* sv=NULL)
{
    if(!element) return 0;

    std::string str;
    unsigned int num=0,i,len;

    len=strlen(element);
    if(len==0) return 0;

    if(sv) sv->clear();

    for(i=0; i<len; i++)
    {
        if(element[i]!='\\'&&element[i]!='/')
        {
            if(element[i]!='>'&&element[i]!='<')
                str+=element[i];
        }
        else if(str.length()>0)
        {
            if(sv) sv->push_back(str);
            str.clear();
            num++;
        }
    }
    if(str.length()>0)
    {
        if(sv) sv->push_back(str);
        str.clear();
        num++;
    }

    return num;
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�parentElement
//[#03-01] �������ܣ�ȥ�����һ�����ַ�������ø��ַ���
//[#03-02] ����˵����const char* element �ַ���
//[#03-03] ����˵����unsigned int ���ַ�������
//[#03-04] �������ڣ�2006.1.31
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�����ָ��Ϊ"/"��"\"������">"��"<"�ַ�
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
extern unsigned int parentElement(char* element)
{
    if(!element) return 0;

    bool ready=false;
    unsigned int num=0,i,len;

    len=strlen(element);
    if(len==0) return 0;

    for(i=len; i>0; i--)
    {
        if(element[i-1]!='\\'&&element[i-1]!='/')
        {
            if(element[i-1]!='>'&&element[i-1]!='<')
                 ready=true;
            element[i-1]=0x0;
        }
        else if(ready)
        {
            element[i-1]=0x0;
            i--;
            while((element[i-1]=='\\'
                 ||element[i-1]=='/'
                 ||element[i-1]=='>'
                 ||element[i-1]=='<')
                 &&i>0)
            {
                element[i-1]=0x0;
                i--;
            }
            return strlen(element);
        }
    }

    return strlen(element);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�childElement
//[#03-01] �������ܣ�������һ�����ַ���
//[#03-02] ����˵����const char* element �ַ���
//[#03-03] ����˵����unsigned int ���ַ�������
//[#03-04] �������ڣ�2006.1.31
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�����ָ��Ϊ"/"��"\"������">"��"<"�ַ�
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
extern unsigned int childElement(char* element)
{
    if(!element) return 0;

    bool ready=false;
    unsigned int num=0,i,len;

    len=strlen(element);
    if(len==0) return 0;

    std::string s;
    for(i=len; i>0; i--)
    {
        if(element[i-1]!='\\'&&element[i-1]!='/')
        {
            if(element[i-1]!='>'&&element[i-1]!='<')
                s.insert(s.begin(), element[i-1]);
        }
        else if(s.size()>0)
        {
            strcpy(element, s.c_str());
            return strlen(element);
        }
    }

    return strlen(element);
}
//-----------------------------��������----------------------------------------
/////////////////////////////�ڲ���������//////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�SearchElemInXML
//[#03-01] �������ܣ�����ĳelement
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   void* root �������
//                   const char* element �ַ���
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
void* SearchElemInXML(ConfigXML& xml, void* root, void* element)
{
	if(!element) return NULL;

	xml.m_cacheNum++;
	if(xml.m_cacheResultP
		&&xml.m_cacheRoot[0]==root
		&&xml.m_cacheElem==element)
	{
		xml.m_shootNum++;
		return xml.m_cacheResultP;
	}

	TiXmlElement* child;
	if(root)
		child=((TiXmlElement*)root)->FirstChildElement();
	else child=xml.m_rootElement->FirstChildElement();
	while(child)
	{
		if(child==element)
		{
			xml.m_cacheRoot[0]=root;
			xml.m_cacheElem=element;
			xml.m_cacheResultP=element;
			xml.m_lastElement=element;
			return element;
		}
		if(SearchElemInXML(xml,child,element))
			return element;
		child=child->NextSiblingElement();
	}
	return NULL;
}
void* SearchElemInXML(ConfigXML& xml, void* root, const char* element)
{
	if(!element) return NULL;

	xml.m_cacheNum++;
	if(xml.m_cacheResultA
		&&xml.m_cacheRoot[1]==root
		&&!strcmp(xml.m_cacheName,element))
	{
		xml.m_shootNum++;
		return xml.m_cacheResultA;
	}

    unsigned int num,i;
    vector<std::string> vs;
    num=splitElement(element,&vs);
    if(num==0) return NULL;

	TiXmlElement* child;
	if(root)
		child=((TiXmlElement*)root)->FirstChildElement(vs[0].c_str());
	else child=xml.m_rootElement->FirstChildElement(vs[0].c_str());
	if(!child) return NULL;

    for(i=1; i<num; i++)
    {
        child=child->FirstChildElement(vs[i].c_str());
        if(!child) return NULL;
    }

	if(child)
	{
		xml.m_cacheRoot[1]=root;
		strcpy(xml.m_cacheName,element);
		xml.m_cacheResultA=child;
		xml.m_lastElement=child;
	}
    return child;
}
void* SearchElemInXML(ConfigXML& xml, void* root, const wchar_t* element)
{
	if(!element) return NULL;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch,CONFIGXML_MAX_ELEM);
	return SearchElemInXML(xml,root,ch);
}
void* SearchElemInXMLByAttr(ConfigXML& xml, void* root, const char* attribute, const char* content)
{
	if(!attribute||!content) return NULL;

	vector<TiXmlElement*> list;
	TiXmlElement* child;
	if(root) child=((TiXmlElement*)root)->FirstChildElement();
	else child=xml.m_rootElement->FirstChildElement();
	while(child)
	{
		list.push_back(child);
		child=child->NextSiblingElement();
	}

	vector<TiXmlElement*>::iterator it=list.begin();
	for(; it!=list.end(); it++)
	if(!strcmp(ReadAttrFromXML_str(xml,(*it),attribute,""),content))
	{
		xml.m_lastElement=*it;
		return *it;
	}
	return NULL;
}
void* SearchElemInXMLByAttr(ConfigXML& xml, void* root, const wchar_t* attribute, const wchar_t* content)
{
	if(!attribute||!content) return NULL;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(content,ch2,CONFIGXML_MAX_ELEM);
	return SearchElemInXMLByAttr(xml,root,ch1,ch2);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�SearchAttrInXML
//[#03-01] �������ܣ�����ĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
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
void* SearchAttrInXML(ConfigXML& xml, const char* element, const char* attribute)
{
    if(!element||!attribute) return NULL;

    TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,NULL,element);
    if(!ele) return NULL;

    std::string s;
    TiXmlAttribute* attr=ele->FirstAttribute();
    while(attr)
    {
        s=attr->Name();
        if(!strcmp(s.c_str(),attribute))
            return attr;
        attr=attr->Next();
    }
    return NULL;
}
void* SearchAttrInXML(ConfigXML& xml, const wchar_t* element, const wchar_t* attribute)
{
	if(!element||!attribute) return NULL;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return SearchAttrInXML(xml,ch1,ch2);
}
void* SearchAttrInXML(ConfigXML& xml, void* element, const char* attribute)
{
	if(!element||!attribute) return NULL;

	std::string s;
    TiXmlAttribute* attr=((TiXmlElement*)element)->FirstAttribute();
    while(attr)
    {
        s=attr->Name();
        if(!strcmp(s.c_str(),attribute))
            return attr;
        attr=attr->Next();
    }
	return NULL;
}
void* SearchAttrInXML(ConfigXML& xml, void* element, const wchar_t* attribute)
{
	if(!element||!attribute) return NULL;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return SearchAttrInXML(xml,element,ch);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�RemoveElemFromXML
//[#03-01] �������ܣ���XML�ļ����Ƴ�ĳelement
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
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
bool RemoveElemFromXML(ConfigXML& xml, void* root, void* element)
{
    TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,root,element);
	if(!ele) return false;

	xml.ClearCache();
	return ele->Parent()->RemoveChild(ele);
}
bool RemoveElemFromXML(ConfigXML& xml, void* root, const char* element)
{
	TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,root,element);
	if(!ele) return false;

	xml.ClearCache();
	return ele->Parent()->RemoveChild(ele);
}
bool RemoveElemFromXML(ConfigXML& xml, void* root, const wchar_t* element)
{
	if(!element) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch,CONFIGXML_MAX_ELEM);
	return RemoveElemFromXML(xml,root,element);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteElemToXML
//[#03-01] �������ܣ���ĳelementд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
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
void* WriteElemToXML(ConfigXML& xml, void* root, const char* element, bool bCheckRepeat)
{
	if(!element) return NULL;

    TiXmlElement* ele=NULL;
	if(bCheckRepeat)
	{
		ele=(TiXmlElement*)SearchElemInXML(xml,root,element);
		if(ele) return ele;
	}

    unsigned int len=strlen(element);
    char* parent=new char[len+1];
    strcpy(parent,element);
    char* childs=new char[len+1];
    strcpy(childs,element);
    parentElement(parent);
    childElement(childs);
    if(strlen(childs)==0) return NULL;

    if(strlen(parent)>0)
    {
        ele=(TiXmlElement*)SearchElemInXML(xml,root,parent);
        if(!ele) ele=(TiXmlElement*)WriteElemToXML(xml,root,parent,false);
        if(!ele) return NULL;
    }
    TiXmlElement* e=new TiXmlElement(childs);
	if(!e) return NULL;
	TiXmlElement* ret;
	TiXmlNode* node;
    if(strlen(parent)>0)
        node=ele->LinkEndChild(e);
    else if(root)
		node=((TiXmlElement*)root)->LinkEndChild(e);
	else node=xml.m_rootElement->LinkEndChild(e);

	if(node)
		ret=node->ToElement();
	else ret=NULL;

    delete[] parent;
    delete[] childs;
    return ret;
}
void* WriteElemToXML(ConfigXML& xml, void* root, const wchar_t* element, bool bCheckRepeat)
{
	if(!element) return NULL;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch,CONFIGXML_MAX_ELEM);
	return WriteElemToXML(xml,root,ch,bCheckRepeat);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�RemoveAttrFromXML
//[#03-01] �������ܣ���XML�ļ����Ƴ�ĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
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
bool RemoveAttrFromXML(ConfigXML& xml, void* element, const char* attribute)
{
	if(!element||!attribute) return false;

    TiXmlAttribute* attr=(TiXmlAttribute*)SearchAttrInXML(xml,element,attribute);
    if(!attr) return false;

    ((TiXmlElement*)element)->RemoveAttribute(attribute);
    return true;
}
bool RemoveAttrFromXML(ConfigXML& xml, void* element, const wchar_t* attribute)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return RemoveAttrFromXML(xml,element,ch);
}
bool RemoveAttrFromXML(ConfigXML& xml, const char* element, const char* attribute)
{
    if(!element||!attribute) return false;

    TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,NULL,element);
    if(ele)
    {
        TiXmlAttribute* attr=(TiXmlAttribute*)SearchAttrInXML(xml,element,attribute);
        if(!attr) return false;

        ele->RemoveAttribute(attribute);
        return true;
    }
    return false;
}
bool RemoveAttrFromXML(ConfigXML& xml, const wchar_t* element, const wchar_t* attribute)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return RemoveAttrFromXML(xml,ch1,ch2);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_str
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   const char* value ֵ
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
bool WriteAttrToXML_str(ConfigXML& xml,
                        const char* element,
                        const char* attribute,
                        const char* value,
					    const char* defaul)
{
    if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;

    TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,NULL,element);
    if(!ele)
        ele=(TiXmlElement*)WriteElemToXML(xml,NULL,element,false);

    if(ele)
    {
		if(!value)
            ele->SetAttribute(attribute,defaul);
		else ele->SetAttribute(attribute,value);
        return true;
    }
    return false;
}
bool WriteAttrToXML_str(ConfigXML& xml,
                        const wchar_t* element,
                        const wchar_t* attribute,
                        const wchar_t* value,
					    const wchar_t* defaul)
{
	if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	char ch3[CONFIGXML_MAX_VALUE];
	char ch4[CONFIGXML_MAX_VALUE];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	if(value)
	    ConfigXML_UnicodeToAnsi(value,ch3,CONFIGXML_MAX_VALUE);
	else ch3[0]=0;
	if(defaul)
		ConfigXML_UnicodeToAnsi(defaul,ch4,CONFIGXML_MAX_VALUE);
	else ch4[0]=0;
	return WriteAttrToXML_str(xml,ch1,ch2,ch3,ch4);
}
bool WriteAttrToXML_str(ConfigXML& xml,
                        void* element,
                        const char* attribute,
                        const char* value,
					    const char* defaul)
{
	if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;

	if(!value)
        ((TiXmlElement*)element)->SetAttribute(attribute,defaul);
	else ((TiXmlElement*)element)->SetAttribute(attribute,value);
    return true;
}
bool WriteAttrToXML_str(ConfigXML& xml,
                        void* element,
                        const wchar_t* attribute,
                        const wchar_t* value,
					    const wchar_t* defaul)
{
	if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	char ch3[CONFIGXML_MAX_VALUE];
	ConfigXML_UnicodeToAnsi(attribute,ch1,CONFIGXML_MAX_ELEM);
	if(value)
	    ConfigXML_UnicodeToAnsi(value,ch2,CONFIGXML_MAX_VALUE);
	else ch2[0]=0;
	if(defaul)
	    ConfigXML_UnicodeToAnsi(defaul,ch3,CONFIGXML_MAX_VALUE);
	else ch3[0]=0;
	return WriteAttrToXML_str(xml,element,ch1,ch2,ch3);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_str_ref
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   const char* value ֵ
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
bool WriteAttrToXML_str_ref(ConfigXML& xml,
                            const char* element,
                            const char* attribute,
                            const char* value,
					        const char* defaul)
{
    if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;
	if(!value&&defaul) value=defaul;
	if(strlen(value)==0)
		return WriteAttrToXML_str(xml,element,attribute,value);

    int code=xml.Grab_String_Ref(value);
	if(code==0) return false;
	WriteAttrToXML_int(xml,element,attribute,code);
	return true;
}
bool WriteAttrToXML_str_ref(ConfigXML& xml,
                            const wchar_t* element,
                            const wchar_t* attribute,
                            const wchar_t* value,
					        const wchar_t* defaul)
{
	if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	char ch3[CONFIGXML_MAX_VALUE];
	char ch4[CONFIGXML_MAX_VALUE];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	if(value)
	    ConfigXML_UnicodeToAnsi(value,ch3,CONFIGXML_MAX_VALUE);
	else ch3[0]=0;
	if(defaul)
		ConfigXML_UnicodeToAnsi(defaul,ch4,CONFIGXML_MAX_VALUE);
	else ch4[0]=0;
	return WriteAttrToXML_str_ref(xml,ch1,ch2,ch3,ch4);
}
bool WriteAttrToXML_str_ref(ConfigXML& xml,
                            void* element,
                            const char* attribute,
                            const char* value,
					        const char* defaul)
{
	if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;
	if(!value&&defaul) value=defaul;
	if(strlen(value)==0)
		return WriteAttrToXML_str(xml,element,attribute,value);

	int code=xml.Grab_String_Ref(value);
	if(code==0) return false;
	WriteAttrToXML_int(xml,element,attribute,code);
	return true;
}
bool WriteAttrToXML_str_ref(ConfigXML& xml,
                            void* element,
                            const wchar_t* attribute,
                            const wchar_t* value,
					        const wchar_t* defaul)
{
	if(!element||!attribute) return false;
 	if(!value&&!defaul) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	char ch3[CONFIGXML_MAX_VALUE];
	ConfigXML_UnicodeToAnsi(attribute,ch1,CONFIGXML_MAX_ELEM);
	if(value)
	    ConfigXML_UnicodeToAnsi(value,ch2,CONFIGXML_MAX_VALUE);
	else ch2[0]=0;
	if(defaul)
	    ConfigXML_UnicodeToAnsi(defaul,ch3,CONFIGXML_MAX_VALUE);
	else ch3[0]=0;
	return WriteAttrToXML_str_ref(xml,element,ch1,ch2,ch3);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_int
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   int value ֵ
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
bool WriteAttrToXML_int(ConfigXML& xml,
                        const char* element,
                        const char* attribute,
                        int value)
{
	if(!element||!attribute) return false;

    char str[16];
    sprintf(str,"%d",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_int(ConfigXML& xml,
                        const wchar_t* element,
                        const wchar_t* attribute,
                        int value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int(xml,ch1,ch2,value);
}
bool WriteAttrToXML_int(ConfigXML& xml,
                        void* element,
                        const char* attribute,
                        int value)
{
	if(!element||!attribute) return false;

	char str[16];
    sprintf(str,"%d",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_int(ConfigXML& xml,
                        void* element,
                        const wchar_t* attribute,
                        int value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int(xml,element,ch,value);
}
bool WriteAttrToXML_int_n(ConfigXML& xml,
                          const char* element,
                          const char* attribute,
                          const int* value,
					 	  int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char str[128];

	switch (n)
	{
	case 1:
		{
			sprintf(str,"%d",value[0]); break;
		}
	case 2:
		{
			if(value[0]==value[1])
			{
				sprintf(str,"a%d%d",n,value[0]);
			}
			else
			{
				sprintf(str,"%d/%d",value[0],value[1]);
			}
		    break;
		}
	case 3:
		{
            if(value[0]==value[1]&&value[0]==value[2])
			{
				sprintf(str,"a%d%d",n,value[0]);
			}
			else
			{
				sprintf(str,"%d/%d/%d",value[0],value[1],value[2]);
			}
		    break;
		}
	case 4:
        {
			if(value[0]==value[1]&&value[0]==value[2]&&value[0]==value[3])
			{
				sprintf(str,"a%d%d",n,value[0]);
			}
			else
			{
				sprintf(str,"%d/%d/%d/%d",value[0],value[1],value[2],value[3]);
			}
			break;
		}
	}
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_int_n(ConfigXML& xml,
                          const wchar_t* element,
                          const wchar_t* attribute,
                          const int* value,
						  int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int_n(xml,ch1,ch2,value,n);
}
bool WriteAttrToXML_int_n(ConfigXML& xml,
                          void* element,
                          const char* attribute,
                          const int* value,
						  int n)
{
    if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char str[128];

	switch (n)
	{
	case 1:
		{
			sprintf(str,"%d",value[0]); break;
		}
	case 2:
		{
			if(value[0]==value[1])
			{
				sprintf(str,"a%d%d",n,value[0]);
			}
			else
			{
				sprintf(str,"%d/%d",value[0],value[1]);
			}
		    break;
		}
	case 3:
		{
            if(value[0]==value[1]&&value[0]==value[2])
			{
				sprintf(str,"a%d%d",n,value[0]);
			}
			else
			{
				sprintf(str,"%d/%d/%d",value[0],value[1],value[2]);
			}
		    break;
		}
	case 4:
        {
			if(value[0]==value[1]&&value[0]==value[2]&&value[0]==value[3])
			{
				sprintf(str,"a%d%d",n,value[0]);
			}
			else
			{
				sprintf(str,"%d/%d/%d/%d",value[0],value[1],value[2],value[3]);
			}
			break;
		}
	}
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_int_n(ConfigXML& xml,
                          void* element,
                          const wchar_t* attribute,
                          const int* value,
						  int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int_n(xml,element,ch,value,n);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_hex
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   int value ֵ
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
bool WriteAttrToXML_hex(ConfigXML& xml,
                        const char* element,
                        const char* attribute,
                        int value)
{
	if(!element||!attribute) return false;

    char str[16];
    sprintf(str,"0x%x",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_hex(ConfigXML& xml,
                        const wchar_t* element,
                        const wchar_t* attribute,
                        int value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_hex(xml,ch1,ch2,value);
}
bool WriteAttrToXML_hex(ConfigXML& xml,
                        void* element,
                        const char* attribute,
                        int value)
{
	if(!element||!attribute) return false;

	char str[16];
    sprintf(str,"0x%x",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_hex(ConfigXML& xml,
                        void* element,
                        const wchar_t* attribute,
                        int value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_hex(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_int64
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   __int64 value ֵ
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
bool WriteAttrToXML_int64(ConfigXML& xml,
                          const char* element,
                          const char* attribute,
                          __int64 value)
{
	if(!element||!attribute) return false;

    char str[32];
    sprintf(str,"%I64d",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_int64(ConfigXML& xml,
                          const wchar_t* element,
                          const wchar_t* attribute,
                          __int64 value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int64(xml,ch1,ch2,value);
}
bool WriteAttrToXML_int64(ConfigXML& xml,
                          void* element,
                          const char* attribute,
                          __int64 value)
{
	if(!element||!attribute) return false;

	char str[32];
    sprintf(str,"%I64d",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_int64(ConfigXML& xml,
                          void* element,
                          const wchar_t* attribute,
						  __int64 value)
{
	if(!element||!attribute) return false;

    char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int64(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_bool
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   bool value ֵ
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
bool WriteAttrToXML_bool(ConfigXML& xml,
                         const char* element,
                         const char* attribute,
                         bool value)
{
	if(!element||!attribute) return false;

	char str[2]={'t',0};
    if(!value) str[0]='f';

    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_bool(ConfigXML& xml,
                         const wchar_t* element,
                         const wchar_t* attribute,
                         bool value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_bool(xml,ch1,ch2,value);
}
bool WriteAttrToXML_bool(ConfigXML& xml,
                         void* element,
                         const char* attribute,
                         bool value)
{
	if(!element||!attribute) return false;

	char str[2]={'t',0};
    if(!value) str[0]='f';

    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_bool(ConfigXML& xml,
                         void* element,
                         const wchar_t* attribute,
                         bool value)
{
	if(!element||!attribute) return false;

    char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_bool(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_float
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   float value ֵ
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
bool WriteAttrToXML_float(ConfigXML& xml,
                          const char* element,
                          const char* attribute,
                          float value)
{
	if(!element||!attribute) return false;

    char str[16];
	if(xml.m_bLowPrecision)
		ConfigXML_fast_ftoa(str,value,3);
    else ConfigXML_fast_ftoa(str,value,6);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_float(ConfigXML& xml,
                          const wchar_t* element,
                          const wchar_t* attribute,
                          float value)
{
	if(!element||!attribute) return false;

    char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_float(xml,ch1,ch2,value);
}
bool WriteAttrToXML_float(ConfigXML& xml,
                          void* element,
                          const char* attribute,
                          float value)
{
	if(!element||!attribute) return false;

	char str[16];
    if(xml.m_bLowPrecision)
		ConfigXML_fast_ftoa(str,value,3);
    else ConfigXML_fast_ftoa(str,value,6);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_float(ConfigXML& xml,
                          void* element,
                          const wchar_t* attribute,
						  float value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_float(xml,element,ch,value);
}
bool WriteAttrToXML_float_n(ConfigXML& xml,
                            const char* element,
                            const char* attribute,
                            const float* value,
							int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char sv[4][32];
	char str[128];
	int precision=6;
	if(xml.m_bLowPrecision)
        precision=3;

	switch (n)
	{
	case 1:
		{
		    ConfigXML_fast_ftoa(str,value[0],precision); break;
		}
	case 2:
		{
			if(ConfigXML_isFloatEqual(value,2,precision))
			{
                ConfigXML_fast_ftoa(sv[0],value[0],precision);
				sprintf(str,"a%d%s",n,sv[0]);
			}
			else
			{
				ConfigXML_fast_ftoa(sv[0],value[0],precision);
				ConfigXML_fast_ftoa(sv[1],value[1],precision);
				sprintf(str,"%s/%s",sv[0],sv[1]);
			}
		    break;
		}
	case 3:
		{
            if(ConfigXML_isFloatEqual(value,3,precision))
			{
                ConfigXML_fast_ftoa(sv[0],value[0],precision);
				sprintf(str,"a%d%s",n,sv[0]);
			}
			else
			{
				ConfigXML_fast_ftoa(sv[0],value[0],precision);
				ConfigXML_fast_ftoa(sv[1],value[1],precision);
				ConfigXML_fast_ftoa(sv[2],value[2],precision);
				sprintf(str,"%s/%s/%s",sv[0],sv[1],sv[2]);
			}
		    break;
		}
	case 4:
        {
			if(ConfigXML_isFloatEqual(value,4,precision))
			{
                ConfigXML_fast_ftoa(sv[0],value[0],precision);
				sprintf(str,"a%d%s",n,sv[0]);
			}
			else
			{
				ConfigXML_fast_ftoa(sv[0],value[0],precision);
				ConfigXML_fast_ftoa(sv[1],value[1],precision);
				ConfigXML_fast_ftoa(sv[2],value[2],precision);
				ConfigXML_fast_ftoa(sv[3],value[3],precision);
				sprintf(str,"%s/%s/%s/%s",sv[0],sv[1],sv[2],sv[3]);
			}
			break;
		}
	}
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_float_n(ConfigXML& xml,
                            const wchar_t* element,
                            const wchar_t* attribute,
                            const float* value,
							int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_float_n(xml,ch1,ch2,value,n);
}
bool WriteAttrToXML_float_n(ConfigXML& xml,
                            void* element,
                            const char* attribute,
                            const float* value,
							int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char sv[4][32];
	char str[128];
	int precision=6;
	if(xml.m_bLowPrecision)
        precision=3;

	switch (n)
	{
	case 1:
		{
		    ConfigXML_fast_ftoa(str,value[0],precision); break;
		}
	case 2:
		{
			if(ConfigXML_isFloatEqual(value,2,precision))
			{
                ConfigXML_fast_ftoa(sv[0],value[0],precision);
				sprintf(str,"a%d%s",n,sv[0]);
			}
			else
			{
				ConfigXML_fast_ftoa(sv[0],value[0],precision);
				ConfigXML_fast_ftoa(sv[1],value[1],precision);
				sprintf(str,"%s/%s",sv[0],sv[1]);
			}
		    break;
		}
	case 3:
		{
            if(ConfigXML_isFloatEqual(value,3,precision))
			{
                ConfigXML_fast_ftoa(sv[0],value[0],precision);
				sprintf(str,"a%d%s",n,sv[0]);
			}
			else
			{
				ConfigXML_fast_ftoa(sv[0],value[0],precision);
				ConfigXML_fast_ftoa(sv[1],value[1],precision);
				ConfigXML_fast_ftoa(sv[2],value[2],precision);
				sprintf(str,"%s/%s/%s",sv[0],sv[1],sv[2]);
			}
		    break;
		}
	case 4:
        {
			if(ConfigXML_isFloatEqual(value,4,precision))
			{
                ConfigXML_fast_ftoa(sv[0],value[0],precision);
				sprintf(str,"a%d%s",n,sv[0]);
			}
			else
			{
				ConfigXML_fast_ftoa(sv[0],value[0],precision);
				ConfigXML_fast_ftoa(sv[1],value[1],precision);
				ConfigXML_fast_ftoa(sv[2],value[2],precision);
				ConfigXML_fast_ftoa(sv[3],value[3],precision);
				sprintf(str,"%s/%s/%s/%s",sv[0],sv[1],sv[2],sv[3]);
			}
			break;
		}
	}
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_float_n(ConfigXML& xml,
                            void* element,
                            const wchar_t* attribute,
                            const float* value,
							int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_float_n(xml,element,ch,value,n);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_double
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   double value ֵ
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
bool WriteAttrToXML_double(ConfigXML& xml,
                           const char* element,
                           const char* attribute,
                           double value)
{
    if(!element||!attribute) return false;

    char str[32];
    sprintf(str,"%lf",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_double(ConfigXML& xml,
                           const wchar_t* element,
                           const wchar_t* attribute,
                           double value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_double(xml,ch1,ch2,value);
}
bool WriteAttrToXML_double(ConfigXML& xml,
                           void* element,
                           const char* attribute,
                           double value)
{
	if(!element||!attribute) return false;

    char str[32];
    sprintf(str,"%lf",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_double(ConfigXML& xml,
                           void* element,
                           const wchar_t* attribute,
                           double value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_double(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_uuid
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   unsigned int value ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
bool WriteAttrToXML_uuid(ConfigXML& xml,
                         const char* element,
                         const char* attribute,
                         const unsigned int* value)
{
    if(!element||!attribute) return false;

    char str[64];
	if(!value||(value[0]+value[1]+value[2]+value[3]==0))
	{
		str[0]='z';
	    str[1]=0;
	}
    else if(xml.m_bFixLengthUUID)
		sprintf(str,"%08x.%08x.%08x.%08x",value[0],value[1],value[2],value[3]);
	else sprintf(str,"%x.%x.%x.%x",value[0],value[1],value[2],value[3]);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_uuid(ConfigXML& xml,
                         const wchar_t* element,
                         const wchar_t* attribute,
                         const unsigned int* value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_uuid(xml,ch1,ch2,value);
}
bool WriteAttrToXML_uuid(ConfigXML& xml,
                         void* element,
                         const char* attribute,
                         const unsigned int* value)
{
	if(!element||!attribute) return false;

    char str[64];
	if(!value||(value[0]+value[1]+value[2]+value[3]==0))
	{
		str[0]='z';
	    str[1]=0;
	}
	else if(xml.m_bFixLengthUUID)
		sprintf(str,"%08x.%08x.%08x.%08x",value[0],value[1],value[2],value[3]);
    else sprintf(str,"%x.%x.%x.%x",value[0],value[1],value[2],value[3]);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_uuid(ConfigXML& xml,
                         void* element,
                         const wchar_t* attribute,
                         const unsigned int* value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_uuid(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_uuid_ref
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   unsigned int value ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
                             const char* element,
                             const char* attribute,
                             const unsigned int* value)
{
    if(!element||!attribute) return false;

	char str[16];
	if(!value||(value[0]+value[1]+value[2]+value[3]==0))
	{
		str[0]='z';
	    str[1]=0;
		return WriteAttrToXML_str(xml,element,attribute,str);
	}

	int code=xml.Grab_UUID_Ref(value);
	if(code==0) return false;
    sprintf(str,"r%d",code);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
                             const wchar_t* element,
                             const wchar_t* attribute,
                             const unsigned int* value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_uuid_ref(xml,ch1,ch2,value);
}
bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
                             void* element,
                             const char* attribute,
                             const unsigned int* value)
{
	if(!element||!attribute) return false;

	char str[16];
	if(!value||(value[0]+value[1]+value[2]+value[3]==0))
	{
		str[0]='z';
	    str[1]=0;
		return WriteAttrToXML_str(xml,element,attribute,str);
	}

    int code=xml.Grab_UUID_Ref(value);
	if(code==0) return false;
    sprintf(str,"r%d",code);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_uuid_ref(ConfigXML& xml,
                             void* element,
                             const wchar_t* attribute,
                             const unsigned int* value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_uuid_ref(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_uuid_str
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   unsigned char value ֵ
//[#03-03] ����˵����bool д��ɹ�����true������false
//[#03-04] �������ڣ�2008.8.30
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
bool WriteAttrToXML_uuid_str(ConfigXML& xml,
                             const char* element,
                             const char* attribute,
                             const unsigned char* value)
{
    if(!element||!attribute) return false;

    char str[64];
	sprintf(str,
		"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		value[0],
		value[1],
		value[2],
		value[3],
		value[4],
		value[5],
		value[6],
		value[7],
		value[8],
		value[9],
		value[10],
		value[11],
		value[12],
		value[13],
		value[14],
		value[15]);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_uuid_str(ConfigXML& xml,
                             const wchar_t* element,
                             const wchar_t* attribute,
                             const unsigned char* value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_uuid_str(xml,ch1,ch2,value);
}
bool WriteAttrToXML_uuid_str(ConfigXML& xml,
                             void* element,
                             const char* attribute,
                             const unsigned char* value)
{
	if(!element||!attribute) return false;

    char str[64];
	sprintf(str,
		"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		value[0],
		value[1],
		value[2],
		value[3],
		value[4],
		value[5],
		value[6],
		value[7],
		value[8],
		value[9],
		value[10],
		value[11],
		value[12],
		value[13],
		value[14],
		value[15]);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_uuid_str(ConfigXML& xml,
                             void* element,
                             const wchar_t* attribute,
                             const unsigned char* value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_uuid_str(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteAttrToXML_color
//[#03-01] �������ܣ���ĳattributeд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   unsigned int value ֵ
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
bool WriteAttrToXML_color(ConfigXML& xml,
						  const char* element,
						  const char* attribute,
						  unsigned int value)
{
	if(!element||!attribute) return false;

    char str[64];
    sprintf(str,"0x%08x",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_color(ConfigXML& xml,
                          const wchar_t* element,
                          const wchar_t* attribute,
                          unsigned int value)
{
	if(!element||!attribute) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int(xml,ch1,ch2,value);
}
bool WriteAttrToXML_color(ConfigXML& xml,
                          void* element,
                          const char* attribute,
                          unsigned int value)
{
	if(!element||!attribute) return false;

	char str[64];
    sprintf(str,"0x%08x",value);
    return WriteAttrToXML_str(xml,element,attribute,str);
}
bool WriteAttrToXML_color(ConfigXML& xml,
                          void* element,
                          const wchar_t* attribute,
                          unsigned int value)
{
	if(!element||!attribute) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return WriteAttrToXML_int(xml,element,ch,value);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_str
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����const char* ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
const char* ReadAttrFromXML_str(ConfigXML& xml,
                                const char* element,
                                const char* attribute,
							    const char* defaul)
{
    if(!element||!attribute) return defaul;

    TiXmlAttribute* attr=(TiXmlAttribute*)SearchAttrInXML(xml,element,attribute);
    if(!attr) return defaul;
 	return attr->Value();
}
const wchar_t* ReadAttrFromXML_str(ConfigXML& xml,
                                   const wchar_t* element,
                                   const wchar_t* attribute,
								   const wchar_t* defaul)
{
	if(!element||!attribute) return defaul;

    TiXmlAttribute* attr=(TiXmlAttribute*)SearchAttrInXML(xml,element,attribute);
    if(!attr) return defaul;

	ConfigXML_AnsiToUnicode(attr->Value(),xml.m_wch,CONFIGXML_MAX_VALUE);
	return xml.m_wch;
}
const char* ReadAttrFromXML_str(ConfigXML& xml,
                                void* element,
                                const char* attribute,
								const char* defaul)
{
	if(!element||!attribute) return defaul;

    TiXmlAttribute* attr=(TiXmlAttribute*)SearchAttrInXML(xml,element,attribute);
    if(!attr) return defaul;
    return attr->Value();
}
const wchar_t* ReadAttrFromXML_str(ConfigXML& xml,
                                   void* element,
                                   const wchar_t* attribute,
								   const wchar_t* defaul)
{
	if(!element||!attribute) return defaul;

    TiXmlAttribute* attr=(TiXmlAttribute*)SearchAttrInXML(xml,element,attribute);
    if(!attr) return defaul;

	ConfigXML_AnsiToUnicode(attr->Value(),xml.m_wch,CONFIGXML_MAX_VALUE);
	return xml.m_wch;
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_str_ref
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   const char* defaul ȱʡֵ
//[#03-03] ����˵����const char* ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
const char* ReadAttrFromXML_str_ref(ConfigXML& xml,
                                    const char* element,
                                    const char* attribute,
							        const char* defaul)
{
    if(!element||!attribute) return defaul;

	int code=ReadAttrFromXML_int(xml,element,attribute,-1);
	if(code==-1) return defaul;
	if(code>0)
		return xml.Read_String_Ref(code,defaul);
	return "";
}
const wchar_t* ReadAttrFromXML_str_ref(ConfigXML& xml,
                                       const wchar_t* element,
                                       const wchar_t* attribute,
								       const wchar_t* defaul)
{
	if(!element||!attribute) return defaul;

    int code=ReadAttrFromXML_int(xml,element,attribute,-1);
	if(code==-1) return defaul;
	if(code>0)
	{
		char ch[CONFIGXML_MAX_ELEM];
	    ConfigXML_UnicodeToAnsi(defaul,ch,CONFIGXML_MAX_ELEM);
		ConfigXML_AnsiToUnicode(xml.Read_String_Ref(code,ch),xml.m_wch,CONFIGXML_MAX_VALUE);
		return xml.m_wch;
	}
	return L"";
}
const char* ReadAttrFromXML_str_ref(ConfigXML& xml,
                                    void* element,
                                    const char* attribute,
								    const char* defaul)
{
	if(!element||!attribute) return defaul;

    int code=ReadAttrFromXML_int(xml,element,attribute,-1);
	if(code==-1) return defaul;
	if(code>0)
		return xml.Read_String_Ref(code,defaul);
	return "";
}
const wchar_t* ReadAttrFromXML_str_ref(ConfigXML& xml,
                                       void* element,
                                       const wchar_t* attribute,
								       const wchar_t* defaul)
{
	if(!element||!attribute) return defaul;

    int code=ReadAttrFromXML_int(xml,element,attribute,-1);
	if(code==-1) return defaul;
	if(code>0)
	{
		char ch[CONFIGXML_MAX_ELEM];
	    ConfigXML_UnicodeToAnsi(defaul,ch,CONFIGXML_MAX_ELEM);
		ConfigXML_AnsiToUnicode(xml.Read_String_Ref(code,ch),xml.m_wch,CONFIGXML_MAX_VALUE);
		return xml.m_wch;
	}
	return L"";
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_int
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   int defaul ȱʡֵ
//[#03-03] ����˵����int ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
int ReadAttrFromXML_int(ConfigXML& xml,
                        const char* element,
                        const char* attribute,
						int defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return atoi(str);
    return defaul;
}
int ReadAttrFromXML_int(ConfigXML& xml,
                        const wchar_t* element,
                        const wchar_t* attribute,
					    int defaul)
{
	if(!element||!attribute) return defaul;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int(xml,ch1,ch2,defaul);
}
int ReadAttrFromXML_int(ConfigXML& xml,
                        void* element,
                        const char* attribute,
					    int defaul)
{
	if(!element||!attribute) return defaul;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return atoi(str);
    return defaul;
}
int ReadAttrFromXML_int(ConfigXML& xml,
                        void* element,
                        const wchar_t* attribute,
					    int defaul)
{
	if(!element||!attribute) return defaul;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int(xml,element,ch,defaul);
}
bool ReadAttrFromXML_int_n(ConfigXML& xml,
                           const char* element,
                           const char* attribute,
						   int* value,
						   const int* defaul,
						   int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			for(int i=0; i<n; i++)
				value[i]=defaul[i];
		}
		else
		{
			for(int i=0; i<n; i++)
				value[i]=0;
		}

		return true;
	}
    else
	{
		if(str[0]=='a')
		{
			char sn[2]={str[1],0};
			int m=atoi(sn);
			int s=atoi(&(str[2]));
            for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=s;
				else if(defaul) value[i]=defaul[i];
			}
		}
		else
		{
			vector<std::string> sv;
			splitElement(str,&sv);
			int m=sv.size();
			for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=atoi(sv[i].c_str());
				else if(defaul) value[i]=defaul[i];
			}
		}

		return true;
	}
}
bool ReadAttrFromXML_int_n(ConfigXML& xml,
                           const wchar_t* element,
                           const wchar_t* attribute,
						   int* value,
						   const int* defaul,
						   int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int_n(xml,ch1,ch2,value,defaul,n);
}
bool ReadAttrFromXML_int_n(ConfigXML& xml,
                           void* element,
                           const char* attribute,
						   int* value,
						   const int* defaul,
						   int n)
{
    if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			for(int i=0; i<n; i++)
				value[i]=defaul[i];
		}
		else
		{
			for(int i=0; i<n; i++)
				value[i]=0;
		}

		return true;
	}
    else
	{
		if(str[0]=='a')
		{
			char sn[2]={str[1],0};
			int m=atoi(sn);
			int s=atoi(&(str[2]));
            for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=s;
				else if(defaul) value[i]=defaul[i];
			}
		}
		else
		{
			vector<std::string> sv;
			splitElement(str,&sv);
			int m=sv.size();
			for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=atoi(sv[i].c_str());
				else if(defaul) value[i]=defaul[i];
			}
		}

		return true;
	}
}
bool ReadAttrFromXML_int_n(ConfigXML& xml,
                           void* element,
                           const wchar_t* attribute,
						   int* value,
						   const int* defaul,
						   int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int_n(xml,element,ch,value,defaul,n);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_hex
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   int defaul ȱʡֵ
//[#03-03] ����˵����int ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
int ReadAttrFromXML_hex(ConfigXML& xml,
                        const char* element,
                        const char* attribute,
						int defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str)
	{
		int c;
		sscanf(str,"%x",&c);
		return c;
	}
    return defaul;
}
int ReadAttrFromXML_hex(ConfigXML& xml,
                        const wchar_t* element,
                        const wchar_t* attribute,
						int defaul)
{
	if(!element||!attribute) return defaul;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_hex(xml,ch1,ch2,defaul);
}
int ReadAttrFromXML_hex(ConfigXML& xml,
                        void* element,
                        const char* attribute,
						int defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str)
	{
		int c;
		sscanf(str,"%x",&c);
		return c;
	}
    return defaul;
}
int ReadAttrFromXML_hex(ConfigXML& xml,
                        void* element,
                        const wchar_t* attribute,
						int defaul)
{
	if(!element||!attribute) return defaul;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_hex(xml,element,ch,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_int64
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   __int64 defaul ȱʡֵ
//[#03-03] ����˵����long ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
__int64 ReadAttrFromXML_int64(ConfigXML& xml,
                              const char* element,
                              const char* attribute,
						      __int64 defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return _atoi64(str);
    return defaul;
}
__int64 ReadAttrFromXML_int64(ConfigXML& xml,
                              const wchar_t* element,
                              const wchar_t* attribute,
						      __int64 defaul)
{
	if(!element||!attribute) return defaul;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int64(xml,ch1,ch2,defaul);
}
__int64 ReadAttrFromXML_int64(ConfigXML& xml,
                              void* element,
                              const char* attribute,
						      __int64 defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return _atoi64(str);
    return defaul;
}
__int64 ReadAttrFromXML_int64(ConfigXML& xml,
                              void* element,
                              const wchar_t* attribute,
						      __int64 defaul)
{
	if(!element||!attribute) return defaul;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int64(xml,element,ch,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_bool
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   bool defaul ȱʡֵ
//[#03-03] ����˵����bool ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
bool ReadAttrFromXML_bool(ConfigXML& xml,
                          const char* element,
                          const char* attribute,
						  bool defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return str[0]=='t';
    return defaul;
}
bool ReadAttrFromXML_bool(ConfigXML& xml,
                          const wchar_t* element,
                          const wchar_t* attribute,
						  bool defaul)
{
	if(!element||!attribute) return defaul;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_bool(xml,ch1,ch2,defaul);
}
bool ReadAttrFromXML_bool(ConfigXML& xml,
                          void* element,
                          const char* attribute,
						  bool defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return str[0]=='t';
    return defaul;
}
bool ReadAttrFromXML_bool(ConfigXML& xml,
                          void* element,
                          const wchar_t* attribute,
						  bool defaul)
{
	if(!element||!attribute) return defaul;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_bool(xml,element,ch,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_float
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   float defaul ȱʡֵ
//[#03-03] ����˵����float ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
float ReadAttrFromXML_float(ConfigXML& xml,
                            const char* element,
                            const char* attribute,
						    float defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return ConfigXML_fast_atof(str);
    return defaul;
}
float ReadAttrFromXML_float(ConfigXML& xml,
                            const wchar_t* element,
                            const wchar_t* attribute,
						    float defaul)
{
	if(!element||!attribute) return defaul;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_float(xml,ch1,ch2,defaul);
}
float ReadAttrFromXML_float(ConfigXML& xml,
                            void* element,
                            const char* attribute,
						    float defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return ConfigXML_fast_atof(str);
    return defaul;
}
float ReadAttrFromXML_float(ConfigXML& xml,
                            void* element,
                            const wchar_t* attribute,
						    float defaul)
{
	if(!element||!attribute) return defaul;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_float(xml,element,ch,defaul);
}
bool ReadAttrFromXML_float_n(ConfigXML& xml,
                             const char* element,
                             const char* attribute,
							 float* value,
						     const float* defaul,
							 int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			for(int i=0; i<n; i++)
				value[i]=defaul[i];
		}
		else
		{
			for(int i=0; i<n; i++)
				value[i]=0.0f;
		}

		return true;
	}
    else
	{
		if(str[0]=='a')
		{
			char sn[2]={str[1],0};
			int m=atoi(sn);
			float f=ConfigXML_fast_atof(&(str[2]));
            for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=f;
				else if(defaul) value[i]=defaul[i];
			}
		}
		else
		{
			vector<std::string> sv;
			splitElement(str,&sv);
			int m=sv.size();
			for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=ConfigXML_fast_atof(sv[i].c_str());
				else if(defaul) value[i]=defaul[i];
			}
		}

		return true;
	}
}
bool ReadAttrFromXML_float_n(ConfigXML& xml,
                             const wchar_t* element,
                             const wchar_t* attribute,
						     float* value,
						     const float* defaul,
							 int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_float_n(xml,ch1,ch2,value,defaul,n);
}
bool ReadAttrFromXML_float_n(ConfigXML& xml,
                             void* element,
                             const char* attribute,
						     float* value,
						     const float* defaul,
							 int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			for(int i=0; i<n; i++)
				value[i]=defaul[i];
		}
		else
		{
			for(int i=0; i<n; i++)
				value[i]=0.0f;
		}

		return true;
	}
    else
	{
		if(str[0]=='a')
		{
			char sn[2]={str[1],0};
			int m=atoi(sn);
			float f=ConfigXML_fast_atof(&(str[2]));
            for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=f;
				else if(defaul) value[i]=defaul[i];
			}
		}
		else
		{
			vector<std::string> sv;
			splitElement(str,&sv);
			int m=sv.size();
			for(int i=0; i<n; i++)
			{
				if(i<m) value[i]=ConfigXML_fast_atof(sv[i].c_str());
				else if(defaul) value[i]=defaul[i];
			}
		}

		return true;
	}
}
bool ReadAttrFromXML_float_n(ConfigXML& xml,
                             void* element,
                             const wchar_t* attribute,
						     float* value,
						     const float* defaul,
							 int n)
{
	if(!element||!attribute) return false;
	if(!value||n>4||n<1) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_float_n(xml,element,ch,value,defaul,n);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_double
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   double defaul ȱʡֵ
//[#03-03] ����˵����double ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵����
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
double ReadAttrFromXML_double(ConfigXML& xml,
                              const char* element,
                              const char* attribute,
							  double defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return atof(str);
    return defaul;
}
double ReadAttrFromXML_double(ConfigXML& xml,
                              const wchar_t* element,
                              const wchar_t* attribute,
							  double defaul)
{
	if(!element||!attribute) return defaul;

    char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_double(xml,ch1,ch2,defaul);
}
double ReadAttrFromXML_double(ConfigXML& xml,
                              void* element,
                              const char* attribute,
							  double defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str) return atof(str);
    return defaul;
}
double ReadAttrFromXML_double(ConfigXML& xml,
                              void* element,
                              const wchar_t* attribute,
							  double defaul)
{
	if(!element||!attribute) return defaul;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_double(xml,element,ch,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_uuid
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
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
bool ReadAttrFromXML_uuid(ConfigXML& xml,
                          const char* element,
                          const char* attribute,
						  unsigned int* value,
						  const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			value[0]=defaul[0];
			value[1]=defaul[1];
			value[2]=defaul[2];
			value[3]=defaul[3];
		}
		else
		{
			value[0]=0;
			value[1]=0;
			value[2]=0;
			value[3]=0;
		}

		return true;
	}
    else
	{
		if(str[0]=='z'
			&&str[1]==0)
		{
			value[0]=0;
			value[1]=0;
			value[2]=0;
			value[3]=0;
		}
		else
		{
			vector<std::string> sv;
			splitIP(str,&sv);
			int m=sv.size();
			for(int i=0; i<4; i++)
			{
				if(i<m) sscanf(sv[i].c_str(),"%x",&value[i]);
				else if(defaul) value[i]=defaul[i];
			}
		}

		return true;
	}
}
bool ReadAttrFromXML_uuid(ConfigXML& xml,
                          const wchar_t* element,
                          const wchar_t* attribute,
						  unsigned int* value,
						  const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

    char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_uuid(xml,ch1,ch2,value,defaul);
}
bool ReadAttrFromXML_uuid(ConfigXML& xml,
                          void* element,
                          const char* attribute,
						  unsigned int* value,
						  const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			value[0]=defaul[0];
			value[1]=defaul[1];
			value[2]=defaul[2];
			value[3]=defaul[3];
		}
		else
		{
			value[0]=0;
			value[1]=0;
			value[2]=0;
			value[3]=0;
		}

		return true;
	}
    else
	{
		if(str[0]=='z'
			&&str[1]==0)
		{
			value[0]=0;
			value[1]=0;
			value[2]=0;
			value[3]=0;
		}
		else
		{
			vector<std::string> sv;
			splitIP(str,&sv);
			int m=sv.size();
			for(int i=0; i<4; i++)
			{
				if(i<m) sscanf(sv[i].c_str(),"%x",&value[i]);
				else if(defaul) value[i]=defaul[i];
			}
		}

		return true;
	}
}
bool ReadAttrFromXML_uuid(ConfigXML& xml,
                          void* element,
                          const wchar_t* attribute,
						  unsigned int* value,
						  const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

    char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_uuid(xml,element,ch,value,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_uuid_ref
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
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
bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
                              const char* element,
                              const char* attribute,
						      unsigned int* value,
						      const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute,"0");
	if(str[0]!='r')
		return ReadAttrFromXML_uuid(xml,element,attribute,value,defaul);
	int code=atoi(&str[1]);
	if(code>0)
		return xml.Read_UUID_Ref(code,value,defaul);
	return false;
}
bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
                              const wchar_t* element,
                              const wchar_t* attribute,
						      unsigned int* value,
						      const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

    char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_uuid_ref(xml,ch1,ch2,value,defaul);
}
bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
                              void* element,
                              const char* attribute,
						      unsigned int* value,
						      const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute,"0");
	if(str[0]!='r')
		return ReadAttrFromXML_uuid(xml,element,attribute,value,defaul);
	int code=atoi(&str[1]);
	if(code>0)
		return xml.Read_UUID_Ref(code,value,defaul);
	return false;
}
bool ReadAttrFromXML_uuid_ref(ConfigXML& xml,
                              void* element,
                              const wchar_t* attribute,
						      unsigned int* value,
						      const unsigned int* defaul)
{
	if(!element||!attribute||!value) return false;

    char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_uuid_ref(xml,element,ch,value,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_uuid_str
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
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
bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
                              const char* element,
                              const char* attribute,
						      unsigned char* value,
						      const unsigned char* defaul)
{
	if(!element||!attribute||!value) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			for(int i=0; i<16; i++)
				value[i]=defaul[i];
		}
		else
		{
			for(int i=0; i<16; i++)
			{
				if((i==4)||(i==6)||(i==8)||(i==10))
				    value[i]='-';
				else value[i]='0';
			}
		}
		return true;
	}
    else
	{
		bool fine=true;
		int i,cur_pos=0;
		for(i=0; i<16; i++)
		{
			// skip '-' symbol
			if((i==4)||(i==6)||(i==8)||(i==10))
			{
				if(*(str+cur_pos)!='-')
				{
					fine=false;
					break;
				}
				cur_pos++;
			}

			// char to byte
			value[i]=0;

			if((*(str+cur_pos)>='0')&&(*(str+cur_pos)<='9'))
				value[i]+=(unsigned char)(*(str+cur_pos)-'0');
			else if((*(str+cur_pos)>='a')&&(*(str+cur_pos)<='f'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'a');
			else if((*(str+cur_pos)>='A')&&(*(str+cur_pos)<='F'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'A');
			else
			{
				fine=false;
				break;
			}

			value[i]=value[i]<<4; // to high 4 bits
			cur_pos++;

			if((*(str+cur_pos)>='0')&&(*(str+cur_pos)<='9'))
				value[i]+=(unsigned char)(*(str + cur_pos)-'0');
			else if((*(str+cur_pos)>='a')&&(*(str+cur_pos)<='f'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'a');
			else if((*(str+cur_pos)>='A')&&(*(str+cur_pos)<='F'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'A');
			else
			{
				fine=false;
				break;
			}

			cur_pos++;
		}
		if(!fine)
		{
			for(i=0; i<16; i++)
				value[i]=0;
		}
		return true;
	}
}
bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
                              const wchar_t* element,
                              const wchar_t* attribute,
						      unsigned char* value,
						      const unsigned char* defaul)
{
	if(!element||!attribute||!value) return false;

    char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_uuid_str(xml,ch1,ch2,value,defaul);
}
bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
                              void* element,
                              const char* attribute,
						      unsigned char* value,
						      const unsigned char* defaul)
{
	if(!element||!attribute||!value) return false;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(!str)
	{
		if(defaul)
		{
			for(int i=0; i<16; i++)
				value[i]=defaul[i];
		}
		else
		{
			for(int i=0; i<16; i++)
			{
				if((i==4)||(i==6)||(i==8)||(i==10))
				    value[i]='-';
				else value[i]='0';
			}
		}
		return true;
	}
    else
	{
		bool fine=true;
		int i,cur_pos=0;
		for(i=0; i<16; i++)
		{
			// skip '-' symbol
			if((i==4)||(i==6)||(i==8)||(i==10))
			{
				if(*(str+cur_pos)!='-')
				{
					fine=false;
					break;
				}
				cur_pos++;
			}

			// char to byte
			value[i]=0;

			if((*(str+cur_pos)>='0')&&(*(str+cur_pos)<='9'))
				value[i]+=(unsigned char)(*(str+cur_pos)-'0');
			else if((*(str+cur_pos)>='a')&&(*(str+cur_pos)<='f'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'a');
			else if((*(str+cur_pos)>='A')&&(*(str+cur_pos)<='F'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'A');
			else
			{
				fine=false;
				break;
			}

			value[i]=value[i]<<4; // to high 4 bits
			cur_pos++;

			if((*(str+cur_pos)>='0')&&(*(str+cur_pos)<='9'))
				value[i]+=(unsigned char)(*(str + cur_pos)-'0');
			else if((*(str+cur_pos)>='a')&&(*(str+cur_pos)<='f'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'a');
			else if((*(str+cur_pos)>='A')&&(*(str+cur_pos)<='F'))
				value[i]+=(unsigned char)(10+*(str+cur_pos)-'A');
			else
			{
				fine=false;
				break;
			}

			cur_pos++;
		}
		if(!fine)
		{
			for(i=0; i<16; i++)
				value[i]=0;
		}
		return true;
	}
}
bool ReadAttrFromXML_uuid_str(ConfigXML& xml,
                              void* element,
                              const wchar_t* attribute,
						      unsigned char* value,
						      const unsigned char* defaul)
{
	if(!element||!attribute||!value) return false;

    char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_uuid_str(xml,element,ch,value,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadAttrFromXML_color
//[#03-01] �������ܣ���ȡĳattribute
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* attribute �ַ���
//                   int defaul ȱʡֵ
//[#03-03] ����˵����unsigned int ��������Ϣ
//[#03-04] �������ڣ�2006.2.1
//[#03-05] �޸����ڣ�
//[#03-06] ִ��ʱ�䣺
//[#03-07] �ڴ����ģ�
//[#03-08] ����������
//[#03-09] ����˵�������û�и�attribute�򷵻�NULL
//[#03-10] Ӧ��ʵ����
//[#03-!!] ˵������
//-----------------------------------------------------------------------------
unsigned int ReadAttrFromXML_color(ConfigXML& xml,
                                   const char* element,
                                   const char* attribute,
						           unsigned int defaul)
{
	if(!element||!attribute) return defaul;

    const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str)
	{
		unsigned int c;
		sscanf(str,"%x",&c);
		return c;
	}
    return defaul;
}
unsigned int ReadAttrFromXML_color(ConfigXML& xml,
                                   const wchar_t* element,
                                   const wchar_t* attribute,
					               unsigned int defaul)
{
	if(!element||!attribute) return defaul;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	ConfigXML_UnicodeToAnsi(attribute,ch2,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int(xml,ch1,ch2,defaul);
}
unsigned int ReadAttrFromXML_color(ConfigXML& xml,
                                   void* element,
                                   const char* attribute,
					               unsigned int defaul)
{
	if(!element||!attribute) return defaul;

	const char* str=ReadAttrFromXML_str(xml,element,attribute);
    if(str)
	{
		unsigned int c;
		sscanf(str,"%x",&c);
		return c;
	}
    return defaul;
}
unsigned int ReadAttrFromXML_color(ConfigXML& xml,
                                   void* element,
                                   const wchar_t* attribute,
					               unsigned int defaul)
{
	if(!element||!attribute) return defaul;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(attribute,ch,CONFIGXML_MAX_ELEM);
	return ReadAttrFromXML_int(xml,element,ch,defaul);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�RemoveTextFromXML
//[#03-01] �������ܣ���XML�ļ����Ƴ�ĳText
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
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
bool RemoveTextFromXML(ConfigXML& xml, const char* element)
{    
    if(!element) return false;
	
	bool remove=false;

    TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,NULL,element);
    if(ele)
    {
        TiXmlNode* node=ele->FirstChild();
        while(node)
        {
            if(node->Type()==TiXmlNode::TEXT)
            {
                TiXmlNode* n=node->NextSibling();
                ele->RemoveChild(node);
                node=n;
                remove=true;
            }
            else node=node->NextSibling();
        }
        return remove;
    }
    return false;
}
bool RemoveTextFromXML(ConfigXML& xml, const wchar_t* element)
{
	if(!element) return false;

	char ch[CONFIGXML_MAX_ELEM];
	ConfigXML_UnicodeToAnsi(element,ch,CONFIGXML_MAX_ELEM);
	return RemoveTextFromXML(xml,ch);
}
bool RemoveTextFromXML(ConfigXML& xml, void* element)
{
	if(!element) return false;

	bool remove=false;

    TiXmlNode* node=((TiXmlElement*)element)->FirstChild();
    while(node)
    {
        if(node->Type()==TiXmlNode::TEXT)
        {
            TiXmlNode* n=node->NextSibling();
            ((TiXmlElement*)element)->RemoveChild(node);
            node=n;
            remove=true;
        }
        else node=node->NextSibling();
    }
    return remove;
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteTextToXML
//[#03-01] �������ܣ���ĳTextд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
//                   const char* text �ַ���
//                   const char* defaul ȱʡֵ
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
void* WriteTextToXML(ConfigXML& xml, const char* element, const char* text, const char* defaul)
{
    if(!element) return NULL;
	if(!text&&!defaul) return NULL;

    TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,NULL,element);
    if(!ele) ele=(TiXmlElement*)WriteElemToXML(xml,NULL,element,false);

    if(ele)
    {
        RemoveTextFromXML(xml,element);
		const char* t=text;
		if(!t) t=defaul;

        TiXmlText txt(t);
        TiXmlNode* node=ele->FirstChild();
		TiXmlText* ret;
		TiXmlNode* rnode;
        if(node)
            rnode=ele->InsertBeforeChild(node,txt);
        else rnode=ele->InsertEndChild(txt);
		
		if(rnode) ret=rnode->ToText();
		else ret=NULL;

        return ret;
    }
    return NULL;
}
void* WriteTextToXML(ConfigXML& xml, const wchar_t* element, const wchar_t* text, const wchar_t* defaul)
{
	if(!element) return NULL;
	if(!text&&!defaul) return NULL;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_VALUE];
	char ch3[CONFIGXML_MAX_VALUE];
	ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	if(text)
	    ConfigXML_UnicodeToAnsi(text,ch2,CONFIGXML_MAX_VALUE);
	else ch2[0]=0;
	if(defaul)
	    ConfigXML_UnicodeToAnsi(defaul,ch3,CONFIGXML_MAX_VALUE);
	else ch3[0]=0;
	return WriteTextToXML(xml,ch1,ch2,ch3);
}
void* WriteTextToXML(ConfigXML& xml, void* element, const char* text, const char* defaul)
{
    if(!element) return NULL;
	if(!text&&!defaul) return NULL;

    RemoveTextFromXML(xml,element);
	const char* t=text;
	if(!t) t=defaul;

    TiXmlText txt(t);
    TiXmlNode* node=((TiXmlElement*)element)->FirstChild();
	TiXmlText* ret;
	TiXmlNode* rnode;
    if(node)
        rnode=((TiXmlElement*)element)->InsertBeforeChild(node,txt);
    else rnode=((TiXmlElement*)element)->InsertEndChild(txt);
	
	if(rnode) ret=rnode->ToText();
	else ret=NULL;

    return ret;
}
void* WriteTextToXML(ConfigXML& xml, void* element, const wchar_t* text, const wchar_t* defaul)
{
	if(!element) return NULL;
	if(!text&&!defaul) return NULL;

	char ch1[CONFIGXML_MAX_VALUE];
	char ch2[CONFIGXML_MAX_VALUE];
	if(text)
	    ConfigXML_UnicodeToAnsi(text,ch1,CONFIGXML_MAX_VALUE);
	else ch1[0]=0;
	if(defaul)
		ConfigXML_UnicodeToAnsi(defaul,ch2,CONFIGXML_MAX_VALUE);
	else ch2[0]=0;
	return WriteTextToXML(xml,element,ch1,ch2);
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�ReadTextFromXML
//[#03-01] �������ܣ���ȡĳText
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* element �ַ���
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
const char* ReadTextFromXML(ConfigXML& xml, const char* element, const char* defaul)
{
    if(!element) return defaul;

    TiXmlElement* ele=(TiXmlElement*)SearchElemInXML(xml,NULL,element);
    if(ele)
    {
        TiXmlNode* node=ele->FirstChild();
        while(node)
        {
            if(node->Type()==TiXmlNode::TEXT)
                return node->Value();
            else node=node->NextSibling();
        }
        return defaul;
    }
    return defaul;
}
const wchar_t* ReadTextFromXML(ConfigXML& xml, const wchar_t* element, const wchar_t* defaul)
{
	if(!element) return defaul;

	char ch1[CONFIGXML_MAX_ELEM];
	char ch2[CONFIGXML_MAX_VALUE];
    ConfigXML_UnicodeToAnsi(element,ch1,CONFIGXML_MAX_ELEM);
	if(defaul)
	    ConfigXML_UnicodeToAnsi(defaul,ch2,CONFIGXML_MAX_VALUE);
	else ch2[0]=0;
	
	const char* result=ReadTextFromXML(xml,ch1,ch2);
	if(result)
	{
		ConfigXML_AnsiToUnicode(result,xml.m_wch,CONFIGXML_MAX_VALUE);
		return xml.m_wch;
	}
	return defaul;
}
const char* ReadTextFromXML(ConfigXML& xml, void* element, const char* defaul)
{
    if(!element) return defaul;

    TiXmlNode* node=((TiXmlElement*)element)->FirstChild();
    while(node)
    {
        if(node->Type()==TiXmlNode::TEXT)
            return node->Value();
        else node=node->NextSibling();
    }
    return defaul;
}
const wchar_t* ReadTextFromXML(ConfigXML& xml, void* element, const wchar_t* defaul)
{
	if(!element) return defaul;

	char ch[CONFIGXML_MAX_VALUE];
	if(defaul)
	    ConfigXML_UnicodeToAnsi(defaul,ch,CONFIGXML_MAX_VALUE);
	else ch[0]=0;
	
	const char* result=ReadTextFromXML(xml,element,ch);
	if(result)
	{
		ConfigXML_AnsiToUnicode(result,xml.m_wch,CONFIGXML_MAX_VALUE);
		return xml.m_wch;
	}
	return defaul;
}
//-----------------------------��������----------------------------------------

//-----------------------------����˵��----------------------------------------
//[#03-00] �������ƣ�WriteCommentToXML
//[#03-01] �������ܣ���ĳCommentд��XML�ļ���
//[#03-02] ����˵����ConfigXML& xml XML�ļ�����
//                   const char* comment ע��
//                   const char* defaul ȱʡֵ
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
void* WriteCommentToXML(ConfigXML& xml, const char* comment, const char* defaul)
{
	if(!comment&&!defaul) return NULL;

	const char* c=comment;
	if(!c) c=defaul;

    TiXmlComment* cmt=new TiXmlComment;
	if(!cmt) return NULL;
	TiXmlComment* ret;
	TiXmlNode* node;

	cmt->SetValue(c);
	node=xml.m_pDoc->LinkEndChild(cmt);

	if(node) ret=node->ToComment();
	else ret=NULL;

    return ret;
}
void* WriteCommentToXML(ConfigXML& xml, const wchar_t* comment, const wchar_t* defaul)
{
	if(!comment&&!defaul) return NULL;

	char ch1[CONFIGXML_MAX_VALUE];
	char ch2[CONFIGXML_MAX_VALUE];
	if(comment)
	    ConfigXML_UnicodeToAnsi(comment,ch1,CONFIGXML_MAX_VALUE);
	else ch1[0]=0;
	if(defaul)
	    ConfigXML_UnicodeToAnsi(defaul,ch2,CONFIGXML_MAX_VALUE);
	else ch2[0]=0;
	return WriteCommentToXML(xml,ch1,ch2);
}
//-----------------------------��������----------------------------------------

//-----------------------------------------------------------------------------
///////////////////////////////�ļ�����////////////////////////////////////////