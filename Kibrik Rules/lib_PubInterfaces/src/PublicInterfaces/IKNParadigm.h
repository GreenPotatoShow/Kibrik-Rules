// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Usage notes: Декларация базового объекта работающего со статистикой.
// элемент type определяет тип словаря понятия + тип словаря получения 
//===================================================================
// Используется :   IKNWord, IKNPhrase, KNConcept
//===================================================================
// Sep 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNParadigmH
#define IKNParadigmH
//---------------------------------------------------------------------------
#include "KNMacros.h"
//#include "KNMacrosType.h"
#include "IKNMorphProperties.h"
//---------------------------------------------------------------------------
/** Парадигма - список окончаний слова.
 *  К каждому окончанию привязывается набор морф.индексов.
 *	Если у формы есть приставки то для пары окончание+приставка - набор морф.индексов
 */
class IKNParadigm
{
public:
    /** Количество окончаний. */
	virtual unsigned GetCount() const = 0;
    /** Количество форм с приставкой (дополнительно к GetCount()). */
	virtual unsigned GetCountPref() const = 0;
//    /** Может ли лексема иметь формы с приставками (при этом не обязательно имеет). */
//	virtual bool IsPrefixInclude() const = 0;
    /** Получить окончание (без приставки). */
	virtual const char * GetFlex( unsigned iIndex ) const = 0;
    /** Получить окончание для формы с приставкой. */
	virtual const char * GetFlexPref( uint iIndexPref ) const = 0;
    /** Получить приставку. */
	virtual const char * GetPref( uint iIndexPref ) const = 0;
    virtual t_errno GetFlexPref( uint iIndexPref, char* oFlex, char* oPref ) const = 0;

// Работа с ПРИЗНАКАМИ
    /** Получить количество наборов морф. признаков окончания iIndex.
	 *	@note Каждое окончание может иметь несколько групп признаков (хотя обычно группа одна)
	 *		  Пример: "мам(ы)" имеем не меньше 2 групп: (ед,род), (мн,им) 
	 *	@note Здесь индекс общий для форм с и без приставок GetCount+GetCountPref
	 */
	virtual uint GetGroupCount( uint iIndex ) = 0;
    /** Получить набор морф. признаков с индексом iIndexGroup, соответствующих
     *	словоформе с окончанием iIndex в виде строки (длина PHRASE_LENGTH).
     */
	virtual t_errno GetGroupAsString( uint iIndex, uint iIndexGroup, char* oProp ) = 0;

    /** Получить iIndexGroup-набор морф. признаков у iIndex-окончания */
	virtual IKNMorphProperties* GetGroup( uint iIndex, uint iIndexGroup ) = 0;

// ПОИСК формы по признакам
    /** Создать пустой набор для последующего добавления морф. признаков с целью узнать окончание. */
	virtual IKNMorphProperties* CreateGroup() = 0;
    /** А дальше надо как-то получить список индексов по установленным признакам.
     *	!!?? Пока только первый.
     */
	virtual uint GetIndexByProperties() = 0;
};

#endif
