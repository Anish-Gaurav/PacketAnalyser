#include "feature_extractor.h"

#include <chrono>

namespace DPI
{

   FeatureVector FeatureExtractor::extract(
       const Connection &conn) const
   {
      FeatureVector fv;

      fv.protocol = conn.tuple.protocol;

      fv.packets_in = conn.packets_in;
      fv.packets_out = conn.packets_out;

      fv.bytes_in = conn.bytes_in;
      fv.bytes_out = conn.bytes_out;

      fv.total_packets =
          fv.packets_in +
          fv.packets_out;

      fv.total_bytes =
          fv.bytes_in +
          fv.bytes_out;

      double duration =
          std::chrono::duration<double>(
              conn.last_seen -
              conn.first_seen)
              .count();

      if (duration <= 0.0)
         duration = 0.001;

      fv.duration = duration;

      if (fv.total_packets)
      {
         fv.avg_packet_size =
             static_cast<double>(fv.total_bytes) /
             fv.total_packets;
      }

      fv.packets_per_second =
          static_cast<double>(fv.total_packets) /
          duration;

      fv.bytes_per_second =
          static_cast<double>(fv.total_bytes) /
          duration;

      if (fv.total_bytes)
      {
         fv.upload_ratio =
             static_cast<double>(fv.bytes_out) /
             fv.total_bytes;

         fv.download_ratio =
             static_cast<double>(fv.bytes_in) /
             fv.total_bytes;
      }

      return fv;
   }

}