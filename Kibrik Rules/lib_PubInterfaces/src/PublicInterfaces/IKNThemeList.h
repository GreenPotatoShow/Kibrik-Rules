// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNThemeListH
#define IKNThemeListH
//---------------------------------------------------------------------------
#include "IKNTheme.h"
//---------------------------------------------------------------------------
/** 
 * @interface IKNThemeList
 * Иерархия тем.
 */
class IKNThemeList {
public:
	/** Get Themes count. */
	virtual unsigned GetCount() const = 0;
	/** Get theme. */
	virtual IKNTheme* GetTheme( unsigned iIndex ) const = 0;

	/** Find theme by name. */
	virtual IKNTheme* FindTheme( char* iThemeName ) const = 0;
	/** Find theme by own id. */
	virtual IKNTheme* FindTheme( unsigned iId ) const = 0;
    /** Найти тему по ее названию, если темы нет, то создать. */
	virtual IKNTheme* FindAddTheme( char *iThemeName ) = 0;

	/** Create theme (уникальный индекс теме присваивается автоматически).
	 * @params iName - name of new theme
	 * @params iParent - parent of new theme
	 */
	virtual IKNTheme* CreateTheme( char* iName, IKNTheme* iParent=0 ) = 0;
	/** Delete theme. */
	virtual void DeleteTheme( IKNTheme* iTheme ) = 0;

	/** Создать список стандартных тем (11 тем). */
	virtual void CreateDefult() = 0;

	/** Загрузить темы из текстового файла. */
    virtual bool LoadAsText(const char* file_name) = 0;
	/** Сохранить темы в текстовый файл. */
    virtual bool SaveAsText(const char* file_name) const = 0;

//-------------------------------------------------------------------
	/** Очистить список активных тем (для обучения). */
    virtual void ClearActive() = 0;
	/** Set text theme (для обучения). */
	virtual t_errno SetTextTheme( IKNTheme* iTheme ) = 0;

	/**
	 * Add theme to list of text themes (для обучения).
     * @note Если одному тексту соответствует несколько тем, то они
     *		 добавляются в список тем для обучения
	 */
	virtual t_errno AddTextTheme( IKNTheme* iTheme ) = 0;

	/** Get themes max Id. */
	virtual unsigned GetMaxId() const = 0;

//-------------------------------------------------------------------
// В IKNManager !!
	/**
	 * Cохранение иерархии тем в файл, указанный пользователем.
	 * @note Сохраение независимо от словаря.
	 * @param iName - имя файла (расширением задает пользователь)
	 */
//	virtual t_errno Save( char* iFileName ) const = 0;

	/**
	 * Загрузка иерархии тем из файла и замена текущей иерархии словаря.
	 * @note Осуществляется проверка совместимости новой иерархии
	 * 		 со словарем в указанном пользователем режиме iMode.
	 * 		 При несовместимости иерархия тем останется старой.
	 *
	 * @param iName - имя файла (расширением задает пользователь)
	 * @param iMode - режим замены иерархии
	 *		iMode = false - Темы идентифицируются по id + названию
	 *		iMode = true - Темы идентифицируются по id, названия заменяются
	 */
//	virtual t_errno Load(char* iFileName, bool iMode) = 0;
};
//---------------------------------------------------------------------------
#endif
