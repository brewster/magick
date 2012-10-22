{
  'targets': [
    {
      'conditions': [

        [
          'OS=="win"',
          {
            # no windows support
          },
          {
            'libraries': [
              '<!@(pkg-config --static --libs MagickWand)',
            ]
          }
        ],

        [
          'OS=="mac"',
          {
            'xcode_settings': {
              'OTHER_CFLAGS': [
                '<!@(pkg-config --static --cflags MagickWand)',
                '-Wall'
              ],
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
              'GCC_ENABLE_CPP_RTTI': 'YES'
            }
          },
          {
            'cflags': [
              '<!@(pkg-config --static --cflags MagickWand)',
              '-Wall'
            ],
            'cflags_cc!': [
              '-fno-rtti',
              '-fno-exceptions'
            ]
          }
        ]

      ],
      'target_name': 'magick',
      'sources': [
        'src/image_wrap.cc',
        'src/file.cc',
        'src/magick.cc'
      ]
    }
  ]
}
