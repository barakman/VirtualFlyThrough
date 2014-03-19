#ifndef DIRECTORY_H
#define DIRECTORY_H


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  Directory                                                     //
//                                                                            //
// DESCRIPTION: Navigate among directories.                                   //
//              Reveal the contents of the current directory.                 //
//                                                                            //
// REMARKS:     This class is applicable over the Windows file system.        //
//              If you use the 'GetFileName' operation, be sure to save       //
//              the file's name in a separate buffer before you use the       //
//              'ChangeTo' operation (and before the object is destroyed).    //
//              The first element in every directory is always ".", which is  //
//              a pointer to the current directory, and is therefore skipped. //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class Directory
{
public: //Constructor + Destructor
	Directory(const char* aName=".");
	virtual ~Directory();
	//--------------------------------------------------------------------------
public: //Object interface
	virtual void ChangeTo(int iId);
	//--------------------------------------------------------------------------
public: //Object interface
	virtual int GetNumOfFiles() const;
	virtual bool FileIsSubDir(int iId) const;
	virtual char* GetFileName(int iId) const;
	//--------------------------------------------------------------------------
protected: //Internal operations
	virtual void Open();
	virtual void Close();
	//--------------------------------------------------------------------------
protected: //Object attributes
	int    m_iFileCount; //The number of files in the current directory
	bool*  m_aFileFlags; //An array of sub-dir flags (for each file)
	char** m_aFileNames; //An array of names (for each file)
	//--------------------------------------------------------------------------
};


#endif
