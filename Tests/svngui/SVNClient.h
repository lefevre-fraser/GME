#pragma once

#include "svn_client.h"
#include "svn_config.h"

class CSVNClient;

#define SVN_ERROR_MSG_MAX	256

class CSVNError
{
	friend class CSVNClient;

private:
	CSVNError(svn_error_t* e);

public:
	virtual ~CSVNError();
	CString msg();

private:
	svn_error_t	*svnError;
};


class CSVNFile
{
	friend class CSVNClient;

private:
	CSVNFile(const CString & filePath);

public:
	virtual ~CSVNFile();

	bool isTracked();
	bool isOwned();
	bool isLatest();

	void takeOwnership();
	void commit();
};


class CSVNClient
{
	friend class CSVNFile;

public:
	CSVNClient();
	virtual ~CSVNClient();

	void initialize();

	CSVNFile* embraceFile(const CString & filePath);

private:
	void forgetFile(CSVNFile* svnFile);

private:
	CList<CSVNFile*, CSVNFile*> svnFiles;
	bool isInitialized;

};

