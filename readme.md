# quake as a service

this is a version of [quakespasm](https://github.com/sezero/quakespasm.git) without IO and rendering which can be used to build a custom renderer for Quake.

it only compiles a static library to run the quake game mechanics in your own engine.
in particular i've removed all opengl/sdl parts of the code.
currently you'll need to implement

```c
// called each time a new map is (re)loaded
void QS_worldspawn();
// called when a texture should be loaded
void QS_texture_load(gltexture_t* glt, uint32_t* data)
// process input, pretty much a copy from in_sdl.c:
void IN_Move(usercmd_t* cmd)
// called in place of the quakespasm renderer
void R_RenderScene()
```

If the meson option `snd_extern` is false you also have to implement:
```c++
qboolean SNDDMA_Init (dma_t *dma);
int SNDDMA_GetDMAPos (void);
void SNDDMA_Shutdown (void);
void SNDDMA_LockBuffer (void);
void SNDDMA_Submit (void);
void SNDDMA_BlockSound (void);
void SNDDMA_UnblockSound (void);
```
Note, that this is not necessary to have sound if you hook into quakes internals, but it makes things easier.

If the meson option `draw_character_extern` is false you also have to implement:
```c++
void Draw_CharacterQuad (int x, int y, char num);
```
