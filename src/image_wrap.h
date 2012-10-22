#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdio.h>
#include <wand/MagickWand.h>

class ImageWrap {

  public:

  // Initialize the necessary components needed by ImageWrap
  // Should be called before using any ImageWrap objects
  static void Init();

  // Let go of any setup created by Init()
  // Should be called after use of ImageWrap objects is over
  static void Shutdown();

  // Create a new ImageWrap from the given data & size
  ImageWrap(void *, size_t);

  // Destruct an ImageWrap
  ~ImageWrap();

  // Get the blob of the image as a (char *) and (size_t) which
  // represents the length of the blob
  void GetBlob(char *&, size_t &);

  // Get the dimensions of the ImageWrap in a (char *)
  // of the format "#{w}x#{h}" set into the given reference
  void GetDimensionString(char *&);

  // Set the format of the ImageWrap ("jpg", "png", etc)
  void SetFormat(char *);

  // Perform a resize operation to the given width and height
  void Resize(int, int);

  // Perform a crop to the given width and height
  void Crop(int, int);

  // Perform a ResizeToFill operation to the given width and height.
  // This is a resize operation very similar to that employed on Flickr,
  // where the resize uses the largest portion of the image possible.
  // If we are resizing a image which is wider than it is tall down to
  // a square image, the result will use the entire vertical dimension,
  // and then center on the horizontal dimension.
  void ResizeToFill(int, int);

  // Set the opacity of the ImageWrap, as a float - where 0.0 represents
  // full transparency and 1.0 represents full opacity.
  void Opacity(float);

  // Perform a blur on the image using the passed sigma and optional radius
  void Blur(int, int);

  // Simulate a charcoal drawing. Accepts the sigma and optional radius
  void Charcoal(int, int);

  // Simulate an oil painting. Accepts optional radius
  void Paint(int);

  // Applies an effect similar to a sepia tone with threshold
  void Sepia(int);

  // Get the underlying MagickWand for the ImageWrap.  This object
  // is not a copy, but rather a reference to the actual MagickWand.
  MagickWand* GetWand(void);

  private:

  // Release the base MagickWand (as part of destruction)
  void ReleaseBaseWand();

  /*
   * Private variables
   */

  // The MagickWand used for internal operations
  MagickWand *baseWand;

  /*
   * Inline methods
   */

  // Get the current width of the ImageWrap
  size_t GetOriginalWidth() {
    return MagickGetImageWidth(this->baseWand);
  }

  // Get the current height of the ImageWrap
  size_t GetOriginalHeight() {
    return MagickGetImageHeight(this->baseWand);
  }

};

#endif
