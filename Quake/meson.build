MUSIC_OBJS = files(
    'bgmusic.c',
    'snd_codec.c',
    'snd_flac.c',
    'snd_wave.c',
    'snd_vorbis.c',
    'snd_opus.c',
    'snd_mp3.c',
    'snd_mp3tag.c',
    'snd_mikmod.c',
    'snd_xmp.c',
    'snd_umx.c'
)

COMOBJ_SND = files('snd_dma.c', 'snd_mix.c', 'snd_mem.c') + MUSIC_OBJS
SYSOBJ_NET = files('net_bsd.c', 'net_udp.c')
SYSOBJ_SYS = files('pl_linux.c', 'vid.c', 'sys_sdl_unix.c', 'cd_null.c', 'in_null.c', 'snd_null.c')

GLOBJS = files(
    'gl_refrag.c',
    'gl_rlight.c',
    'gl_rmain.c',
    'gl_fog.c',
    'gl_rmisc.c',
    'r_part.c',
    'r_world.c',
    'gl_screen.c',
    'gl_sky.c',
    'gl_warp.c',
    'gl_draw.c',
    'image.c',
    'gl_texmgr.c',
    'gl_mesh.c',
    'r_sprite.c',
    'r_alias.c',
    'r_brush.c',
    'gl_model.c',
)

OBJS = files(
    'strlcat.c',
    'strlcpy.c',
    'net_dgrm.c',
    'net_loop.c',
    'net_main.c',
    'chase.c',
    'cl_demo.c',
    'cl_input.c',
    'cl_main.c',
    'cl_parse.c',
    'cl_tent.c',
    'console.c',
    'keys.c',
    'menu.c',
    'sbar.c',
    'view.c',
    'wad.c',
    'cmd.c',
    'common.c',
    'miniz.c',
    'crc.c',
    'cvar.c',
    'cfgfile.c',
    'host.c',
    'host_cmd.c',
    'mathlib.c',
    'pr_cmds.c',
    'pr_edict.c',
    'pr_exec.c',
    'sv_main.c',
    'sv_move.c',
    'sv_phys.c',
    'sv_user.c',
    'world.c',
    'zone.c',
) + SYSOBJ_SYS + GLOBJS + COMOBJ_SND + SYSOBJ_NET

quake_lib = static_library(
    'quakespasm',
    [OBJS],
    dependencies: [
    ],
    include_directories: inc_dirs,
    install : true
)
