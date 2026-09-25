/*
============================================================================================
	cbGWEN

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
    //  base object counter class
    class Object
    {
    public:
        Object( void ) : m_count( 0 ) // We create the object whith new 
        {
        }

        virtual ~Object( void )
        {
        }
            
        /// @brief increment the counter atomically, and return the old value
        /// @return the previous value of the counter
        uint32_t    IncrementReference( void )
        {
            return m_count.fetch_add( 1, std::memory_order_relaxed );
        }
    
        /// @brief decrement the counte atomically, and return the old value 
        /// @return the previous of the counter 
        uint32_t    DecrementReference( void )
        {
            return m_count.fetch_sub( 1, std::memory_order_acq_rel );
        }    
            
        /// @brief 
        /// @param in_ptr 
        /// @return 
        static uint32_t IncRef( Object* in_ptr )
        {
            if( in_ptr == nullptr )
                return 0;

            return in_ptr->IncrementReference();
        }

        /// @brief 
        /// @param in_ptr 
        /// @return 
        static uint32_t DecRef( Object* &in_ptr )
        {
            if( in_ptr == nullptr )
                return 0;

            uint32_t old_count = in_ptr->DecrementReference();
            if( old_count == 1 )
            {
                delete in_ptr;
                in_ptr = nullptr;
            }
        }

    private:
        std::atomic<uint32_t>   m_count;
    };
        
    template<class _t>
    class AutoPointer
    {    
    public:
        typedef _t          value_type;
	    typedef _t&         reference;
	    typedef const _t&   const_reference;
	    typedef _t*         pointer;
	    typedef const _t*   const_pointer;
	    typedef const _t*&  pointer_reference;
	    typedef const _t*&  const_pointer_reference;

        AutoPointer( void );
        AutoPointer( const AutoPointer<_t> & in_ref );
        AutoPointer( const_pointer &in_ref );
        ~AutoPointer( void );

        // dynamic casting 
        template< class _u >
        inline AutoPointer<_t> &operator= ( const AutoPointer<_u> &in_ref );
        inline AutoPointer<_t>  operator= ( const_pointer &in_ref );
        inline AutoPointer<_t>  operator= ( pointer in_ptr );
        inline AutoPointer<_t>  operator= ( const AutoPointer<_t> &in_ref );
        inline pointer          operator -> ( void );
	    inline const_pointer    operator -> ( void ) const;
	    inline pointer	        operator & ( void );
	    inline const_pointer    operator & ( void ) const;
	    inline reference        operator *(void);
	    inline const_reference  operator *( void ) const;
        
        
        inline bool operator == ( const const_pointer &ptr );
        inline bool operator == ( const const_pointer &ptr ) const;
        inline bool operator == ( const AutoPointer<_t> &in_ref );

        inline bool operator != ( const_pointer &ptr );
        inline bool operator != ( const_pointer &ptr ) const;
        inline bool operator != ( const AutoPointer<_t> &in_ref );
	    inline explicit operator bool( void ) const noexcept;
        
        template< class _u >
        inline bool operator == ( const AutoPointer<_u> &in_ref );    

        template< class _u >                
        inline bool operator != ( const AutoPointer<_u> &in_ref );
        
    private:
            pointer m_pointer;
    };

    template <class _t>
    inline AutoPointer<_t>::AutoPointer( void ) : m_pointer( nullptr )
    {
    }

    template <class _t>
    inline AutoPointer<_t>::AutoPointer(const AutoPointer<_t> &in_ref ) : m_pointer( nullptr ) /* prevent gargbage */
    {
        if( in_ref )
        {
            m_pointer = in_ref.m_pointer;
            Object::IncRef( dynamic_cast<Object*>( m_pointer ) );
        }
    }

    template <class _t>
    inline AutoPointer<_t>::AutoPointer(const_pointer &in_ref) : m_pointer( nullptr ) /* prevent gargbage */
    {
        m_pointer = in_ref;        
        if( m_pointer )
        {
            Object::IncRef( dynamic_cast<Object*>( m_pointer ) );
        }
    }

    template <class _t>
    inline AutoPointer<_t>::~AutoPointer(void)
    {
        if( m_pointer )
        {
            
            Object::DecRef( m_pointer );
            m_pointer = nullptr;
        }
    }

    template <class _t>
    template <class _u>
    inline AutoPointer<_t> &AutoPointer<_t>::operator=(const AutoPointer<_u> &in_ref)
    {
        if( m_pointer )
        {
            Object::DecRef( m_pointer );
            m_pointer = nullptr;
        }

        m_pointer = dynamic_cast<_t>( in_ref.m_pointer );

        if( m_pointer )
            Object::IncRef( m_pointer );

        return *this;
    }

};
