#pragma once

#include <iostream>
#include <onnxruntime_cxx_api.h>

using namespace std;

class Embedder
{
public:
    Embedder();

private:
    Ort::Env env;
    Ort::SessionOptions sessionOptions;
    Ort::Session* session;
};