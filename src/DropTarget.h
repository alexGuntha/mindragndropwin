/*
	Minimal Drag and Drop Application for Windows
	Copright (C) Alexandre LHUILLIER - 2019
	
	===
	
	This class has to be registered by the application in order for
	the drag-and-drop functionnality to work.
	
	The mechanism of extracting the paths of the dragged files is 
	entirely embedded in the Drop() method of this class.
*/

#ifndef _DROPTARGET_H
#define _DROPTARGET_H

#include <iostream>

#include <oleidl.h>
#include <shellapi.h>

class DropTarget: IDropTarget
{
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject){ return S_OK; }

	virtual ULONG STDMETHODCALLTYPE AddRef(void){ return 0; }

	virtual ULONG STDMETHODCALLTYPE Release(void){ return 0; }

	virtual HRESULT STDMETHODCALLTYPE DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		if(pdwEffect == NULL)
			return E_INVALIDARG;

		*pdwEffect |= DROPEFFECT_COPY;

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		if(pdwEffect == NULL)
			return E_INVALIDARG;

		*pdwEffect |= DROPEFFECT_COPY;

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE DragLeave(void)
	{
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		if(pdwEffect == NULL)
			return E_INVALIDARG;

		*pdwEffect |= DROPEFFECT_COPY;

		FORMATETC format;
		STGMEDIUM medium;
		format.cfFormat = CF_HDROP;
		format.ptd = NULL;
		format.dwAspect = DVASPECT_CONTENT;
		format.lindex = -1;
		format.tymed = TYMED_HGLOBAL;
		medium.tymed = TYMED_HGLOBAL;
		HRESULT res = pDataObj->GetData(&format, &medium);
		HDROP drop = (HDROP)medium.hGlobal;
		wchar_t* fileName = NULL;
		//See https://docs.microsoft.com/en-us/windows/desktop/api/shellapi/nf-shellapi-dragqueryfilew
		UINT filePathesCount = DragQueryFile(drop, 0xFFFFFFFF, NULL, 512);//If "0xFFFFFFFF" as the second parameter: return the count of files dropped
		UINT longestFileNameLength = 0;

		for(UINT i = 0; i < filePathesCount; ++i)
		{
			//If NULL as the third parameter: return the length of the path, not counting the trailing '0'
			UINT fileNameLength = DragQueryFile(drop, i, NULL, 512) + 1;
			if(fileNameLength > longestFileNameLength)
			{
				if(fileName != NULL)
				{
					free(fileName);
				}
				longestFileNameLength = fileNameLength;
				fileName = (wchar_t*)malloc(longestFileNameLength * sizeof(*fileName));
			}
			DragQueryFile(drop, i, fileName, fileNameLength);

			std::wcout << fileName << std::endl;
		}
		if(fileName != NULL)
		{
			free(fileName);
		}
		ReleaseStgMedium(&medium);

		return S_OK;
	}
};
#endif
