/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/15   10:16
 *	File base:	HSObjectPool.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSObjectPool_H__
#define __HSObjectPool_H__
#pragma once
#include "HSBase.h"

template<typename T>
class HSObjectPool
{
public:
	HSObjectPool();
	HSObjectPool(int maxSize);
	HSObjectPool(int maxSize,CCObject *target,SEL_CallFunc callbackNewObect);
	~HSObjectPool(void);

public:
	
private:
	std::vector<T>* m_pvNotUsedObject;

	CCObject* m_newObjectTarget;
	SEL_CallFunc m_callbackNewObject;

	int m_iMaxCount;
	int m_iNewIndex;

private:
	void Init(int maxSize);

public:
	T GetNotUsedObjectFromBegin();

	T GetNotUsedObjectFromEnd();

	void SetCallbackNewObect(CCObject *target,SEL_CallFunc callbackNewObject);
	
	void AddNotUsedObjectFromBegin(T obj);

	void AddNotUsedObjectFromEnd(T obj);

	void SetNewMaxSize(int size);

	int GetNotUsedObjectSize();
};


//////////////////////////////////////////////////////////////////////////


template<typename T>
HSObjectPool<T>::HSObjectPool()
{
	m_newObjectTarget = NULL;
	m_callbackNewObject = NULL;
	this->Init(0);
}

template<typename T>
HSObjectPool<T>::HSObjectPool(int maxSize)
{
	m_newObjectTarget = NULL;
	m_callbackNewObject = NULL;
	this->Init(maxSize);
}

template<typename T>
HSObjectPool<T>::HSObjectPool(int maxSize, CCObject *target,SEL_CallFunc callbackNewObect )
{
	this->Init();
	this->SetCallbackNewObect(target,callbackNewObect);
}

template<typename T>
HSObjectPool<T>::~HSObjectPool(void)
{
	CC_SAFE_DELETE(m_pvNotUsedObject);
}

template<typename T>
void HSObjectPool<T>::SetNewMaxSize(int size)
{
	m_iMaxCount = size;
}

template<typename T>
void HSObjectPool<T>::Init(int maxSize)
{
	m_iNewIndex = 0;
	this->SetNewMaxSize(maxSize);
	this->m_pvNotUsedObject = new std::vector<T>();
}

template<typename T>
T HSObjectPool<T>::GetNotUsedObjectFromBegin()
{
	HSAssert(m_iMaxCount >= 0," m_iMaxCount Must be a non-zero");
	int count = 0;
	do 
	{
		count++;
		if (count > 3)
		{
			HSMessageBox("池子添加对象错误");
			break;
		}

		int notUsedObectCount = (int)m_pvNotUsedObject->size();

		if (notUsedObectCount > 0)
		{
			T obj = m_pvNotUsedObject->front();
			m_pvNotUsedObject->erase(m_pvNotUsedObject->begin());
			return obj;
		}else{
			if (m_iNewIndex >= m_iMaxCount)
			{
				break;
			}
			(this->m_newObjectTarget->*m_callbackNewObject)();
			m_iNewIndex++;
		}		
	} while (1);

	return NULL;
}

template<typename T>
T HSObjectPool<T>::GetNotUsedObjectFromEnd()
{
	// 	int notUsedObectCount = (int)m_pvNotUsedObject->size();
	// 	notUsedObectCount--;
	// 	if (notUsedObectCount  > 0)
	// 	{
	// 		return m_pvNotUsedObject[notUsedObectCount];
	// 	}
	return NULL;
}

template<typename T>
void HSObjectPool<T>::SetCallbackNewObect( CCObject *target,SEL_CallFunc callbackNewObject )
{
	m_newObjectTarget = target;
	m_callbackNewObject = callbackNewObject;
}

template<typename T>
void HSObjectPool<T>::AddNotUsedObjectFromBegin( T obj )
{
	m_pvNotUsedObject->insert(m_pvNotUsedObject->begin(),1,obj);
}

template<typename T>
void HSObjectPool<T>::AddNotUsedObjectFromEnd( T obj )
{
	typename std::vector<T>::iterator it = m_pvNotUsedObject->begin();
	for (;it != m_pvNotUsedObject->end();++it)
	{
		T o = dynamic_cast<T>(*it);
		if (o == obj)
		{
			return;
		}
	}
	m_pvNotUsedObject->push_back(obj);

}

template<typename T>
int HSObjectPool<T>::GetNotUsedObjectSize()
{
	return m_pvNotUsedObject->size();
}

#endif // __HSObjectPool_H____

