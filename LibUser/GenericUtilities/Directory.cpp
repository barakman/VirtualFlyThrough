#include "Directory.h"
#include <direct.h>
#include <string.h>
#include <io.h>


Directory::Directory(const char* aName)
{
	_chdir(aName);
	Open();
}


Directory::~Directory()
{
	Close();
}


void Directory::ChangeTo(int iId)
{
	if (FileIsSubDir(iId)==true)
	{
		_chdir(GetFileName(iId));
		Close();
		Open();
	}
}


int Directory::GetNumOfFiles() const
{
	return m_iFileCount;
}


bool Directory::FileIsSubDir(int iId) const
{
	if (0<=iId && iId<=m_iFileCount-1)
		return m_aFileFlags[iId];
	return false;
}


char* Directory::GetFileName(int iId) const
{
	if (0<=iId && iId<=m_iFileCount-1)
		return m_aFileNames[iId];
	return NULL;
}


void Directory::Open()
{
    int iHandle;
	struct _finddata_t sFile;

	iHandle=_findfirst("*.*",&sFile);
	m_iFileCount=0;
	while (_findnext(iHandle,&sFile)==0)
		m_iFileCount++;
	_findclose(iHandle);

	m_aFileFlags=new bool[m_iFileCount];
	m_aFileNames=new char*[m_iFileCount];

	iHandle=_findfirst("*.*",&sFile);
	for (int i=0; i<m_iFileCount; i++)
	{
		_findnext(iHandle,&sFile);
		m_aFileFlags[i]=(sFile.attrib&_A_SUBDIR)!=0;
		m_aFileNames[i]=new char[strlen(sFile.name)+1];
		strcpy(m_aFileNames[i],sFile.name);
	}
	_findclose(iHandle);
}


void Directory::Close()
{
	delete[] m_aFileFlags;
	for (int i=0; i<m_iFileCount; i++)
		delete[] m_aFileNames[i];
	delete[] m_aFileNames;
}
