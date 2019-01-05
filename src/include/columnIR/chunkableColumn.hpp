#pragma once

#include <fstream>
#include <string>

namespace PanCake
{
    class ChunkableColumn
    {
        public:
            explicit ChunkableColumn(std::ofstream&_stream)
            {
                this->stream = &_stream;
            }

            template<class T>
            void addValueToChunk(T&val)
            {
                *this->stream<<"        "<<this->containerName<<":add("<<val<<")\n";
            }

            template<class T>
            void addQuotedValueToChunk(T&val)
            {
                *this->stream<<"        "<<this->containerName<<":add([["<<val<<"]])\n";
            }

            void writeFunctionSignature(const char*functionSuffix)
            {
                *this->stream<<"function "<<this->functionName<<functionSuffix<<"("<<this->containerName<<","<<this->chunkIndexName<<")\n";
            }

            void beginChunk(int n)
            {
                *this->stream<<"    if n == "<<n<<" then\n";
            }

            void endChunk()
            {
                *this->stream<<"    end\n";
            }

            void endIR()
            {
                *this->stream<<"end\n";
            }

            void _writeTotalChunksFunction(int totalChunks,const char*functionSuffix)
            {
                *this->stream<<"function "<<this->totalChunksFunctionName<<functionSuffix<<"()\n";
                *this->stream<<"    return "<<totalChunks<<"\n";
                *this->stream<<"end";
            }

            std::ofstream*stream;
            int itemsInChunk = 0;

            static constexpr const char*containerName = "cont";
            static constexpr const char*chunkIndexName = "n";
            static constexpr const char*functionName = "chunk";
            static constexpr const char*totalChunksFunctionName = "totalChunksIn";
    };
}
