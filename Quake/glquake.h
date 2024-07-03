/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2007-2008 Kristian Duske
Copyright (C) 2010-2014 QuakeSpasm developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef GLQUAKE_H
#define GLQUAKE_H

void GL_BeginRendering (int *x, int *y, int *width, int *height);
void GL_EndRendering (void);
void GL_Set2D (void);

extern	int glx, gly, glwidth, glheight;

#define	GL_UNUSED_TEXTURE	(~(GLuint)0)

// r_local.h -- private refresh defs

#define ALIAS_BASE_SIZE_RATIO		(1.0 / 11.0)
					// normalizing factor so player model works out to about
					//  1 pixel per triangle
#define	MAX_LBM_HEIGHT		480

#define TILE_SIZE		128		// size of textures generated by R_GenTiledSurf

#define SKYSHIFT		7
#define	SKYSIZE			(1 << SKYSHIFT)
#define SKYMASK			(SKYSIZE - 1)

#define BACKFACE_EPSILON	0.01


void R_TimeRefresh_f (void);
void R_ReadPointFile_f (void);
texture_t *R_TextureAnimation (texture_t *base, int frame);

typedef struct surfcache_s
{
	struct surfcache_s	*next;
	struct surfcache_s 	**owner;		// NULL is an empty chunk of memory
	int			lightadj[MAXLIGHTMAPS]; // checked for strobe flush
	int			dlight;
	int			size;		// including header
	unsigned		width;
	unsigned		height;		// DEBUG only needed for debug
	float			mipscale;
	struct texture_s	*texture;	// checked for animating textures
	byte			data[4];	// width*height elements
} surfcache_t;


typedef struct
{
	pixel_t		*surfdat;	// destination for generated surface
	int		rowbytes;	// destination logical width in bytes
	msurface_t	*surf;		// description for surface to generate
	fixed8_t	lightadj[MAXLIGHTMAPS];
							// adjust for lightmap levels for dynamic lighting
	texture_t	*texture;	// corrected for animating textures
	int		surfmip;	// mipmapped ratio of surface texels / world pixels
	int		surfwidth;	// in mipmapped texels
	int		surfheight;	// in mipmapped texels
} drawsurf_t;


typedef enum {
	pt_static, pt_grav, pt_slowgrav, pt_fire, pt_explode, pt_explode2, pt_blob, pt_blob2
} ptype_t;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct particle_s
{
// driver-usable fields
	vec3_t		org;
	vec3_t  	mv_prev_origin; // LDAP for motion vectors, set from rendering engine
	float		color;
// drivers never touch the following fields
	struct particle_s	*next;
	vec3_t		vel;
	float		ramp;
	float		die;
	ptype_t		type;
} particle_t;


//====================================================

extern	vec3_t		modelorg, r_entorigin;
extern	entity_t	*currententity;
extern	int		r_visframecount;	// ??? what difs?
extern	int		r_framecount;
extern	mplane_t	frustum[4];

extern	texture_t	*r_notexture_mip, *r_notexture_mip2;

//
// view origin
//
extern	vec3_t	vup;
extern	vec3_t	vpn;
extern	vec3_t	vright;
extern	vec3_t	r_origin;

//
// screen size info
//
extern	refdef_t	r_refdef;
extern	mleaf_t		*r_viewleaf, *r_oldviewleaf;
extern	int		d_lightstylevalue[256];	// 8.8 fraction of base light value

extern	cvar_t	r_norefresh;
extern	cvar_t	r_drawentities;
extern	cvar_t	r_drawworld;
extern	cvar_t	r_drawviewmodel;
extern	cvar_t	r_speeds;
extern	cvar_t	r_pos;
extern	cvar_t	r_waterwarp;
extern	cvar_t	r_fullbright;
extern	cvar_t	r_lightmap;
extern	cvar_t	r_lightmapwide;
extern	cvar_t	r_shadows;
extern	cvar_t	r_wateralpha;
extern	cvar_t	r_lavaalpha;
extern	cvar_t	r_telealpha;
extern	cvar_t	r_slimealpha;
extern	cvar_t	r_litwater;
extern	cvar_t	r_dynamic;
extern	cvar_t	r_novis;
extern	cvar_t	r_scale;

extern	cvar_t	gl_clear;
extern	cvar_t	gl_cull;
extern	cvar_t	gl_smoothmodels;
extern	cvar_t	gl_affinemodels;
extern	cvar_t	gl_polyblend;
extern	cvar_t	gl_flashblend;
extern	cvar_t	gl_nocolors;
extern	cvar_t	gl_finish;

extern	cvar_t	gl_playermip;

extern	cvar_t	gl_subdivide_size;
extern	float	load_subdivide_size; //johnfitz -- remember what subdivide_size value was when this map was loaded

extern int		gl_stencilbits;

// Multitexture
extern	qboolean	mtexenabled;
extern	qboolean	gl_mtexable;
#if 0
extern PFNGLMULTITEXCOORD2FARBPROC  GL_MTexCoord2fFunc;
extern PFNGLACTIVETEXTUREARBPROC    GL_SelectTextureFunc;
extern PFNGLCLIENTACTIVETEXTUREARBPROC	GL_ClientActiveTextureFunc;
extern GLint		gl_max_texture_units; //ericw

//johnfitz -- anisotropic filtering
#define	GL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE
#define	GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT	0x84FF
extern	float		gl_max_anisotropy;
extern	qboolean	gl_anisotropy_able;

//ericw -- VBO
extern PFNGLBINDBUFFERARBPROC  GL_BindBufferFunc;
extern PFNGLBUFFERDATAARBPROC  GL_BufferDataFunc;
extern PFNGLBUFFERSUBDATAARBPROC  GL_BufferSubDataFunc;
extern PFNGLDELETEBUFFERSARBPROC  GL_DeleteBuffersFunc;
extern PFNGLGENBUFFERSARBPROC  GL_GenBuffersFunc;
extern	qboolean	gl_vbo_able;
//ericw

//ericw -- GLSL

// SDL 1.2 has a bug where it doesn't provide these typedefs on OS X!
typedef GLuint (APIENTRYP QS_PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRYP QS_PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRYP QS_PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP QS_PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRYP QS_PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (APIENTRYP QS_PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRYP QS_PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP QS_PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRYP QS_PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef GLuint (APIENTRYP QS_PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRYP QS_PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP QS_PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP QS_PFNGLBINDATTRIBLOCATIONFUNC) (GLuint program, GLuint index, const GLchar *name);
typedef void (APIENTRYP QS_PFNGLUSEPROGRAMPROC) (GLuint program);
typedef GLint (APIENTRYP QS_PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP QS_PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void (APIENTRYP QS_PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP QS_PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef GLint (APIENTRYP QS_PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP QS_PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRYP QS_PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (APIENTRYP QS_PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP QS_PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP QS_PFNGENERATEMIPMAP) (GLenum type);

extern QS_PFNGLCREATESHADERPROC GL_CreateShaderFunc;
extern QS_PFNGLDELETESHADERPROC GL_DeleteShaderFunc;
extern QS_PFNGLDELETEPROGRAMPROC GL_DeleteProgramFunc;
extern QS_PFNGLSHADERSOURCEPROC GL_ShaderSourceFunc;
extern QS_PFNGLCOMPILESHADERPROC GL_CompileShaderFunc;
extern QS_PFNGLGETSHADERIVPROC GL_GetShaderivFunc;
extern QS_PFNGLGETSHADERINFOLOGPROC GL_GetShaderInfoLogFunc;
extern QS_PFNGLGETPROGRAMIVPROC GL_GetProgramivFunc;
extern QS_PFNGLGETPROGRAMINFOLOGPROC GL_GetProgramInfoLogFunc;
extern QS_PFNGLCREATEPROGRAMPROC GL_CreateProgramFunc;
extern QS_PFNGLATTACHSHADERPROC GL_AttachShaderFunc;
extern QS_PFNGLLINKPROGRAMPROC GL_LinkProgramFunc;
extern QS_PFNGLBINDATTRIBLOCATIONFUNC GL_BindAttribLocationFunc;
extern QS_PFNGLUSEPROGRAMPROC GL_UseProgramFunc;
extern QS_PFNGLGETATTRIBLOCATIONPROC GL_GetAttribLocationFunc;
extern QS_PFNGLVERTEXATTRIBPOINTERPROC GL_VertexAttribPointerFunc;
extern QS_PFNGLENABLEVERTEXATTRIBARRAYPROC GL_EnableVertexAttribArrayFunc;
extern QS_PFNGLDISABLEVERTEXATTRIBARRAYPROC GL_DisableVertexAttribArrayFunc;
extern QS_PFNGLGETUNIFORMLOCATIONPROC GL_GetUniformLocationFunc;
extern QS_PFNGLUNIFORM1IPROC GL_Uniform1iFunc;
extern QS_PFNGLUNIFORM1FPROC GL_Uniform1fFunc;
extern QS_PFNGLUNIFORM3FPROC GL_Uniform3fFunc;
extern QS_PFNGLUNIFORM4FPROC GL_Uniform4fFunc;
#endif
extern	qboolean	gl_glsl_able;
extern	qboolean	gl_glsl_gamma_able;
extern	qboolean	gl_glsl_alias_able;
// ericw --

//mipmapped warp textures
extern int GL_GenerateMipmap;

//ericw -- NPOT texture support
extern	qboolean	gl_texture_NPOT;

#if 0
//johnfitz -- polygon offset
#define OFFSET_BMODEL 1
#define OFFSET_NONE 0
#define OFFSET_DECAL -1
#define OFFSET_FOG -2
#define OFFSET_SHOWTRIS -3
void GL_PolygonOffset (int);
#endif

//GL_EXT_packed_pixels
#ifndef GL_UNSIGNED_INT_10_10_10_2
#define GL_UNSIGNED_INT_10_10_10_2 0x8036
#endif
extern qboolean gl_packed_pixels;

#if 0
//johnfitz -- GL_EXT_texture_env_combine
//the values for GL_ARB_ are identical
#define GL_COMBINE_EXT		0x8570
#define GL_COMBINE_RGB_EXT	0x8571
#define GL_COMBINE_ALPHA_EXT	0x8572
#define GL_RGB_SCALE_EXT	0x8573
#define GL_CONSTANT_EXT		0x8576
#define GL_PRIMARY_COLOR_EXT	0x8577
#define GL_PREVIOUS_EXT		0x8578
#define GL_SOURCE0_RGB_EXT	0x8580
#define GL_SOURCE1_RGB_EXT	0x8581
#define GL_SOURCE0_ALPHA_EXT	0x8588
#define GL_SOURCE1_ALPHA_EXT	0x8589
extern qboolean gl_texture_env_combine;
extern qboolean gl_texture_env_add; // for GL_EXT_texture_env_add
#endif

//johnfitz -- rendering statistics
extern int rs_brushpolys, rs_aliaspolys, rs_skypolys;
extern int rs_dynamiclightmaps, rs_brushpasses, rs_aliaspasses, rs_skypasses;

//johnfitz -- track developer statistics that vary every frame
extern cvar_t devstats;
typedef struct {
	int		packetsize;
	int		edicts;
	int		visedicts;
	int		efrags;
	int		tempents;
	int		beams;
	int		dlights;
} devstats_t;
extern devstats_t dev_stats, dev_peakstats;

//ohnfitz -- reduce overflow warning spam
typedef struct {
	double	packetsize;
	double	efrags;
	double	beams;
	double	varstring;
} overflowtimes_t;
extern overflowtimes_t dev_overflows; //this stores the last time overflow messages were displayed, not the last time overflows occured
#define CONSOLE_RESPAM_TIME 3 // seconds between repeated warning messages

//johnfitz -- moved here from r_brush.c
extern int gl_lightmap_format, lightmap_bytes;

#define LMBLOCK_WIDTH	256	//FIXME: make dynamic. if we have a decent card there's no real reason not to use 4k or 16k (assuming there's no lightstyles/dynamics that need uploading...)
#define LMBLOCK_HEIGHT	256 //Alternatively, use texture arrays, which would avoid the need to switch textures as often.

typedef struct glRect_s {
	unsigned short l,t,w,h;
} glRect_t;
struct lightmap_s
{
	gltexture_t *texture;
	glpoly_t	*polys;
	qboolean	modified;
	glRect_t	rectchange;

	// the lightmap texture data needs to be kept in
	// main memory so texsubimage can update properly
	byte		*data;//[4*LMBLOCK_WIDTH*LMBLOCK_HEIGHT];
};
extern struct lightmap_s *lightmaps;
extern int lightmap_count;	//allocated lightmaps

extern int gl_warpimagesize; //johnfitz -- for water warp

extern qboolean r_drawflat_cheatsafe, r_fullbright_cheatsafe, r_lightmap_cheatsafe, r_drawworld_cheatsafe; //johnfitz

typedef struct glsl_attrib_binding_s {
	const char *name;
	uint32_t attrib;
} glsl_attrib_binding_t;

extern float	map_wateralpha, map_lavaalpha, map_telealpha, map_slimealpha; //ericw

#define NUMVERTEXNORMALS	162
extern const float	r_avertexnormals[NUMVERTEXNORMALS][3];

extern char	skybox_name[1024];
extern gltexture_t	*skybox_textures[6];
extern gltexture_t	*solidskytexture, *alphaskytexture;

//johnfitz -- fog functions called from outside gl_fog.c
void Fog_ParseServerMessage (void);
float *Fog_GetColor (void);
float Fog_GetDensity (void);
void Fog_EnableGFog (void);
void Fog_DisableGFog (void);
void Fog_StartAdditive (void);
void Fog_StopAdditive (void);
void Fog_SetupFrame (void);
void Fog_NewMap (void);
void Fog_Init (void);
void Fog_SetupState (void);

void R_NewGame (void);

void R_AnimateLight (void);
void R_MarkSurfaces (void);
qboolean R_CullBox (vec3_t emins, vec3_t emaxs);
void R_StoreEfrags (efrag_t **ppefrag);
qboolean R_CullModelForEntity (entity_t *e);
void R_RotateForEntity (vec3_t origin, vec3_t angles, unsigned char scale);
void R_MarkLights (dlight_t *light, int num, mnode_t *node);
void R_SetupView();

void R_InitParticles (void);
void R_DrawParticles (void);
void CL_RunParticles (void);
void R_ClearParticles (void);

void R_TranslatePlayerSkin (int playernum);
void R_TranslateNewPlayerSkin (int playernum); //johnfitz -- this handles cases when the actual texture changes
void R_UpdateWarpTextures (void);

void R_DrawWorld (void);
void R_DrawAliasModel (entity_t *e);
void R_DrawBrushModel (entity_t *e);
mspriteframe_t *R_GetSpriteFrame (entity_t *currentent);
void R_DrawSpriteModel (entity_t *e);

void R_DrawTextureChains_Water (qmodel_t *model, entity_t *ent, texchain_t chain);

void R_RenderDlights (void);
void GL_BuildLightmaps (void);
// void GL_DeleteBModelVertexBuffer (void);
// void GL_BuildBModelVertexBuffer (void);
// void GLMesh_LoadVertexBuffers (void);
// void GLMesh_DeleteVertexBuffers (void);
void R_RebuildAllLightmaps (void);

int R_LightPoint (vec3_t p);

void GL_SubdivideSurface (msurface_t *fa);
void R_BuildLightMap (msurface_t *surf, byte *dest, int stride);
void R_RenderDynamicLightmaps (msurface_t *fa);
void R_UploadLightmaps (void);

void R_SetupAliasFrame (entity_t *e, aliashdr_t *paliashdr, int frame, lerpdata_t *lerpdata);
void R_SetupEntityTransform (entity_t *e, lerpdata_t *lerpdata);

void R_DrawWorld_ShowTris (void);
void R_DrawBrushModel_ShowTris (entity_t *e);
void R_DrawAliasModel_ShowTris (entity_t *e);
void R_DrawParticles_ShowTris (void);

// int32_t GL_GetUniformLocation (GLuint *programPtr, const char *name);
// uint32_t GL_CreateProgram (const GLchar *vertSource, const GLchar *fragSource, int numbindings, const glsl_attrib_binding_t *bindings);
void R_DeleteShaders (void);

// void GLWorld_CreateShaders (void);
// void GLAlias_CreateShaders (void);
// void GL_DrawAliasShadow (entity_t *e);
void DrawGLTriangleFan (glpoly_t *p);
void DrawGLPoly (glpoly_t *p);
void DrawWaterPoly (glpoly_t *p);
void GL_MakeAliasModelDisplayLists (qmodel_t *m, aliashdr_t *hdr);

void Sky_Init (void);
void Sky_ClearAll (void);
void Sky_DrawSky (void);
void Sky_NewMap (void);
void Sky_LoadTexture (qmodel_t *m, texture_t *mt);
void Sky_LoadTextureQ64 (qmodel_t *m, texture_t *mt);
void Sky_LoadSkyBox (const char *name);

void TexMgr_RecalcWarpImageSize (void);

void R_ClearTextureChains (qmodel_t *mod, texchain_t chain);
void R_ChainSurface (msurface_t *surf, texchain_t chain);
void R_DrawTextureChains (qmodel_t *model, entity_t *ent, texchain_t chain);
void R_DrawWorld_Water (void);

// void GL_BindBuffer (GLenum target, GLuint buffer);
// void GL_ClearBufferBindings (void);

// void GLSLGamma_DeleteTexture (void);
// void GLSLGamma_GammaCorrect (void);

void R_ScaleView_DeleteTexture (void);

// float GL_WaterAlphaForSurface (msurface_t *fa);

#endif	/* GLQUAKE_H */
