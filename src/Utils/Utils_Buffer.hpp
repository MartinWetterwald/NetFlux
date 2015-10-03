#ifndef UTILS_BUFFER_HPP_
#define UTILS_BUFFER_HPP_

namespace NetFlux
{
    namespace Utils
    {
        template <unsigned int PAGESIZE>
        class Buffer
        {
        public:
            Buffer ( ) :
                mpbegin ( nullptr ),
                mpend ( nullptr ),
                frontCursor ( 0 ),
                backCursor ( 0 )
            {
            }

            ~Buffer ( )
            {
                while ( mpbegin )
                {
                    mpend = mpbegin;
                    mpbegin = mpbegin -> next;
                    delete mpend;
                }
            }

            inline unsigned int pageSize ( ) const
            {
                if ( ! mpbegin )
                {
                    return 0;
                }

                if ( mpbegin == mpend )
                {
                    return backCursor - frontCursor;
                }

                return PAGESIZE - frontCursor;
            }

            inline const void * pageContent ( ) const
            {
                if ( ! mpbegin )
                {
                    return 0;
                }
                return mpbegin -> data + frontCursor;
            }

            inline void append ( const void * data, unsigned int dataSize )
            {
                const unsigned char * d = ( const unsigned char * ) data;
                unsigned int remainingSize;
                unsigned int readedSize = 0;

                for ( ; ; )
                {
                    if ( backCursor == 0 )
                    {
                        if ( mpbegin )
                        {
                            mpend -> next = new Page;
                            mpend = mpend -> next;
                        }
                        else
                        {
                            mpbegin = mpend = new Page;
                        }
                        mpend -> next = nullptr;
                    }

                    remainingSize = PAGESIZE - backCursor;

                    if ( dataSize - readedSize > remainingSize )
                    {
                        memcpy ( mpend -> data + backCursor, d + readedSize, remainingSize );
                        readedSize += remainingSize;
                        backCursor = 0;
                        continue;
                    }

                    memcpy ( mpend -> data + backCursor, d + readedSize, dataSize - readedSize );
                    if ( dataSize - readedSize == remainingSize )
                    {
                        backCursor = 0;
                    }
                    else
                    {
                        backCursor += dataSize - readedSize;
                    }
                    break;
                }
            }

            inline bool acquit ( unsigned int acquitSize )
            {
                if ( acquitSize > pageSize ( ) )
                {
                    return false;
                }

                frontCursor += acquitSize;

                if ( frontCursor == PAGESIZE )
                {
                    Page * tmp = mpbegin;
                    mpbegin = mpbegin -> next;
                    delete tmp;
                    frontCursor = 0;
                }

                else if ( mpbegin == mpend && frontCursor == backCursor )
                {
                    delete mpbegin;
                    mpbegin = nullptr;
                    mpend = nullptr;
                    backCursor = 0;
                    frontCursor = 0;
                }

                return true;
            }

        protected:
            struct Page
            {
                Page * next;
                unsigned char data [ PAGESIZE ];
            };

            Page * mpbegin;
            Page * mpend;
            unsigned int frontCursor;
            unsigned int backCursor;

        private:
            Buffer ( const Buffer & ) = delete;
            Buffer & operator= ( const Buffer & ) = delete;
        };
    }
}

#endif
