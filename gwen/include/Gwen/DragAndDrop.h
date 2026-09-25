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

namespace Gwen
{
	namespace DragAndDrop
	{
		class GWEN_EXPORT Package : public Object
		{
		public:
			typedef AutoPointer<Package> pointer;


			Package( void )
			{
				userdata = nullptr;
				draggable = false;
				drawcontrol = nullptr;
				holdoffset = Gwen::Point( 0, 0 );
			}

			String	name;
			void*	userdata;
			bool	draggable;

			AutoPointer<Controls::Base>	drawcontrol;
			Point						holdoffset;
		};
		
		
		extern GWEN_EXPORT Package*	CurrentPackage;
		extern GWEN_EXPORT AutoPointer<Controls::Base>	SourceControl;
		extern GWEN_EXPORT AutoPointer<Controls::Base>	HoveredControl;
		bool GWEN_EXPORT Start( AutoPointer<Controls::Base> pControl, AutoPointer<Package> pPackage );
		bool GWEN_EXPORT OnMouseButton( AutoPointer<Controls::Base> pHoveredControl, const int x, const int y, const bool bDown );
		void GWEN_EXPORT OnMouseMoved( AutoPointer<Controls::Base> pHoveredControl, const int x, const int y );
		void GWEN_EXPORT RenderOverlay( AutoPointer<Controls::Canvas> pCanvas, AutoPointer<Skin::Base> skin );
		void GWEN_EXPORT ControlDeleted( AutoPointer<Controls::Base> pControl );
	}

}
