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

if is_windows
    SYSOBJ_NET = files('net_win.c', 'net_wins.c', 'net_wipx.c')
else
    SYSOBJ_NET = files('net_bsd.c', 'net_udp.c')
endif

if is_windows
    SYSOBJ_SYS = files('pl_null.c', 'vid.c', 'in_null.c', 'cd_null.c', 'snd_null.c', 'sys_sdl_win.c')
else
    SYSOBJ_SYS = files('pl_null.c', 'vid.c', 'sys_sdl_unix.c', 'cd_null.c', 'in_null.c', 'snd_null.c')
endif

GLOBJS = files(
    'gl_refrag.c',
    'gl_rlight.c',
    'r_alias.c',
    'gl_fog.c',
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
    'gl_model.c',
    'r_brush.c',
    'gl_rmisc.c',
    'gl_rmain.c',
)

STR_OBJS = files(
    'strlcat.c',
    'strlcpy.c',
)
OBJS = files(
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
)

quake_lib = static_library(
    'quakespasm',
    [STR_OBJS, GLOBJS, COMOBJ_SND, SYSOBJ_NET, OBJS, SYSOBJ_SYS],
    dependencies: deps,
    include_directories: inc_dirs,
    install : true,
)
