#include "Embedder.h"

Embedder::Embedder()
    : env(ORT_LOGGING_LEVEL_WARNING, "CodeSense"),
      session(nullptr)
{
    sessionOptions.SetGraphOptimizationLevel(
        GraphOptimizationLevel::ORT_ENABLE_ALL);

    session = new Ort::Session(
        env,
        L"../models/all-MiniLM-L6-v2/model.onnx",
        sessionOptions);

    cout << "ONNX model loaded successfully!" << endl;
}