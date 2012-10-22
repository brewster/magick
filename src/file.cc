#define BUILDING_NODE_EXTENSION
#include "file.h"

void File::Init(v8::Handle<v8::Object> target) {
  // Get ready
  ImageWrap::Init();

  // Get a template for the C++ object we're wrapping
  v8::Local<v8::FunctionTemplate> tplate = v8::FunctionTemplate::New(New);
  tplate->SetClassName(v8::String::NewSymbol("File"));
  tplate->InstanceTemplate()->SetInternalFieldCount(1);

  // Set the getString method on the prototype
  v8::Local<v8::ObjectTemplate> proto = tplate->PrototypeTemplate();
  proto->Set(v8::String::NewSymbol("getBuffer"),
    v8::FunctionTemplate::New(GetBuffer)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("release"),
    v8::FunctionTemplate::New(Release)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("dimensions"),
    v8::FunctionTemplate::New(Dimensions)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("setFormat"),
    v8::FunctionTemplate::New(SetFormat)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("resize"),
    v8::FunctionTemplate::New(Resize)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("crop"),
    v8::FunctionTemplate::New(Crop)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("resizeToFill"),
    v8::FunctionTemplate::New(ResizeToFill)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("opacity"),
    v8::FunctionTemplate::New(Opacity)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("blur"),
    v8::FunctionTemplate::New(Blur)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("charcoal"),
    v8::FunctionTemplate::New(Charcoal)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("paint"),
    v8::FunctionTemplate::New(Paint)->GetFunction()
  );
  proto->Set(v8::String::NewSymbol("sepia"),
    v8::FunctionTemplate::New(Sepia)->GetFunction()
  );

  // Set the constructor on the module
  target->Set(
    v8::String::NewSymbol("File"),
    v8::Persistent<v8::Function>::New(tplate->GetFunction())
  );
}

v8::Handle<v8::Value> File::GetBuffer(const v8::Arguments &args) {
  char *result;
  size_t length;

  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());
  thisOne->image->GetBlob(result, length);

  // We want to make sure we get a fast-buffer back
  // see: http://sambro.is-super-awesome.com/category/node-js/
  node::Buffer *slowBuffer = node::Buffer::New(result, length);
  v8::Local<v8::Object> globalObj = v8::Context::GetCurrent()->Global();
  v8::Local<v8::Function> bufferConstructor =
    v8::Local<v8::Function>::Cast(globalObj->Get(v8::String::New("Buffer")));
  v8::Handle<v8::Value> constructorArgs[3] =
    { slowBuffer->handle_, v8::Integer::New(length), v8::Integer::New(0) };
  v8::Local<v8::Object> actualBuffer =
    bufferConstructor->NewInstance(3, constructorArgs);

  MagickRelinquishMemory(result); // can also be delete[] result

  v8::HandleScope scope;
  return scope.Close(actualBuffer);
}

v8::Handle<v8::Value> File::Release(const v8::Arguments &args) {
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());
  thisOne->ReleaseImage();
  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Dimensions(const v8::Arguments &args) {
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  char *orig;
  thisOne->image->GetDimensionString(orig);
  v8::Local<v8::String> dim = v8::String::New(orig);
  delete[] orig;

  v8::HandleScope scope;
  return scope.Close(dim);
}

v8::Handle<v8::Value> File::SetFormat(const v8::Arguments &args) {
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  v8::String::AsciiValue format(args[0]);
  thisOne->image->SetFormat(*format);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Resize(const v8::Arguments &args) {
  int desiredWidth = args[0]->NumberValue();
  int desiredHeight = args[1]->NumberValue();
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->Resize(desiredWidth, desiredHeight);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Crop(const v8::Arguments &args) {
  int desiredWidth = args[0]->NumberValue();
  int desiredHeight = args[1]->NumberValue();
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->Crop(desiredWidth, desiredHeight);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::ResizeToFill(const v8::Arguments &args) {
  int desiredWidth = args[0]->NumberValue();
  int desiredHeight = args[1]->NumberValue();
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->ResizeToFill(desiredWidth, desiredHeight);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Opacity(const v8::Arguments &args) {
  float desiredOpacity = args[1]->NumberValue();
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->Opacity(desiredOpacity);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Blur(const v8::Arguments &args) {
  int sigma = args[0]->NumberValue();
  int radius = 0;
  if (args[1]->IsNumber()) {
    radius = args[1]->NumberValue();
  }
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->Blur(sigma, radius);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Charcoal(const v8::Arguments &args) {
  int sigma = args[0]->NumberValue();
  int radius = 0;
  if (args[1]->IsNumber()) {
    radius = args[1]->NumberValue();
  }
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->Charcoal(sigma, radius);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Paint(const v8::Arguments &args) {
  int radius = 0;
  if (args[0]->IsNumber()) {
    radius = args[0]->NumberValue();
  }
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->Paint(radius);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::Sepia(const v8::Arguments &args) {
  int threshold = args[0]->NumberValue();
  File *thisOne = node::ObjectWrap::Unwrap<File>(args.This());

  thisOne->image->Sepia(threshold);

  v8::HandleScope scope;
  return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value> File::New(const v8::Arguments &args) {
  File* thisOne = new File();
  thisOne->Wrap(args.This());

  v8::Local<v8::Object> buffer = args[0]->ToObject();
  char *data = node::Buffer::Data(buffer);
  size_t length = node::Buffer::Length(buffer);
  thisOne->image = new ImageWrap((void *) data, length);

  return args.This();
}

ImageWrap* File::GetImageWrap(void) {
  return this->image;
}

void File::ReleaseImage() {
  if (this->image) {
    delete this->image;
    this->image = 0;
  }
}

File::~File() {
  this->ReleaseImage();
}
