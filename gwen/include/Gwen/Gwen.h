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

// can be referenced outside the source 
#include <cmath>
#include <string>
#include <vector>
#include <list>

#include "Gwen/Macros.h"
#include "Gwen/Config.h"
#include "Gwen/Exports.h"
#include "Gwen/Structures.h"
#include "Gwen/AutoPointer.h"
#include "Gwen/Platform/Platform.h"
#include "Gwen/Skin.h"
#include "Gwen/Align.h"

#ifndef GWEN_NO_ANIMATION
#include "Gwen/Anim.h"
#endif

// Enable the hook system (se Hook.h)
#define GWEN_HOOKSYSTEM

namespace Gwen
{
	namespace Controls
	{
		class Base;
		class Canvas;
	}

	namespace Renderer
	{
		class Base;
	}

	extern GWEN_EXPORT AutoPointer<Controls::Base>	HoveredControl;
	extern GWEN_EXPORT AutoPointer<Controls::Base>	KeyboardFocus;
	extern GWEN_EXPORT AutoPointer<Controls::Base>	MouseFocus;

} //namespace Gwen

#include "Gwen/Controls.h"