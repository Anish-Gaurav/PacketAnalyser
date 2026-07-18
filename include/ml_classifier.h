#ifndef ML_CLASSIFIER_H
#define ML_CLASSIFIER_H

#include <string>
#include <vector>
#include <memory>

#include "feature_extractor.h"

#include <onnxruntime_cxx_api.h>

namespace DPI
{

   //==============================================================
   // Result returned by the ML model
   //==============================================================

   struct Prediction
   {
      std::string label;

      float confidence = 0.0f;

      int class_id = -1;
   };

   //==============================================================
   // ONNX Runtime wrapper
   //==============================================================

   class MLClassifier
   {
   public:
      MLClassifier();

      ~MLClassifier();

      // Load exported ONNX model
      bool loadModel(const std::string &modelPath);

      // Perform inference
      Prediction predict(const FeatureVector &feature);

      bool isLoaded() const;

   private:
      // ONNX Runtime
      Ort::Env env_;

      Ort::SessionOptions session_options_;

      std::unique_ptr<Ort::Session> session_;

      Ort::MemoryInfo memory_info_;

      bool loaded_;

      // Cached model metadata
      std::vector<std::string> input_names_;

      std::vector<std::string> output_names_;

      // Labels corresponding to model outputs
      std::vector<std::string> labels_;

   private:
      std::vector<float> featureToTensor(
          const FeatureVector &feature) const;
   };

}

#endif