#pragma once

namespace PanCake
{
    struct BulkImageDownloadStatus
    {
        int succeeded = 0;
        int failed = 0;
        int attempted = 0;
    };
}
