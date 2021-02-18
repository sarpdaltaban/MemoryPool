/**
  *************************************************************************
  * @file    MemPool.h
  * @author  Sarp Engin DALTABAN
  * @version V 0.1.0
  * @date    1-Feb-2021
  * @brief   This is a Memory Pool implementation for fast de/allocations.
  *	@Note	 There is only a Header File because of a template class.
  *************************************************************************
  */

#ifndef MEMPOOL_H_
#define MEMPOOL_H_

/* Includes -------------------------------------------------------------*/
#include <stdio.h>
#include <cstring>

/* Global Variables -----------------------------------------------------*/
const int g_MaxNumberOfObjectsInPool = 1000;

template<class T>
class MemPool {
public:
	/**
	* @brief  Constructor initializes member variables
	* @timeComplexity  O(1)
	* @spaceComplexity O(1)
	*/
	MemPool() {
		m_bPoolInitialized = false;
		m_uiNumOfElements = 0;
	}

	/**
	* @brief  This function; allocates a memory for the pool at start,
	*						 initializes an unsigned array holding free indexes of adresses which will be used as a stack,
	*						 initializes a boolean array which indicates related address is in use or not.				
	* @timeComplexity  O(n)		
	* @spaceComplexity O(n)
 	*/
	void createPool() {
		if (m_bPoolInitialized == false)
		{
			m_bPoolInitialized = true;
			m_tpPool = (T*)malloc(sizeof(T) * g_MaxNumberOfObjectsInPool);
			m_bpMemInUse = (bool*)malloc(sizeof(bool) * g_MaxNumberOfObjectsInPool);
			m_uipFreeAdrIdx = (unsigned *)malloc(sizeof(unsigned) * g_MaxNumberOfObjectsInPool);

			for (int i = 0; i < g_MaxNumberOfObjectsInPool; i++) {
				*m_uipFreeAdrIdx++ = g_MaxNumberOfObjectsInPool - (i + 1);
				m_bpMemInUse[i] = false;
			}
		}		
	}

	/**
	* @brief  This function destroys members of this class.
	* @timeComplexity  O(1)
	* @spaceComplexity O(1)
	*/
	void destroyPool() {
		if (m_bPoolInitialized){
			m_bPoolInitialized = false;
			free(m_tpPool);
			free(m_bpMemInUse);
			free(m_uipFreeAdrIdx - (g_MaxNumberOfObjectsInPool - m_uiNumOfElements));
		}
	}

	/**
	* @brief  This function assigns a free memory space to an object called by.
	*		  If the memory is full, then function asserts.
	* @retval Start address for the object.
	* @note   This function can be used for objects with default constructors only.
	* @timeComplexity   O(1)
	* @spaceComplexity  O(1)
	*/
	T* allocateObject() {	
		if (m_bPoolInitialized)
		{
			if (m_uiNumOfElements == g_MaxNumberOfObjectsInPool) {
				assert(0);
			}
			T t;
			T* tpAllocated = &m_tpPool[*(--m_uipFreeAdrIdx)];
			memcpy(tpAllocated, &t, sizeof(T));
			m_bpMemInUse[*m_uipFreeAdrIdx] = true;
			m_uiNumOfElements++;
			return tpAllocated;
		}
		else {
			return 0;
		}
	}

	/**
	* @brief  This function assigns a free memory space to an object called by.
	*		  If the memory is full, then function asserts.
	* @params An object constructor.
	* @retval Start address for the object.
	* @note   This function can be used for objects with default constructors as well as non-default constructors
	* @timeComplexity   O(1)
	* @spaceComplexity  O(1)
	*/
	T* allocateObject(const T &t) {
		if (m_bPoolInitialized)
		{
			if (m_uiNumOfElements == g_MaxNumberOfObjectsInPool) {
				assert(0);
			}
			T* tpAllocated = &m_tpPool[*(--m_uipFreeAdrIdx)];
			memcpy(tpAllocated, &t, sizeof(T));
			m_bpMemInUse[*m_uipFreeAdrIdx] = true;
			m_uiNumOfElements++;
			return tpAllocated;
		}
		else {
			return 0;
		}
	}

	/**
	* @brief  This function pushes the integer index of the memory address to be freed, unless Null ptr is an input.
	* @params Pointer to the object to be deallocated
	* @note   Deallocation does not set the memory
	* @timeComplexity   O(1)
	* @spaceComplexity  O(1)
	*/
	void deallocateObject(T *tpAllocated) {	
		if (m_bPoolInitialized) 
		{
			int iIdx = tpAllocated - m_tpPool;
			if (tpAllocated != NULL && m_bpMemInUse[iIdx]) {
				m_bpMemInUse[iIdx] = false;
				*m_uipFreeAdrIdx++ = iIdx;
				m_uiNumOfElements--;
			}
		}		
	}

	/**
	* @brief  This function is created for testing purposes and prints all the bytes of this memory pool in an ordered form.
	* @note   This function is usable when g_MaxNumberOfObjectsInPool is lowerEqual than 7(changeable), otherwise it will print much.
	*/
	void printPool() {
		if (g_MaxNumberOfObjectsInPool <= 7){		
			printf("\n");
			for (int i = 0; i < g_MaxNumberOfObjectsInPool; i++) {
				char *c = (char *)&m_tpPool[i];
				printf("0x%p: ", c);
				for (int j = 0; j < sizeof(T); j++) {
					printf("%02X ", (*c++) & 0xFF);
				}
				printf("\n");
			}
		}
	}

private:
	T *m_tpPool;
	bool *m_bpMemInUse;
	bool m_bPoolInitialized;
	unsigned m_uiNumOfElements;
	unsigned *m_uipFreeAdrIdx;
};

#endif /* MEMPOOL_H_ */
