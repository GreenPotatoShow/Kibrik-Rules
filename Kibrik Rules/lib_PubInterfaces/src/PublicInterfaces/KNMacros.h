// Copyright (c) 2005 by IIS. All rights reserved.
//===================================================================
// Usage notes: Список универсальных типов, констант и макросов.
//===================================================================
// july 2009                  Edited                L. Sidorova, IIS
//===================================================================
#ifndef KNMacrosH
#define KNMacrosH

//#include "KNMacrosType.h"
//---------------------------------------------------------------------------
typedef unsigned char 	byte_t;
typedef unsigned int   	uint;
typedef byte_t t_errno; /**< error code */
typedef byte_t t_visible_type; /**< Тип видимости термина. */
typedef byte_t t_covering_type; /**< Тип покртия термином других терминов. */
typedef byte_t t_theme_type; /**< Тип темы: стат, сем и т.п. */
typedef byte_t t_method_type; /**< Тип метода */
//-------------------------------------------------------------------
/** Длина строковых переменных. */
#define PATH_LENGTH         127
#define NAME_LENGTH         63
#define WORD_LENGTH         63
#define RULE_LENGTH			63
#define PHRASE_LENGTH       127
#define DESC_LENGTH  		1023
#define TEXT_LENGTH  		50000

const t_errno NO_ERRORS				= 0;
const t_errno ERRORS				= 1; /**< Не специфицированная ошибка. */
const t_errno INIT_ERROR			= 2;
const t_errno OPEN_FILE_ERROR		= 3;
const t_errno LOAD_FILE_ERROR		= 4;

const t_errno TYPE_NOT_CORRECT		= 5;
const t_errno OUT_OF_BOUND			= 6;
const t_errno STRING_LENGTH_ERROR	= 7;  /**< Не соответствует длина строки . */

const t_errno OPERATION_ERROR		= 8;
const t_errno FIND_OBJECT_ERROR		= 9;
const t_errno STRING_ERROR			= 10;


const t_errno VOC_IS_EMPTY          = 20;
const t_errno WORD_FINDER_ERROR		= 21;
const t_errno NOT_ACTIVE_OBJECT_ERROR = 22;

const t_errno OPEN_TABLES_ERROR		= 23;
const t_errno LOAD_THEMES_ERROR		= 24;
const t_errno LOAD_MORPH_ERROR		= 25;

const t_errno ACTIVATION_ERROR		= 26;

//const t_errno ACTIVATION_ERROR		= 27;


//typedef byte_t t_visible_type; /**< Тип видимости термина. */

 /** Незначимый, используется только в составе других терминов (всегда невидим). */
const t_visible_type VISIBLE_NON	= 0;
 /** Самостоятельно значимый, если не покрыт другим термином (видим, если не покрыт). */
const t_visible_type VISIBLE_OWN	= 1;
 /** Абсолютно значимый, независимо от покрытия другими терминами (всегда видим). */
const t_visible_type VISIBLE_ABS	= 2;

//typedef byte_t t_covering_type; /**< Тип покртия термином других терминов. */

 /** Незначимо покрывает другие термины (покрытые термины видимы, если они не VISIBLE_NON). */
const t_covering_type COVERING_NO	= 0;
 /** Содержательно покрывает другие термины (покрытые термины невидимы, если они не VISIBLE_ABS). */
const t_covering_type COVERING_YES	= 1;
 /** Приоритетный термин при омонимии и пересечении 
  *  (покрывает вложенные, совпадающие границами и пересекающиеся термины). 
  */
const t_covering_type COVERING_PRIOR = 2;
 /** Содержательно покрывает другие термины (все покрытые термины невидимы включая VISIBLE_ABS). */
const t_covering_type COVERING_FULL	= 3;

//---------------------------------------------------------------------------
/** Параметры статуса для KNConcept (KNWord,KNPhrase). */
#define EXIST_MODE 		0  
#define STOP_MODE		1  
#define FIX_MODE		2  
#define EXPERT_MODE 	3  
#define DEL_MODE 		4
#define EDIT_MODE 		5  
#define NEW_MODE 		6  
#define PRED_MODE 		7  
//---------------------------------------------------------------------------
#define CONCEPT_TYPE        0
#define WORD_TYPE	        1
#define PHRASE_TYPE         2

/** Признак - тип не установлен (ошибка, такого быть не должно). */
const t_theme_type THEME_TYPE_BASE			= 0;
/** Признак - тема для классификации. */
const t_theme_type THEME_TYPE_STAT			= 1;
/** Признак - тема-вершина классификатора (если несколько классифкаторов). */
const t_theme_type THEME_TYPE_STAT_HEAD		= 2;
/** Признак - атрибут (без значения). */
const t_theme_type THEME_TYPE_ATTR			= 3;
/** Признак - значение атрибута (имя атрибута берется выше по иерархии). */
const t_theme_type THEME_TYPE_ATTR_VAL		= 4;
/** Признак - семнатический класс. */
const t_theme_type THEME_TYPE_SEM			= 5;
/** Признак - атрибут со значением, записанным как экспертная норма. */
const t_theme_type THEME_TYPE_ATTR_INTVAL 	= 6;
/** Признак - имя группы синонимов (нормализованное значение). */
const t_theme_type THEME_TYPE_SIN 			= 7;


const t_method_type METHOD_CLASS_BASE = 0;
const t_method_type METHOD_CLASS_PARAL1 = 1;
const t_method_type METHOD_CLASS_PARAL2 = 2;
const t_method_type METHOD_CLASS_PARAL3 = 3;
const t_method_type METHOD_CLASS_PARAL_BASE = 4;

/** Длина строковых переменных. */
#define PART_SPEECH_LENGTH  31
//-------------------------------------------------------------------
/** Тип активного словаря. */
#define WORD_VOC        	1
#define STOP_WORD_VOC   	2

#define PHRASE_VOC      	3
#define STOP_PHRASE_VOC 	4

#define CONCEPT_VOC      	6
#define STOP_CONCEPT_VOC 	7

#define DEL_WORD_VOC	 	0
#define DEL_PHRASE_VOC      5
//-------------------------------------------------------------------
/** Текущий статус понятия. */
#define TYPE_ORDINARY   0
#define TYPE_RENEWED    1
#define TYPE_NEW        2

/** Режимы обработки текста. */
#define FULL_UPDATE 			0
#define VOC_UPDATE				1
#define STATISTIC_UPDATE		2
#define MORPH_ANALISYS			3
#define CLASSIFICATION			4
#define CLASSIFICATION_UPDATE	5
#define STATISTIC_ANALISYS		7

#define WORK_ANALISYS			6
//#define WORK_STATISTIC			7
//#define WORK_CLASSIFICATION		8
//-------------------------------------------------------------------
/** Количественные хар-ки текста. */
/** все объектоы */
#define СOUNT_ALL	 			-1
/** все слова (с повторами) */
#define СOUNT_WORDS	 			0
/** слова из словаря значимых слов */
#define СOUNT_WORDS_TERMIN		1
/** слова из стоп-словаря */
#define СOUNT_WORDS_STOP		2
/** новые слова */
#define СOUNT_WORDS_NEW			10
/** кол-во неповторяющихся слов */
#define СOUNT_WORDS_UNIC		6
/** все СК (с повторами) */
#define СOUNT_PHRASES 			3
/** СК из словаря значимых СК */
#define СOUNT_PHRASES_TERMIN	4
/** СК из стоп-словаря */
#define СOUNT_PHRASES_STOP		5
/** новые СК */
#define СOUNT_PHRASES_NEW		11
/** кол-во неповторяющихся СК */
#define СOUNT_PHRASES_UNIC		7
//-------------------------------------------------------------------
/** Режимы загрузки иерархии тем. */
// Темы идентифицируются по id + названию
#define ID_NAME_MODE    false
// Темы идентифицируются по id, названия заменяются
#define ID_MODE         true
// Темы идентифицируются по названю, id заменяются
//#define NAME_MODE     2
//-------------------------------------------------------------------
//Название темы/признака по умолчанию
#define DEFULT_THEME "Вспомогательный"
//Название правила сборки СК по умолчанию
#define EXPERT_RULE 	"Эксперт"

//кол-во знаков после запятой для статистических параметров Норма и Эксперт
#define PARAMETR_LENGTH_ROUND 3
//кол-во терминов, относительно которого отображается частота термина
#define PARAMETR_FREQUENCY 100000
//максимальное кол-во тем
#define MAX_COUNT_OF_THEME 500000
// базовое кол-во тем
#define DEFOLTE_COUNT_OF_THEME 11
// мера близости
#define PROXIMITY 2
// порог (минимальная величина) встречаемости термина в выборке
#define TERM_THRESHOLD 30
// порог (минимальная величина) терминов в выборке по теме
#define THEME_THRESHOLD 200
// максимальное кол-во элементов в парадигме
#define MAX_PARADIGM_COUNT 200

/** Параметры для классификации */
/** порог необходимости */
#define NECESSITY_THRESHOLD 2
/** порог достаточности */
#define SUFFICIENCY_THRESHOLD 5

/** Параметры для WF. */
#define WF_PREDICTION	true
#define WF_USE_ALEX		false
#define WF_PHRASES		true
// Файлы лога обработчика
#define LOG_FILE		"speed_error.log"
#define LEMRULES_LOG_FILE		"lemrules_error.log"
#define GRAMTAB_LOG_FILE		"gramtab_error.log"
#define RULE_FILE		"rules.ini"
#define LEX_FILE  		"gramtab.ini"
#define LEM_RULE_FILE	"lemrules.ini"
#define LOG_LOAD		"load_voc_error.log"

/// functions snprintf, snprintf_* are deprecated in windows and thus
/// has a prefix '_'. This macros detects OS and substitutes proper name.
#if (defined(__WINDOWS__) || defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(_WIN64)) && !defined(__CYGWIN__)
#define SNPRINTF _snprintf
#else
#define SNPRINTF snprintf
#endif

//---------------------------------------------------------------------------
#endif
