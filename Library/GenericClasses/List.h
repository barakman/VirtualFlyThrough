#ifndef LIST_H
#define LIST_H


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  List                                                          //
//                                                                            //
// DESCRIPTION: Store generic-type elements.                                  //
//              Allow insertion of new elements.                              //
//              Allow deletion of existing elements.                          //
//                                                                            //
// REMARKS:     The time complexity of inserting or deleting an element is    //
//              O(n), where n is the current number of elements in the list.  //
//              However, in a sequential set of operations (e.g. for i=1:N),  //
//              the average time complexity of each operation would be O(1).  //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


template<typename TYPE>
class List
{
public: //Constructor + Destructor
	List();
	virtual ~List();
	//--------------------------------------------------------------------------
public: //Insertion interface
	virtual void Add(const TYPE& tItem,int iIndex);
	virtual void Append(List<TYPE>& cList);
	//--------------------------------------------------------------------------
public: //Deletion interface
	virtual void Remove(int iIndex);
	virtual void Clear();
	//--------------------------------------------------------------------------
public: //Retrieval interface
	virtual TYPE& Get(int iIndex);
	virtual int Size() const;
	//--------------------------------------------------------------------------
protected: //Node definition
	struct Node
	{
		TYPE  m_tItem; //A data record
		Node* m_pPrev; //The previous node
		Node* m_pNext; //The next node
	};
	//--------------------------------------------------------------------------
protected: //List pointers
	Node* m_pCurr; //The current node in the list
	Node* m_pHead; //The first node in the list
	Node* m_pTail; //The last node in the list
	//--------------------------------------------------------------------------
protected: //List indices
	int m_iCurrIndex; //The number of the current node in the list
	int m_iLastIndex; //The number of the last node in the list
	//--------------------------------------------------------------------------
protected: //Internal operations
	virtual void SetCurrTo(int iIndex);
	//--------------------------------------------------------------------------
};


template<typename TYPE>
List<TYPE>::List()
{
	m_pCurr=0;
	m_pHead=0;
	m_pTail=0;

	m_iCurrIndex=-1;
	m_iLastIndex=-1;
}


template<typename TYPE>
List<TYPE>::~List()
{
	Clear();
}


template<typename TYPE>
void List<TYPE>::Add(const TYPE& tItem,int iIndex)
{
	Node* pNode=new Node;
	pNode->m_tItem=tItem;

	if (iIndex<m_iLastIndex+1)
	{
		SetCurrTo(iIndex);
		pNode->m_pPrev=m_pCurr->m_pPrev;
		pNode->m_pNext=m_pCurr;
	}
	else
	{
		m_iCurrIndex=iIndex;
		pNode->m_pPrev=m_pTail;
		pNode->m_pNext=0;
	}

	if (pNode->m_pPrev)
		pNode->m_pPrev->m_pNext=pNode;
	if (pNode->m_pNext)
		pNode->m_pNext->m_pPrev=pNode;

	if (iIndex==0)
		m_pHead=pNode;
	if (iIndex==++m_iLastIndex)
		m_pTail=pNode;

	m_pCurr=pNode;
}


template<typename TYPE>
void List<TYPE>::Append(List<TYPE>& cList)
{
	if (cList.Size()>0)
	{
		if (this->Size()>0)
		{
			m_pTail->m_pNext=cList.m_pHead;
			cList.m_pHead->m_pPrev=m_pTail;
			m_iLastIndex+=cList.Size();
			m_pTail=cList.m_pTail;
		}
		else
		{
			m_pCurr=cList.m_pCurr;
			m_pHead=cList.m_pHead;
			m_pTail=cList.m_pTail;
			m_iCurrIndex=cList.m_iCurrIndex;
			m_iLastIndex=cList.m_iLastIndex;
		}

		cList.m_pCurr=0;
		cList.m_pHead=0;
		cList.m_pTail=0;
		cList.m_iCurrIndex=-1;
		cList.m_iLastIndex=-1;
	}
}


template<typename TYPE>
void List<TYPE>::Remove(int iIndex)
{
	SetCurrTo(iIndex);
	Node* pNode=m_pCurr;

	if (m_pCurr->m_pPrev)
		m_pCurr->m_pPrev->m_pNext=m_pCurr->m_pNext;
	if (m_pCurr->m_pNext)
		m_pCurr->m_pNext->m_pPrev=m_pCurr->m_pPrev;

	if (m_pHead==m_pCurr)
		m_pHead=m_pHead->m_pNext;
	if (m_pTail==m_pCurr)
		m_pTail=m_pTail->m_pPrev;

	if (iIndex<m_iLastIndex--)
	{
		m_pCurr=m_pCurr->m_pNext;
		m_iCurrIndex=iIndex;
	}
	else
	{
		m_pCurr=m_pCurr->m_pPrev;
		m_iCurrIndex=iIndex-1;
	}

	delete pNode;
}


template<typename TYPE>
void List<TYPE>::Clear()
{
	while (Size()>0)
		Remove(0);
}


template<typename TYPE>
TYPE& List<TYPE>::Get(int iIndex)
{
	SetCurrTo(iIndex);
	return m_pCurr->m_tItem;
}


template<typename TYPE>
int List<TYPE>::Size() const
{
	return m_iLastIndex+1;
}


template<typename TYPE>
void List<TYPE>::SetCurrTo(int iIndex)
{
	if (iIndex<0)
		throw "Index Too Small";

	else if (iIndex<=(0+m_iCurrIndex)/2)
	{
		m_pCurr=m_pHead;
		for (int i=0; i<iIndex; i++)
			m_pCurr=m_pCurr->m_pNext;
	}

	else if (iIndex<=m_iCurrIndex)
	{
		for (int i=iIndex; i<m_iCurrIndex; i++)
			m_pCurr=m_pCurr->m_pPrev;
	}

	else if (iIndex<=(m_iCurrIndex+m_iLastIndex)/2)
	{
		for (int i=m_iCurrIndex; i<iIndex; i++)
			m_pCurr=m_pCurr->m_pNext;
	}

	else if (iIndex<=m_iLastIndex)
	{
		m_pCurr=m_pTail;
		for (int i=iIndex; i<m_iLastIndex; i++)
			m_pCurr=m_pCurr->m_pPrev;
	}

	else
		throw "Index Too Large";

	m_iCurrIndex=iIndex;
}


#endif
