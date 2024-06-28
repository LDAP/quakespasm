// short circuited minimum linkage for some globals
#include "quakedef.h"
#include "cfgfile.h"
#include "vid.h"

// from gl_vidsdl.c
viddef_t	vid;				// global video state
modestate_t	modestate = MS_UNINIT;
qboolean	scr_skipupdate;

qboolean gl_mtexable = false;
qboolean gl_packed_pixels = false;
qboolean gl_texture_env_combine = false; //johnfitz
qboolean gl_texture_env_add = false; //johnfitz
qboolean gl_swap_control = false; //johnfitz
qboolean gl_anisotropy_able = false; //johnfitz
float gl_max_anisotropy; //johnfitz
qboolean gl_texture_NPOT = false; //ericw
qboolean gl_vbo_able = false; //ericw
qboolean gl_glsl_able = false; //ericw
int32_t gl_max_texture_units = 0; //ericw
qboolean gl_glsl_gamma_able = false; //ericw
qboolean gl_glsl_alias_able = false; //ericw
int gl_stencilbits;
int GL_GenerateMipmap = 0;

//johnfitz -- new cvars
static cvar_t	vid_fullscreen = {"vid_fullscreen", "0", CVAR_ARCHIVE};	// QuakeSpasm, was "1"
static cvar_t	vid_width = {"vid_width", "1920", CVAR_ARCHIVE};		// QuakeSpasm, was 640
static cvar_t	vid_height = {"vid_height", "1080", CVAR_ARCHIVE};	// QuakeSpasm, was 480
static cvar_t	vid_bpp = {"vid_bpp", "16", CVAR_ARCHIVE};
static cvar_t	vid_refreshrate = {"vid_refreshrate", "60", CVAR_ARCHIVE};
static cvar_t	vid_vsync = {"vid_vsync", "0", CVAR_ARCHIVE};
static cvar_t	vid_fsaa = {"vid_fsaa", "0", CVAR_ARCHIVE}; // QuakeSpasm
static cvar_t	vid_desktopfullscreen = {"vid_desktopfullscreen", "0", CVAR_ARCHIVE}; // QuakeSpasm
static cvar_t	vid_borderless = {"vid_borderless", "0", CVAR_ARCHIVE}; // QuakeSpasm
//johnfitz
cvar_t		vid_gamma = {"gamma", "1", CVAR_ARCHIVE}; //johnfitz -- moved here from view.c
cvar_t		vid_contrast = {"contrast", "1", CVAR_ARCHIVE}; //QuakeSpasm, MarkV

void VID_Changed_f (cvar_t *var);

static void _VID_Changed_f (cvar_t *var) {
	vid.width  = (int)vid_width.value;
  	vid.height = (int)vid_height.value;
  	vid.conwidth = vid.width & 0xFFFFFFF8;
	vid.conheight = vid.conwidth * vid.height / vid.width;
	vid.recalc_refdef = 1;

	if (var)
  		VID_Changed_f(var);
}

void VID_Init (void)
{
	const char	*read_vars[] = {
           "vid_fullscreen",
					 "vid_width",
					 "vid_height",
					 "vid_refreshrate",
					 "vid_bpp",
					 "vid_vsync",
					 "vid_fsaa",
					 "vid_desktopfullscreen",
					 "vid_borderless"};
#define num_readvars	( sizeof(read_vars)/sizeof(read_vars[0]) )

	Cvar_RegisterVariable (&vid_fullscreen); //johnfitz
	Cvar_RegisterVariable (&vid_width); //johnfitz
	Cvar_RegisterVariable (&vid_height); //johnfitz
	Cvar_RegisterVariable (&vid_refreshrate); //johnfitz
	Cvar_RegisterVariable (&vid_bpp); //johnfitz
	Cvar_RegisterVariable (&vid_vsync); //johnfitz
	Cvar_RegisterVariable (&vid_fsaa); //QuakeSpasm
	Cvar_RegisterVariable (&vid_desktopfullscreen); //QuakeSpasm
	Cvar_RegisterVariable (&vid_borderless); //QuakeSpasm
	Cvar_SetCallback (&vid_fullscreen, _VID_Changed_f);
	Cvar_SetCallback (&vid_width, _VID_Changed_f);
	Cvar_SetCallback (&vid_height, _VID_Changed_f);
	Cvar_SetCallback (&vid_refreshrate, _VID_Changed_f);
	Cvar_SetCallback (&vid_bpp, _VID_Changed_f);
	Cvar_SetCallback (&vid_vsync, _VID_Changed_f);
	//Cvar_SetCallback (&vid_fsaa, VID_FSAA_f);
	Cvar_SetCallback (&vid_desktopfullscreen, _VID_Changed_f);
	Cvar_SetCallback (&vid_borderless, _VID_Changed_f);
	
	// Cmd_AddCommand ("vid_unlock", VID_Unlock); //johnfitz
	// Cmd_AddCommand ("vid_restart", VID_Restart); //johnfitz
	// Cmd_AddCommand ("vid_test", VID_Test); //johnfitz
	// Cmd_AddCommand ("vid_describecurrentmode", VID_DescribeCurrentMode_f);
	// Cmd_AddCommand ("vid_describemodes", VID_DescribeModes_f);

	Cvar_SetValueQuick (&vid_bpp, (float)8);

	if (CFG_OpenConfig("config.cfg") == 0)
	{
		CFG_ReadCvars(read_vars, num_readvars);
		CFG_CloseConfig();
	}
	CFG_ReadCvarOverrides(read_vars, num_readvars);

	vid.numpages = 2;
	vid.maxwarpwidth  = 320;
	vid.maxwarpheight = 200;
	vid.colormap = host_colormap;
	vid.fullbright = 256 - LittleLong (*((int *)vid.colormap + 2048));
  	
  	int p;
  	p = COM_CheckParm("-width");
	if (p && p < com_argc-1)
	{
		vid.width = Q_atoi(com_argv[p+1]);

		if(!COM_CheckParm("-height"))
			vid.height = vid.width * 3 / 4;
	}

	p = COM_CheckParm("-height");
	if (p && p < com_argc-1)
	{
		vid.height = Q_atoi(com_argv[p+1]);

		if(!COM_CheckParm("-width"))
			vid.width = vid.height * 4 / 3;
	}

	_VID_Changed_f(NULL);
}
void VID_Shutdown (void) {}
void VID_Update (vrect_t *rects) {}
void VID_SyncCvars (void) {}
void VID_Toggle (void) {}
void *VID_GetWindow (void) { return 0; }
qboolean VID_HasMouseOrInputFocus (void) { return true; }
qboolean VID_IsMinimized (void) { return false; }
void	VID_Lock (void) {}
