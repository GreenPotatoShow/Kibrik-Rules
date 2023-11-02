// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNResultListH
#define IKNResultListH
//---------------------------------------------------------------------------
#include "IKNMorphProperties.h"
//#include "IKNWordShell.h"
#include "IKNPhraseShell.h"
//-------------------------------------------------------------------
/**
 *	@interface IKNResultList
 *	Список найденных объетов.
 */
class IKNResultList
{
public:
	/** Получить количество найденных словарных объектов.
     * @param iType - тип словарных объектов
     *		iType = -1 - все объектоы
     *		iType = 0  - все слова (с повторами)
     *		iType = 1  - слова из словаря значимых слов
     *		iType = 2  - слова из стоп-словаря
     *		iType = 3  - все СК (с повторами)
     *		iType = 4  - СК из словаря значимых СК
     *		iType = 5  - СК из стоп-словаря
     *		iType = 6  - кол-во неповторяющихся слов
     *		iType = 7  - кол-во неповторяющихся СК
     *		iType = 10  - новые слова
     *		iType = 11  - новые СК
     */
	virtual int GetCount( int iType = -1 ) = 0;

	virtual void InitWordsList() = 0;
	/** Взять следуещее слово, найденное в тексте. */
	virtual IKNWordShell* GetNextWordShell() const = 0;

	/** Взятие СК по индексу. */
	virtual IKNPhraseShell* GetPhraseShell( unsigned iPhraseIndex ) const = 0;

/** При статистической обработке shell-ы создаются в единичном экземпляре и накапливают статистику.
 * К такому типу обработки относятя все кроме MORPH_ANALISYS и WORK_ANALISYS
 */
	virtual void InitStatisticWords() = 0;
	/** Взять следуещее слово, найденное в тексте.
	 * @param   oCount - count word in text
	 */
	virtual IKNWord* GetStatisticWord( uint* oCount ) const = 0;

	virtual void InitStatisticPhrases() = 0;
	/** Взять следуещую фразу, найденную в тексте.
	 * @param   oCount - count phrse in text
	 */
	virtual IKNPhrase* GetStatisticPhrase( uint* oCount ) const = 0;

};

#endif
