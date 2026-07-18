#ifndef DATASET_EXPORTER_H
#define DATASET_EXPORTER_H

#include <fstream>
#include <mutex>
#include <string>

#include "feature_extractor.h"

namespace DPI
{

   class DatasetExporter
   {
   public:
      DatasetExporter();

      ~DatasetExporter();

      bool open(const std::string &filename);

      void close();

      void exportSample(
          const FeatureVector &feature,
          const std::string &label);

   private:
      std::ofstream file_;

      std::mutex mutex_;

      bool header_written_;
   };

}

#endif