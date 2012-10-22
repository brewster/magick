# Magick

ImageMagick bindings for Node.js.

## Installation

``` bash
$ npm install magick
```

## Usage

``` javascript
var fs = require('fs');
var magick = require('magick');

// Load the file data into Magick
var data = fs.readFileSync('./image.jpg');
var file = new magick.File(data);

// Perform operations
file.setFormat('PNG');
file.opacity(0.5);
file.resize(200, 250);
file.blur(5);
file.paint(5);

// Get file and release memory
var buffer = file.getBuffer();
file.release();

// Write to new file
fs.writeFileSync('./image-altered.png', buffer);
```

## License

Magick is distributed under the MIT License. See
[LICENSE](https://github.com/brewster/magick/blob/master/LICENSE) for more
details.
