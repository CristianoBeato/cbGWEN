/*
============================================================================================
	GWEN

	Copyright (c) 2010 Facepunch Studios.
	Copyright (c) 2025 Cristiano Beato.

	MIT License

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
============================================================================================
*/

#pragma once

#include "Gwen/Exports.h"
#include <string>

namespace Gwen
{
	namespace Controls
	{
		class Base;
		class Canvas;
	}

	enum CursorType : uint8_t
	{
		CURSOR_NORMAL	= 0,
		CURSOR_BEAM,
		CURSOR_SIZENS,
		CURSOR_SIZEWE,
		CURSOR_SIZENWSE,
		CURSOR_SIZENESW,
		CURSOR_SIZEALL,
		CURSOR_NO,
		CURSOR_WAIT,
		CURSOR_FINGER,
		CURSOR_COUNT
	};

	typedef std::wstring UnicodeString;
	typedef std::string String;

	typedef wchar_t UnicodeChar; // Portability??

	struct GWEN_EXPORT Margin
	{
		Margin( int left_ = 0, int top_ = 0, int right_ = 0, int bottom_ = 0 )
		{
			this->top = top_;
			this->bottom = bottom_;
			this->left = left_;
			this->right = right_;
		}

		Margin operator + ( const Margin & margin ) const
		{
			Margin m;
			m.top		= top + margin.top;
			m.bottom	= bottom + margin.bottom;
			m.left		= left + margin.left;
			m.right		= right + margin.right;
			return m;
		}

		int top, bottom, left, right;
	};


	typedef Margin Padding;


	struct GWEN_EXPORT Rect
	{
		Rect( int x_ = 0, int y_ = 0, int w_ = 0, int h_ = 0 )
		{
			this->x = x_;
			this->y = y_;
			this->w = w_;
			this->h = h_;
		}

		Rect operator + ( const Rect & rct ) const
		{
			Rect m;
			m.x		= x + rct.x;
			m.y		= y + rct.y;
			m.w		= w + rct.w;
			m.h		= h + rct.h;
			return m;
		}

		int x, y, w, h;
	};


	struct GWEN_EXPORT Point
	{
		Point( int x_ = 0, int y_ = 0 )
		{
			this->x = x_;
			this->y = y_;
		}

		void operator += ( const Point & p )
		{
			x += p.x;
			y += p.y;
		}

		Point operator + ( const Point & p ) const
		{
			return Point( x + p.x, p.y + y );
		}

		void operator -= ( const Point & p )
		{
			x -= p.x;
			y -= p.y;
		}

		Point operator - ( const Point & p ) const
		{
			return Point( x - p.x, y - p.y );
		}

		int x, y;
	};

	struct GWEN_EXPORT HSV
	{
		float h;
		float s;
		float v;
	};

	struct GWEN_EXPORT Color
	{
		Color( const uint8_t r_ = 255, const uint8_t g_ = 255, const uint8_t b_ = 255, const uint8_t a_ = 255 )
		{
			r = r_;
			g = g_;
			b = b_;
			a = a_;
		}

		void operator = ( const Color &c )
		{
			r = c.r;
			g = c.g;
			b = c.b;
			a = c.a;
		}

		void operator += ( const Color &c )
		{
			r += c.r;
			g += c.g;
			b += c.b;
			a += c.a;
		}

		void operator -= ( const Color &c )
		{
			r -= c.r;
			g -= c.g;
			b -= c.b;
			a -= c.a;
		}

		void operator *= ( float f )
		{
			// We can SIMDize this ?
			r = static_cast<uint8_t>( static_cast<float>( r ) * f );
			g = static_cast<uint8_t>( static_cast<float>( g ) * f );
			b = static_cast<uint8_t>( static_cast<float>( b ) * f );
			a = static_cast<uint8_t>( static_cast<float>( a ) * f );
		}

		inline Color operator * ( float f )
		{
			return Color(
					   ( float ) this->r * f,
					   ( float ) this->g * f,
					   ( float ) this->b * f,
					   ( float ) this->a * f
				   );
		}

		inline Color operator - ( const Color &c )
		{
			return Color( r - c.r, g - c.g, b - c.b, a - c.a );
		}

		inline Color operator + ( const Color &c )
		{
			return Color( r + c.r, g + c.g, b + c.b, a + c.a );
		}

		bool operator == ( const Color & c ) const
		{
			return c.r == r && c.g == g && c.b == b && c.a == a;
		}

		uint8_t r, g, b, a;
	};

	namespace Colors
	{
		// TODO: extern and define in a header 
		static const Color Black( 0, 0, 0, 255 );
		static const Color Red( 255, 0, 0, 255 );
		static const Color Yellow( 255, 255, 0, 255 );
		static const Color White( 255, 255, 255, 255 );
		static const Color Blue( 0, 0, 255, 255 );
		static const Color Green( 0, 255, 0, 255 );
		static const Color Grey( 200, 200, 200, 255 );
		static const Color GreyLight( 230, 230, 230, 255 );
		static const Color GwenPink( 255, 65, 199, 255 );
	};
}
