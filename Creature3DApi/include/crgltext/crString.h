/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/
#ifndef CRGLTEXT_STRING
#define CRGLTEXT_STRING 1

#include <CRCore/Referenced.h>
#include <CRGLText/crExport.h>

#include <vector>
#include <set>
#include <string>

namespace CRGLText {

class crText;

#ifndef _MSC_VER

typedef std::vector<unsigned int> VectorUInt;

#else // _MSC_VER

class VectorUInt: public std::vector<unsigned int> {
	typedef std::vector<value_type> inherited;
public:
	VectorUInt(): inherited() {}
	explicit VectorUInt(size_type n): inherited(n) {}
	VectorUInt(const VectorUInt &copy): inherited(copy) {}
	//VectorUInt(value_type *beg_, value_type *end_): inherited(beg_, end_) {}
	template<class InputIterator>
	VectorUInt(InputIterator beg_, InputIterator end_): inherited(beg_, end_) {}
};

#endif

class CRGLTEXT_EXPORT crString : public CRCore::Referenced, public VectorUInt
{
public:

    /**
     * Types of string encodings supported
     */
    enum Encoding
    {
        ENCODING_UNDEFINED,                 /// not using Unicode
        ENCODING_ASCII = ENCODING_UNDEFINED,/// unsigned char ASCII
        ENCODING_UTF8,                      /// 8-bit unicode transformation format
        ENCODING_UTF16,                     /// 16-bit signature
        ENCODING_UTF16_BE,                  /// 16-bit big-endian
        ENCODING_UTF16_LE,                  /// 16-bit little-endian
        ENCODING_UTF32,                     /// 32-bit signature
        ENCODING_UTF32_BE,                  /// 32-bit big-endian
        ENCODING_UTF32_LE,                  /// 32-bit little-endian
        ENCODING_SIGNATURE                  /// detect encoding from signature
    };


    crString() {}
	crString(const crString& str):CRCore::Referenced(),CRGLText::VectorUInt(str){}
    crString(const std::string& str) { set(str); }
    crString(const wchar_t* text) { set(text); }
    crString(const std::string& text,Encoding encoding) { set(text,encoding); }

    virtual ~crString() {} // public temporily while crText is still in flux.

    crString& operator = (const crString& str);

    void set(const std::string& str);

    /** Set the text using a wchar_t string, 
      * which is converted to an internal TextString.*/
    void set(const wchar_t* text);

    /** Set the text using a Unicode encoded std::string, which is converted to an internal TextString.
      * The encoding parameter specificies which Unicode encodeding is used in the std::string. */
    void set(const std::string& text,Encoding encoding);

    /** returns a UTF8 encoded version of this crText::crString.*/
    std::string createUTF8EncodedString() const;

protected:

};

}


#endif
