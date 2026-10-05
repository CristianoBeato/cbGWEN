/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

namespace Gwen
{
	namespace ToolTip
	{
		GWEN_EXPORT bool TooltipActive( void );

		GWEN_EXPORT void Enable( AutoPointer<Controls::Base> pControl );
		GWEN_EXPORT void Disable( AutoPointer<Controls::Base> pControl );

		GWEN_EXPORT void ControlDeleted( AutoPointer<Controls::Base> pControl );

		GWEN_EXPORT void RenderToolTip( AutoPointer<Skin::Base> skin );
	}
}
