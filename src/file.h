#ifndef __FILE_H__
#define __FILE_H__

#include <node.h>
#include <node_buffer.h>
#include "image_wrap.h"

class File : public node::ObjectWrap {

  public:

  static void Init(v8::Handle<v8::Object> target);

  ~File();
  ImageWrap* GetImageWrap(void);

  private:

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> GetBuffer(const v8::Arguments &args);
  static v8::Handle<v8::Value> Release(const v8::Arguments &args);
  static v8::Handle<v8::Value> Dimensions(const v8::Arguments &args);
  static v8::Handle<v8::Value> SetFormat(const v8::Arguments &args);
  static v8::Handle<v8::Value> Resize(const v8::Arguments &args);
  static v8::Handle<v8::Value> Crop(const v8::Arguments &args);
  static v8::Handle<v8::Value> ResizeToFill(const v8::Arguments &args);
  static v8::Handle<v8::Value> Opacity(const v8::Arguments &args);
  static v8::Handle<v8::Value> Blur(const v8::Arguments &args);
  static v8::Handle<v8::Value> Charcoal(const v8::Arguments &args);
  static v8::Handle<v8::Value> Paint(const v8::Arguments &args);
  static v8::Handle<v8::Value> Sepia(const v8::Arguments &args);

  void ReleaseImage();

  ImageWrap *image;

};

#endif
