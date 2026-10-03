/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

#include <string>

namespace Gwen
{
	namespace Renderer
	{
		class Base; 
	}

	//
	// Texture
	//
	class Texture : public Object
	{
	public:
		typedef AutoPointer<Texture>	Pointer;
		typedef std::list<Texture*>		List;

		Texture( void );
		~Texture( void );

		void Load( const TextObject & str, AutoPointer<Renderer::Base> render );
		void Release( AutoPointer<Renderer::Base> render );
		bool FailedToLoad( void ) const;

		bool	failed;
		int		width;
		int		height;
		TextObject	name;
		void*	data;
	};
}
