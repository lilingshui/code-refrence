#ifndef __LIB_MINI_MEDIA_H__
#define __LIB_MINI_MEDIA_H__

#ifdef LIBMINIMEDIA_EXPORTS
#define LIBMINIMEDIA_API __declspec(dllexport)
#else
#define LIBMINIMEDIA_API __declspec(dllimport)
#endif

enum MM_REQUEST {
	REQUEST_NONE,
	REQUEST_DEMAND,
	REQUEST_UPLOAD,
	REQUEST_DOWNLOAD,
	REQUEST_ENUM,
	REQUEST_CREATE_DIR,
	REQUEST_DELETE_TREE,
	REQUEST_NAME_CONNECTION,
	REQUEST_REMOTE_PROCESS_CALL,
	REQUEST_CUSTOM_DATA,
};

typedef struct _FILE_ATTRIBUTE
{
	DWORD		dwAttributes;
	LONGLONG	llSize;
	FILETIME	ftLastModified;
} FILE_ATTRIBUTE, *PFILE_ATTRIBUTE;

#endif //__LIB_MINI_MEDIA_H__