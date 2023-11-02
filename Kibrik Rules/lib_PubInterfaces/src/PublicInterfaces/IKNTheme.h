// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNThemeH
#define IKNThemeH
//---------------------------------------------------------------------------
#include "KNMacros.h"
//#include "KNMacrosType.h"
//---------------------------------------------------------------------------
/** 
 * @interface IKNTheme
 * Тема (класс).
 * @note Тема имеет собственный идентификатор (номер).
 *		 Идентификаторы начинаются с 1.
 */
class IKNTheme {
public:
	/** Get name of theme. */
	virtual t_errno GetName( char* oName ) const = 0;
	virtual const char* GetName() const = 0;
	/** Get id of theme. */
	virtual int GetId() const = 0;
	/**
	 * Get theme statistics.
	 * @params oWordsCount - count of local concepts in texts with this theme
	 * @params oTextsCount - count of procesed texts with this theme
	 */
	/// {
	virtual void GetStatistic( int* oTextsCount, int *oWordsCount ) const = 0;
	virtual uint GetTextStat() const = 0;
	virtual uint GetWordStat() const = 0;
	virtual uint GetUnicTermsStat() const = 0;
	/// }

	/** Тype of theme. */
	/// {
	virtual bool IsStat() const = 0;
	virtual bool IsHeadClassify() const = 0;
	virtual bool IsSem() const = 0;
	virtual t_theme_type GetType() const = 0;
	virtual void SetType( t_theme_type ) = 0;
	/// }
	
//-------------------------------------------------------------------
	/** Get theme, which is head of classification. */
	virtual IKNTheme* GetHeadClassify() const = 0;
    
	/** Get count of own parents (непосредственные родители). */
	virtual int GetParentCount() const = 0;
    virtual uint GetChildrenCount() const  = 0;
    virtual IKNTheme* GetChild( uint i ) const = 0;
	/** Get parent. */
	virtual IKNTheme* GetFirstParent() const = 0;
	virtual IKNTheme* GetNextParent() const = 0;
//	virtual IKNTheme* GetParent( unsigned num ) const = 0;

	/** Являтся ли тема наследником темы par. */
    virtual bool IsChildOf(IKNTheme* par) const = 0;
    virtual bool IsChildOf(const char* par) const = 0;
//-------------------------------------------------------------------
	/** Edit name. */
	virtual t_errno EditName( char* iNewName ) = 0;
	/** Edit index of active theme. */
	virtual t_errno EditId( unsigned iId ) = 0;

	/** Add parent. */
	virtual t_errno AddParent( IKNTheme* par ) = 0;
	/** Delete parent. */
	virtual t_errno DeleteParent( IKNTheme* par ) = 0;
};
//---------------------------------------------------------------------------
#endif
