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

#ifndef __AUTO_POINTER_H__
#define __AUTO_POINTER_H__

namespace Gwen
{
    namespace Platform
    {
        //  base object counter class
        class Object
        {
            
        public:
            Object( void );
            ~Object( void );
            
            /// @brief increment the counter atomically, and return the old value
            /// @return the previous value of the counter
            uint32_t    IncrementReference( void );

            /// @brief decrement the counte atomically, and return the old value 
            /// @return the previous of the counter 
            uint32_t    DecrementReference( void );    
            
            /// @brief 
            /// @param in_ptr 
            /// @return 
            static uint32_t IncRef( void* in_ptr );

            /// @brief 
            /// @param in_ptr 
            /// @return 
            static uint32_t DecRef( void* in_ptr );

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
            explicit AutoPointer( const_pointer &in_ref );
            explicit AutoPointer( const_pointer in_pointr );
            ~AutoPointer( void );

            inline pointer operator = ( const_pointer &in_ref )
            {
                Decrement();
                m_pointer = in_ref;
                Increment();
                return m_pointer;
            }

            inline pointer operator=( pointer in_ptr )
            {
                Decrement();
                m_pointer = in_ptr;
                Increment();
                return m_pointer;
            }

            inline AutoPointer<_t> operator=( const AutoPointer<_t> &in_ref )
            {
                Decrement();
                m_pointer = in_ref.m_pointer;
                Increment();
                return *this;
            }

            // dynamic casting 
            template< class _u >
            inline AutoPointer<_t> operator=( const AutoPointer<_u> &in_ref )
            {
                Decrement();
                m_pointer = dynamic_cast<pointer>( in_ref.m_pointer );
                Increment();
                return *this;
            }

            inline pointer              operator -> ( void )
            {
                return m_pointer;
            }

	        inline const_pointer        operator -> ( void ) const
            {
                return m_pointer;
            }

	        inline pointer	            operator & ( void )
            {
                return m_pointer;
            }

	        inline const_pointer        operator & ( void ) const
            {
                return m_pointer;
            }

	        inline reference            operator *(void)
            {
                return m_pointer;
            }

	        inline const_reference      operator *( void ) const
            {
                return m_pointer;                
            }

            inline bool operator == ( const_pointer &ptr )
            {
                return m_pointer == ptr;
            }

            inline bool operator == ( const_pointer &ptr ) const
            {
                return m_pointer == ptr;
            }

            inline bool operator == ( const AutoPointer<_t> &in_ref )
            {
                return m_pointer == in_ref.m_pointer;
            }

            template< class _u >
            inline bool operator == ( const AutoPointer<_u> &in_ref )
            {
                return m_pointer == in_ref.m_pointer;
            }
            
            inline bool operator != ( const_pointer &ptr )
            {
                return m_pointer != ptr;
            }

            inline bool operator != ( const_pointer &ptr ) const
            {
                return m_pointer != ptr;
            }

            inline bool operator != ( const AutoPointer<_t> &in_ref )
            {
                return m_pointer != in_ref.m_pointer;
            }

            template< class _u >                
            inline bool operator != ( const AutoPointer<_u> &in_ref )
            {
                return m_pointer != &in_ref;
            }

	        inline explicit operator bool( void ) const noexcept
            {
                return m_pointer == nullptr;
            }

        private:
            pointer m_pointer;
            inline void Increment( void );
            inline void Decrement( void );

        };

        template<class _t>
        AutoPointer<_t>::AutoPointer( void ) : m_pointer( nullptr )
        {
        }
        
        template<class _t>
        AutoPointer<_t>::AutoPointer( const_pointer &in_ref )
        {
            Decrement();
            m_pointer = in_ref;
            Increment();
        }

        template <class _t>
        inline AutoPointer<_t>::AutoPointer( const_pointer in_pointr)
        {
            Decrement();
            m_pointer = const_cast<_t*>( in_pointr );
            Increment();
        }

        template<class _t>
        AutoPointer<_t>::~AutoPointer( void )
        {
            if( m_pointer == nullptr )
                return;
            
            Decrement();
        }

        template <class _t>
        inline void AutoPointer<_t>::Increment( void )
        {
            Object::DecRef( m_pointer );
        }

        template <class _t>
        inline void AutoPointer<_t>::Decrement( void )
        {
            if ( Object::DecRef( m_pointer ) <= 1 )
            {
                delete m_pointer;
                m_pointer = nullptr;
            }
        }
    };
};

#endif //__AUTO_POINTER_H__