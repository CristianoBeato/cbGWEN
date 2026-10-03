/*
============================================================================================
	GWEN

	Copyright (c) 2010 Facepunch Studios.
	Copyright (c) 2025-2026 Cristiano Beato.

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
	namespace Controls
	{
		class Base;
	}

	namespace Skin
	{
		namespace Symbol
		{
			inline constexpr unsigned char None				= 0;
			inline constexpr unsigned char ArrowRight		= 1;
			inline constexpr unsigned char Check			= 2;
			inline constexpr unsigned char Dot				= 3;
		}

		class GWEN_EXPORT Base : public Object
		{
			public:
				typedef AutoPointer<Skin::Base>	Pointer;

				Base( Renderer::Base::Pointer renderer = Renderer::Base::Pointer() );
				
				virtual ~Base( void );

				virtual void ReleaseFont( Gwen::Font::Pointer fnt );
				
				virtual void DrawGenericPanel( AutoPointer<Controls::Base> control ) = 0;

				virtual void DrawButton( AutoPointer<Controls::Base> control, bool bDepressed, bool bHovered, bool bDisabled ) = 0;
				virtual void DrawTabButton( AutoPointer<Controls::Base> control, bool bActive, int dir ) = 0;
				virtual void DrawTabControl( AutoPointer<Controls::Base> control ) = 0;
				virtual void DrawTabTitleBar( AutoPointer<Controls::Base> control ) = 0;

				virtual void DrawMenuItem( AutoPointer<Controls::Base> control, bool bSubmenuOpen, bool bChecked ) = 0;
				virtual void DrawMenuStrip( AutoPointer<Controls::Base> control ) = 0;
				virtual void DrawMenu( AutoPointer<Controls::Base> control, bool bPaddingDisabled ) = 0;
				virtual void DrawMenuRightArrow( AutoPointer<Controls::Base> control ) = 0;

				virtual void DrawRadioButton( AutoPointer<Controls::Base> control, bool bSelected, bool bDepressed ) = 0;
				virtual void DrawCheckBox( AutoPointer<Controls::Base> control, bool bSelected, bool bDepressed ) = 0;
				virtual void DrawGroupBox( AutoPointer<Controls::Base> control, int textStart, int textHeight, int textWidth ) = 0;
				virtual void DrawTextBox( AutoPointer<Controls::Base> control ) = 0;

				virtual void DrawWindow( AutoPointer<Controls::Base> control, int topHeight, bool inFocus ) = 0;
				virtual void DrawWindowCloseButton( Gwen::AutoPointer<Controls::Base> control, bool bDepressed, bool bHovered, bool bDisabled ) = 0;
				virtual void DrawWindowMaximizeButton( Gwen::AutoPointer<Controls::Base> control, bool bDepressed, bool bHovered, bool bDisabled, bool bMaximized ) = 0;
				virtual void DrawWindowMinimizeButton( Gwen::AutoPointer<Controls::Base> control, bool bDepressed, bool bHovered, bool bDisabled ) = 0;

				virtual void DrawHighlight( AutoPointer<Controls::Base> control ) = 0;
				virtual void DrawStatusBar( AutoPointer<Controls::Base> control ) = 0;

				virtual void DrawShadow( AutoPointer<Controls::Base> control ) = 0;
				virtual void DrawScrollBarBar( AutoPointer<Controls::Base> control, bool bDepressed, bool isHovered, bool isHorizontal ) = 0;
				virtual void DrawScrollBar( AutoPointer<Controls::Base> control, bool isHorizontal, bool bDepressed ) = 0;
				virtual void DrawScrollButton( AutoPointer<Controls::Base> control, int iDirection, bool bDepressed, bool bHovered, bool bDisabled ) = 0;
				virtual void DrawProgressBar( AutoPointer<Controls::Base> control, bool isHorizontal, float progress ) = 0;

				virtual void DrawListBox( AutoPointer<Controls::Base> control ) = 0;
				virtual void DrawListBoxLine( AutoPointer<Controls::Base> control, bool bSelected, bool bEven ) = 0;

				virtual void DrawSlider( AutoPointer<Controls::Base> control, bool bIsHorizontal, int numNotches, int barSize ) = 0;
				virtual void DrawSlideButton( Gwen::AutoPointer<Controls::Base> control, bool bDepressed, bool bHorizontal ) = 0;

				virtual void DrawComboBox( AutoPointer<Controls::Base> control, bool bIsDown, bool bIsMenuOpen ) = 0;
				virtual void DrawComboDownArrow( Gwen::AutoPointer<Controls::Base> control, bool bHovered, bool bDown, bool bOpen, bool bDisabled ) = 0;
				virtual void DrawKeyboardHighlight( AutoPointer<Controls::Base> control, const Gwen::Rect & rect, int offset ) = 0;
				virtual void DrawToolTip( AutoPointer<Controls::Base> control ) = 0;

				virtual void DrawNumericUpDownButton( AutoPointer<Controls::Base> control, bool bDepressed, bool bUp ) = 0;

				virtual void DrawTreeButton( AutoPointer<Controls::Base> control, bool bOpen ) = 0;
				virtual void DrawTreeControl( AutoPointer<Controls::Base> control ) = 0;
				virtual void DrawTreeNode( AutoPointer<Controls::Base> ctrl, bool bOpen, bool bSelected, int iLabelHeight, int iLabelWidth, int iHalfWay, int iLastBranch, bool bIsRoot );

				virtual void DrawPropertyRow( Controls::Base* control, int iWidth, bool bBeingEdited, bool bHovered );
				virtual void DrawPropertyTreeNode( AutoPointer<Controls::Base> control, int BorderLeft, int BorderTop );
				virtual void DrawColorDisplay( AutoPointer<Controls::Base> control, Gwen::Color color ) = 0;
				virtual void DrawModalControl( AutoPointer<Controls::Base> control ) = 0;
				virtual void DrawMenuDivider( AutoPointer<Controls::Base> control ) = 0;

				virtual void DrawCategoryHolder( AutoPointer<Controls::Base> ctrl ) = 0;
				virtual void DrawCategoryInner( AutoPointer<Controls::Base> ctrl, bool bCollapsed ) = 0;


				virtual void SetRender( Gwen::Renderer::Base::Pointer renderer )
				{
					m_Render = renderer;
				}

				virtual Gwen::Renderer::Base::Pointer GetRender( void )
				{
					return m_Render;
				}

				virtual void DrawArrowDown( Gwen::Rect rect );
				virtual void DrawArrowUp( Gwen::Rect rect );
				virtual void DrawArrowLeft( Gwen::Rect rect );
				virtual void DrawArrowRight( Gwen::Rect rect );
				virtual void DrawCheck( Gwen::Rect rect );


				struct
				{
					struct Window_t
					{
						Gwen::Color TitleActive;
						Gwen::Color TitleInactive;

					} Window;

					struct Label_t
					{
						Gwen::Color Default;
						Gwen::Color Bright;
						Gwen::Color Dark;
						Gwen::Color Highlight;

					} Label;

					struct Tree_t
					{
						Gwen::Color Lines;
						Gwen::Color Normal;
						Gwen::Color Hover;
						Gwen::Color Selected;

					} Tree;

					struct Properties_t
					{
						Gwen::Color Line_Normal;
						Gwen::Color Line_Selected;
						Gwen::Color Line_Hover;
						Gwen::Color Column_Normal;
						Gwen::Color Column_Selected;
						Gwen::Color Column_Hover;
						Gwen::Color Label_Normal;
						Gwen::Color Label_Selected;
						Gwen::Color Label_Hover;
						Gwen::Color Border;
						Gwen::Color Title;

					} Properties;

					struct Button_t
					{
						Gwen::Color Normal;
						Gwen::Color Hover;
						Gwen::Color Down;
						Gwen::Color Disabled;

					} Button;

					struct Tab_t
					{
						struct Active_t
						{
							Gwen::Color Normal;
							Gwen::Color Hover;
							Gwen::Color Down;
							Gwen::Color Disabled;
						} Active;

						struct Inactive_t
						{
							Gwen::Color Normal;
							Gwen::Color Hover;
							Gwen::Color Down;
							Gwen::Color Disabled;
						} Inactive;

					} Tab;

					struct Category_t
					{
						Gwen::Color Header;
						Gwen::Color Header_Closed;

						struct Line_t
						{
							Gwen::Color Text;
							Gwen::Color Text_Hover;
							Gwen::Color Text_Selected;
							Gwen::Color Button;
							Gwen::Color Button_Hover;
							Gwen::Color Button_Selected;
						} Line;

						struct LineAlt_t
						{
							Gwen::Color Text;
							Gwen::Color Text_Hover;
							Gwen::Color Text_Selected;
							Gwen::Color Button;
							Gwen::Color Button_Hover;
							Gwen::Color Button_Selected;
						} LineAlt;

					} Category;

					Gwen::Color ModalBackground;
					Gwen::Color TooltipText;

				} Colors;


			public:
				virtual Font::Pointer GetDefaultFont( void );
				virtual void SetDefaultFont( const Gwen::UnicodeString & strFacename, const float fSize = 10.0f );

			protected:
				Gwen::Font::Pointer		m_DefaultFont;
				Renderer::Base::Pointer m_Render;
		};
	};
}
