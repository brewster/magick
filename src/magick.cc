#define BUILDING_NODE_EXTENSION
#include "file.h"

void Init(v8::Handle<v8::Object> target) {
  File::Init(target);
}

NODE_MODULE(magick, Init)
