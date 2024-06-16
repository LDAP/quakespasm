project(
    'quakespasm',
    ['c'],
    version : '0.0.1',
    default_options : [
        'warning_level=3',
        'b_ndebug=if-release',
    ]
)

project_dir  = meson.current_source_dir()
cc = meson.get_compiler('c')
is_windows = build_machine.system() == 'windows'
deps = []
lib_search_paths = []

if is_windows
    if build_machine.cpu_family() == 'x86_64'
        codec_path = join_paths(project_dir, 'Windows/codecs/x64')
        sdl_path = join_paths(project_dir, 'Windows\SDL\lib64')
    elif build_machine.cpu_family() == 'x86'
        codec_path = join_paths(project_dir, 'Windows/codecs/x86')
        sdl_path = join_paths(project_dir, 'Windows\SDL\lib')
    else
        error('system not supported')
    endif

    lib_search_paths += codec_path
    lib_search_paths += sdl_path

    # Maybe there is an cleaner way to get those installed...
    install_data(codec_path / 'libmad-0.dll', install_dir : get_option('bindir'))
    install_data(sdl_path / 'SDL.dll', install_dir : get_option('bindir'))

    add_project_arguments('-D_USE_WINSOCK2', language: 'c')
	deps += cc.find_library('ws2_32', required: true)
    deps += cc.find_library('SDL', required : true, dirs : lib_search_paths)
    deps += cc.find_library('winmm', required: true)
endif

deps += cc.find_library('m', required : not is_windows)

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
  deps += cc.find_library('vorbis', required : true, dirs : lib_search_paths)
  deps += cc.find_library('ogg', required : true, dirs : lib_search_paths)
  deps += cc.find_library('vorbisfile', required : true, dirs : lib_search_paths)
endif
if get_option('use_codec_mp3')
  add_project_arguments('-DUSE_CODEC_MP3', language: 'c')
  deps += cc.find_library('mad', required : true, dirs : lib_search_paths)
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

if is_windows
    inc_dirs += include_directories('Windows\SDL2\include',
                                    'Windows\codecs\include',
                                    'Windows\misc\include')
endif


if get_option('draw_extern')
    add_project_arguments('-DDRAW_EXTERN', language: 'c')
endif

subdir('Quake')

quake_dep = declare_dependency(
    link_with: [quake_lib],
    include_directories : include_directories('./Quake'),
)
