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
		GWEN_EXPORT bool TooltipActive();

		GWEN_EXPORT void Enable( Controls::Base* pControl );
		GWEN_EXPORT void Disable( Controls::Base* pControl );

		GWEN_EXPORT void ControlDeleted( Controls::Base* pControl );

		GWEN_EXPORT void RenderToolTip( Skin::Base* skin );
	}
}
