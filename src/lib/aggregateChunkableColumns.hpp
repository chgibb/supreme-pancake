#pragma once

namespace PanCake
{
    template<class... Chunkables>
    class AggregateChunkableColumns : private Chunkables...
    {
        private:
            template<class T,class... R>
            struct Helper
            {
                template<class C>
                static void addItem(AggregateChunkableColumns*_this,const C&c)
                {
                    static_cast<T*>(_this)->addItem(c);
                    Helper<R...>::addItem(_this,c);
                }

                static void beginIR(AggregateChunkableColumns*_this)
                {
                    static_cast<T*>(_this)->beginIR();
                    Helper<R...>::beginIR(_this);
                }

                template<class C>
                static void beginChunk(AggregateChunkableColumns*_this,const C&c)
                {
                    static_cast<T*>(_this)->beginChunk(c);
                    Helper<R...>::beginChunk(_this,c);
                }

                template<class C>
                static void endChunk(AggregateChunkableColumns*_this,const C&c)
                {
                    static_cast<T*>(_this)->endChunk(c);
                    Helper<R...>::endChunk(_this,c);
                }

                static void endIR(AggregateChunkableColumns*_this)
                {
                    static_cast<T*>(_this)->endIR();
                    Helper<R...>::endIR(_this);
                }

                template<class C>
                static void badStream(AggregateChunkableColumns*_this,C&c)
                {
                    static_cast<T*>(_this)->badStream(c);
                    Helper<R...>::badStream(_this,c);
                }
            };

            template<class T>
            struct Helper<T>
            {
                template<class C>
                static void addItem(AggregateChunkableColumns*_this,const C&c)
                {
                    static_cast<T*>(_this)->addItem(c);
                }
            
                static void beginIR(AggregateChunkableColumns*_this)
                {
                    static_cast<T*>(_this)->beginIR();
                }

                template<class C>
                static void beginChunk(AggregateChunkableColumns*_this,const C&c)
                {
                    static_cast<T*>(_this)->beginChunk(c);
                }

                template<class C>
                static void endChunk(AggregateChunkableColumns*_this,const C&c)
                {
                    static_cast<T*>(_this)->endChunk(c);
                }

                static void endIR(AggregateChunkableColumns*_this)
                {
                    static_cast<T*>(_this)->endIR();
                }

                template<class C>
                static void badStream(AggregateChunkableColumns*_this,C&c)
                {
                    static_cast<T*>(_this)->badStream(c);
                }
            };
    
        public:
            AggregateChunkableColumns() = delete;
        
            template<class... Out>
            AggregateChunkableColumns(Out&... out) : Chunkables(out)...{}
        
            template<class C>
            void addItem(const C&c)
            {
                Helper<Chunkables...>::addItem(this,c);
            }

            void beginIR()
            {
                Helper<Chunkables...>::beginIR(this);
            }

            template<class C>
            void beginChunk(const C&c)
            {
                Helper<Chunkables...>::beginChunk(this,c);
            }

            template<class C>
            void endChunk(const C&c)
            {
                Helper<Chunkables...>::endChunk(this,c);
            }

            void endIR()
            {
                Helper<Chunkables...>::endIR(this);
            }

            template<class C>
            void badStream(C&c)
            {
                Helper<Chunkables...>::badStream(this,c);
            }
    };
}
