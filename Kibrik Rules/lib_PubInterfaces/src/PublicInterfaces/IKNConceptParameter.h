// Copyright (c) 2009 by IIS. All rights reserved.
//===================================================================
// Usage notes: Декларация статистиких параметром термина по одной теме.
//===================================================================
// Используется :   IKNWord, IKNPhrase, KNConcept
//===================================================================
// Использует   :  
//===================================================================
// Oct 2009                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNConceptParameterH
#define IKNConceptParameterH
//---------------------------------------------------------------------------
//#include "KNMacrosVoc.h"
#include "IKNTheme.h"
//---------------------------------------------------------------------------
/** Позволяет взть полную статистику термина по одной теме. */
class IKNConceptParameter
{
public:
	/** Взять уникальный индекс темы, к которой относится статистика термина. */
	virtual uint GetThemeId() const = 0;
	/** Взять уникальный индекс темы, к которой относится статистика термина. */
	virtual IKNTheme* GetTheme() const = 0;
	/** Взять встречаемость термина в теме. */
	virtual uint GetCount() const = 0;
	/** Взять кол-во текстов, в которым встретился термин. */
	virtual uint GetCountText() const = 0;
	/** Взять экспертную оценку веса термина в теме.
	 *	@note -1 если оценка не установлена
	 */
	virtual int GetExpertNorm() const = 0;
	virtual void SetExpertNorm( int ) = 0;
	/** Взять вес термина в теме. Через общую частоту термина. */
//	virtual float GetDirectNorm() const = 0;
	/** Взять частоту термина в теме. */	                               	
	virtual double GetRelativeNorm() const = 0;
	/** Взять вес термина в теме.
	 *	@note Вес всех терминлв вычисляется функцией KNEngineStatistic::CalculateWeight
	 *	@param 	oStatus=0 означает, что вес не вычислялся
	 *			oStatus=1 вес в прjцессе вычисления (in progress)
	 *			oStatus=2 - вес вычислен
	 */
	virtual double GetWeight(byte_t *oStatus ) const = 0;
	
	virtual bool IsValue() const  = 0;
	virtual const char* GetValue() const  = 0;
//	virtual void SetValue(const char* iVal)  = 0;
	
};

typedef IKNConceptParameter IKNStatisticT;

#endif
