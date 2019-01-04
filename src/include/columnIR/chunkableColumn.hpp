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

            void writeFunctionSignature(std::string&functionSuffix)
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
                *this->stream<<"end";
            }

            std::ofstream*stream;
            int itemsInChunk = 0;

            std::string containerName = "cont";
            std::string chunkIndexName = "n";
            std::string functionName = "chunk";
    };
}
