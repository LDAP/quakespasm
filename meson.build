project(
    'quakespasm',
    ['c'],
    version : '0.0.1',
    default_options : [
        'warning_level=3',
        'b_ndebug=if-release',
    ]
)

cc = meson.get_compiler('c')
libm = cc.find_library('m', required : true)

deps = [libm]

if get_option('enable_userdirs')
  add_project_arguments('-DDO_USERDIRS', language: 'c')
endif

if get_option('use_codec_wave')
  add_project_arguments('-DUSE_CODEC_WAVE', language: 'c')
endif
if get_option('use_codec_flac')
  add_project_arguments('-DUSE_CODEC_FALC', language: 'c')
endif
if get_option('use_codec_opus')
  add_project_arguments('-DUSE_CODEC_OPUS', language: 'c')
  # CFLAGS+= $(shell $(PKG_CONFIG) --cflags opusfile)
  #CODECLIBS+= $(shell $(PKG_CONFIG) --libs   opusfile)
endif
if get_option('use_codec_vorbis')
  add_project_arguments('-DUSE_CODEC_VORBIS', language: 'c')
  deps += cc.find_library('vorbis', required : true)
  deps += cc.find_library('ogg', required : true)
  deps += cc.find_library('vorbisfile', required : true)
endif
if get_option('use_codec_mp3')
  add_project_arguments('-DUSE_CODEC_MP3', language: 'c')
  deps += cc.find_library('mad', required : true)
endif
if get_option('use_codec_mikmod')
  add_project_arguments('-DUSE_CODEC_MIKMOD', language: 'c')
  # CODECLIBS+= -lmikmod
endif
if get_option('use_codec_xmp')
  add_project_arguments('-DUSE_CODEC_XMP', language: 'c')
  # CODECLIBS+= -lxmp
endif
if get_option('use_codec_umx')
  add_project_arguments('-DUSE_CODEC_UMX', language: 'c')
endif

inc_dirs = [
    include_directories('./Quake'),
]

subdir('Quake')

quake_dep = declare_dependency(
    link_with: [quake_lib],
    dependencies: deps,
    include_directories : inc_dirs
)
