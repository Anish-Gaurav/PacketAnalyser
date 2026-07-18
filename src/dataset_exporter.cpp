#include "dataset_exporter.h"

namespace DPI
{

   DatasetExporter::DatasetExporter() : header_written_(false)
   {
   }

   DatasetExporter::~DatasetExporter()
   {
      close();
   }

   bool DatasetExporter::open(const std::string &filename)
   {
      file_.open(filename);

      if (!file_.is_open())
         return false;

      file_
          << "duration,"
          << "packets,"
          << "bytes,"
          << "avg_packet_size,"
          << "packets_per_second,"
          << "bytes_per_second,"
          << "upload_ratio,"
          << "download_ratio,"
          << "protocol,"
          << "label\n";

      header_written_ = true;

      return true;
   }

   void DatasetExporter::close()
   {
      if (file_.is_open())
         file_.close();
   }

   void DatasetExporter::exportSample(
       const FeatureVector &f,
       const std::string &label)
   {
      if (!file_.is_open())
         return;

      std::lock_guard<std::mutex> lock(mutex_);

      file_
          << f.duration << ","
          << f.total_packets << ","
          << f.total_bytes << ","
          << f.avg_packet_size << ","
          << f.packets_per_second << ","
          << f.bytes_per_second << ","
          << f.upload_ratio << ","
          << f.download_ratio << ","
          << static_cast<int>(f.protocol) << ","
          << label
          << "\n";
   }

}