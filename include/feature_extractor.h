#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include "types.h"

namespace DPI
{

   struct FeatureVector
   {
      double duration = 0.0;

      uint64_t packets_in = 0;
      uint64_t packets_out = 0;

      uint64_t bytes_in = 0;
      uint64_t bytes_out = 0;

      uint64_t total_packets = 0;
      uint64_t total_bytes = 0;

      double avg_packet_size = 0.0;

      double packets_per_second = 0.0;

      double bytes_per_second = 0.0;

      double upload_ratio = 0.0;

      double download_ratio = 0.0;

      uint8_t protocol = 0;
   };

   class FeatureExtractor
   {
   public:
      FeatureVector extract(const Connection &conn) const;
   };

}

#endif