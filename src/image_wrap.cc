#define BUILDING_NODE_EXTENSION
#include "image_wrap.h"

MagickWand* ImageWrap::GetWand(void) {
  return this->baseWand;
}

void ImageWrap::GetBlob(char *& out, size_t &length) {
  out = (char *) MagickGetImageBlob(this->baseWand, &length);
}

void ImageWrap::GetDimensionString(char *& out) {
  out = new char[10];
  sprintf(
    out,
    "%ux%u",
    (unsigned int) this->GetOriginalWidth(),
    (unsigned int) this->GetOriginalHeight()
  );
}

void ImageWrap::SetFormat(char *format) {
  MagickSetImageFormat(this->baseWand, format);
}

void ImageWrap::Resize(int dw, int dh) {
  MagickResizeImage(this->baseWand, dw, dh, LanczosFilter, 1.0);
}

void ImageWrap::Crop(int dw, int dh) {
  MagickCropImage(this->baseWand, dw, dh, 0, 0);
}

void ImageWrap::ResizeToFill(int dw, int dh) {
  int width = MagickGetImageWidth(this->baseWand);
  int height = MagickGetImageHeight(this->baseWand);
  if (dw != width || dh != height) {
    float xscale = (float) dw / width;
    float yscale = (float) dh / height;
    float scale = xscale > yscale ? xscale : yscale;
    MagickResizeImage(
      this->baseWand,
      scale * width + 0.5,
      scale * height + 0.5,
      LanczosFilter,
      1.0
    );
    width = MagickGetImageWidth(this->baseWand); // TODO figure from scale
    height = MagickGetImageHeight(this->baseWand);
    MagickCropImage(
      this->baseWand,
      dw,
      dh,
      (dw > width ? dw - width : width - dw) / 2,
      (dh > height ? dh - height : height - dh) / 2
    );
    MagickResetImagePage(this->baseWand, "");
  }
}

void ImageWrap::Opacity(float opacity) {
  MagickSetImageOpacity(this->baseWand, opacity);
}

void ImageWrap::Blur(int sigma, int radius) {
  MagickBlurImage(this->baseWand, radius, sigma);
}

void ImageWrap::Charcoal(int sigma, int radius) {
  MagickCharcoalImage(this->baseWand, radius, sigma);
}

void ImageWrap::Paint(int radius) {
  MagickOilPaintImage(this->baseWand, radius);
}

void ImageWrap::Sepia(int threshold) {
  MagickSepiaToneImage(this->baseWand, threshold);
}

ImageWrap::ImageWrap(void *data, size_t length) {
  this->baseWand = NewMagickWand();
  MagickReadImageBlob(this->baseWand, data, length);
}

ImageWrap::~ImageWrap() {
  DestroyMagickWand(this->baseWand);
}

// static
void ImageWrap::Shutdown() { MagickWandTerminus(); }
void ImageWrap::Init()     { MagickWandGenesis();  }
