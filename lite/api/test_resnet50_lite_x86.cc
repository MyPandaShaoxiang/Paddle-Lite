// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gflags/gflags.h>
#include <gtest/gtest.h>
#include <vector>
#include "lite/api/lite_api_test_helper.h"
#include "lite/api/paddle_api.h"
#include "lite/api/paddle_use_kernels.h"
#include "lite/api/paddle_use_ops.h"
#include "lite/api/paddle_use_passes.h"
#include "lite/api/test_helper.h"
#include "lite/utils/cp_logging.h"

namespace paddle {
namespace lite {

TEST(Resnet50, test_resnet50_lite_x86) {
  lite_api::CxxConfig config;
  config.set_model_dir(FLAGS_model_dir);
  config.set_valid_places({lite_api::Place{TARGET(kX86), PRECISION(kFloat)},
                           lite_api::Place{TARGET(kHost), PRECISION(kFloat)}});
  auto predictor = lite_api::CreatePaddlePredictor(config);

  auto input_tensor = predictor->GetInput(0);
  std::vector<int64_t> input_shape{1, 3, 224, 224};
  input_tensor->Resize(input_shape);
  auto* data = input_tensor->mutable_data<float>();
  int input_num = 1;
  for (int i = 0; i < input_shape.size(); ++i) {
    input_num *= input_shape[i];
  }
  for (int i = 0; i < input_num; i++) {
    data[i] = 1;
  }

  for (int i = 0; i < FLAGS_warmup; ++i) {
    predictor->Run();
  }

  auto start = GetCurrentUS();
  for (int i = 0; i < FLAGS_repeats; ++i) {
    predictor->Run();
  }

  LOG(INFO) << "================== Speed Report ===================";
  LOG(INFO) << "Model: " << FLAGS_model_dir << ", threads num " << FLAGS_threads
            << ", warmup: " << FLAGS_warmup << ", repeats: " << FLAGS_repeats
            << ", spend " << (GetCurrentUS() - start) / FLAGS_repeats / 1000.0
            << " ms in average.";

  // TODO(FrostML): open this check.
  /*std::vector<std::vector<float>> results;
  // i = 1
  results.emplace_back(std::vector<float>(
      {0.00024139918, 0.00020566184, 0.00022418296, 0.00041731037,
       0.0005366107,  0.00016948722, 0.00028638865, 0.0009257241,
       0.00072681636, 8.531815e-05,  0.0002129998,  0.0021168243,
       0.006387163,   0.0037145028,  0.0012812682,  0.00045948103,
       0.00013535398, 0.0002483765,  0.00076759676, 0.0002773295}));
  auto out = predictor->GetOutput(0);
  ASSERT_EQ(out->shape().size(), 2);
  ASSERT_EQ(out->shape()[0], 1);
  ASSERT_EQ(out->shape()[1], 1000);

  int step = 50;
  for (int i = 0; i < results.size(); ++i) {
    for (int j = 0; j < results[i].size(); ++j) {
      EXPECT_NEAR(out->data<float>()[j * step + (out->shape()[1] * i)],
                  results[i][j],
                  1e-6);
    }
  }*/
}

}  // namespace lite
}  // namespace paddle
