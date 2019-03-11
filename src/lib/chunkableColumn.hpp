#pragma once

#include <fstream>
#include <string>
#include <type_traits>

#include "findAndReplace.hpp"

namespace PanCake
{
    template <typename T, typename = void>
    struct isChunkable : std::false_type {};

    template <typename T>
    struct isChunkable<T,
        std::void_t<
            decltype(std::declval<T&>().beginIR()),
            decltype(std::declval<T&>().functionSuffix),
            decltype(std::declval<T&>().contName)
        >> : std::true_type {};

    class ChunkableColumn
    {
        public:
            explicit ChunkableColumn(std::ofstream&_stream)
            {
                this->stream = &_stream;
            }

            template<class T>
            void addValueToChunk(const char*contName,T&val)
            {
                *this->stream<<"        "<<contName<<":add("<<val<<")\n";
            }

            template<class T>
            void addQuotedValueToChunk(const char*contName,T&val)
            {
                std::string lB = "[";
                std::string rB = "]";
                std::string eLB = "=[";
                std::string eRB = "]=";
                std::string escaped = PanCake::findAndReplace(val,lB,eLB);
                escaped = PanCake::findAndReplace(escaped,rB,eRB);
                *this->stream<<"        "<<contName<<":add([["<<escaped<<"]])\n";
            }

            void writeFunctionSignature(const char*functionSuffix)
            {
                *this->stream<<"function "<<this->functionName<<functionSuffix<<"("<<this->chunkIndexName<<")\n";
            }

            void beginChunk(int n)
            {
                *this->stream<<"    if n == "<<n<<" then\n";
            }

            void endChunk(int length)
            {
                *this->stream<<"        "<<this->chunkLength<<" = "<<length<<"\n";
                *this->stream<<"    end\n";
            }

            void endIR()
            {
                *this->stream<<"end\n";
            }

            void badStream(bool&badStream)
            {
                if(!this->stream->good())
                    badStream = true;
                else if(this->stream->bad())
                    badStream = true;
            }

            std::ofstream*stream;
            int itemsInChunk = 0;

            static constexpr const char*chunkIndexName = "n";
            static constexpr const char*functionName = "chunk";
            static constexpr const char*totalChunksFunctionName = "totalChunksIn";
            static constexpr const char*chunkLength = "chunkLength";
    };
}
