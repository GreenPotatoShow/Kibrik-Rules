// Copyright (c) 2017 by IIS. All rights reserved.
//===================================================================
// Usage notes: Группа параметров тремина.
//				Используется для задания совместных (vs. альтернативы) 
//				параметров при описании сложной семнатики термина
//===================================================================
// Используется :   IKNWord, IKNPhrase, KNConcept
//===================================================================
// Использует   :  
//===================================================================
// March 2017                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNConceptParameterGroupH
#define IKNConceptParameterGroupH
//---------------------------------------------------------------------------
//#include "KNMacrosVoc.h"
#include "IKNConceptParameter.h"
//---------------------------------------------------------------------------
/** Группа параметров тремина. */
class IKNConceptParameterGroup //IKNConceptParameter
{
public:
	/** Взять кол-во элементов в группе. */
	virtual uint GetCount() const = 0;
	/** Взять родительскую родительскую группу. */
//	virtual IKNConceptParameterGroup* GetParentGroup() const = 0;
	/** Установить родительскую группу. */
//	virtual void SetParentGroup(IKNConceptParameterGroup* iParent) = 0;

	/** Взять элемент группы по индексу. */
	virtual IKNConceptParameter* GetParameter(uint) const = 0;

	/** Поиск параметра. */
	virtual IKNConceptParameter* FindParameter(IKNTheme* iTh) const =0;
	/** Поиск параметра. */
	virtual IKNConceptParameter* FindParameter(uint iTh_id) const =0;
	/** Проверка наличия элемента в группе. */
	virtual bool IsElement(IKNConceptParameter* iPar) const =0;

	
	/** Добавить элемент в группу. 
	 *	@return Если элемент уже существует или 0, то OPERATION_ERROR
	 */
	virtual t_errno AddParameter(IKNConceptParameter*) = 0;	
	/** Удалить элемент группы по индексу. 
	 *	@note Элемент исключается из группы, но не удаляется.
	 */
	virtual void DeleteParameter(uint) = 0;
};

#endif
