/******************************************************************************
 * File: IKNParsedText.h
 * Description: Common text parser.
 * ----------------------------------------------------------------------------
 * Created: 15.03.2012 by Lena Sidorova (IIS) <lena@iis.nsk.su>
 ******************************************************************************/

#ifndef IKNParsedText_h
#define IKNParsedText_h

//-----------------------------------------------------------------------------
enum AType
{
	t_unknown = 0, // unknown (other) char
	t_delim,       // space, tab
	t_para,        // \r, \n
	t_punct,       // ,.!?:;-<>{}[]()\|/~`'"+=_@#$%^&*
	t_digit,       // 0123456789
	t_rus,         // russian characters
	t_eng          // english characters
};

//-----------------------------------------------------------------------------
class IKNAtom
{
public:
	virtual const char* GetData() const = 0;
	virtual const wchar_t* GetDataW() const = 0;
	virtual unsigned GetId() const = 0;
	virtual unsigned GetTextPos() const = 0;
	virtual AType GetType() const = 0;
};
//-----------------------------------------------------------------------------
class IKNParsedText
{
public:
    /* ѕолучить количество атомов. */
    virtual unsigned GetCount() const = 0;
    /* ѕолучить атом по индексу (без проверки на диапазон позиции). */
    virtual const IKNAtom* Get( unsigned id ) const = 0;

    /* ѕо текстовой позиции получить индекс(бинарный поиск). */
    virtual unsigned GetIndex( unsigned iTextPos ) const = 0;
    /* ѕо индексу получить текстовую позицию (на начало элемента в тексте). */
    virtual unsigned GetTextPos( unsigned id, unsigned* oTextEndPos ) const = 0;

    /* ѕолучить атом по текстовой позиции. */
    virtual const IKNAtom* Find( unsigned iTextPos ) const =0;
};
//-----------------------------------------------------------------------------
#endif // IKNParser_h
