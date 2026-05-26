// Linkage provided by the embedding C++ engine (like QS_texture_load,
// QS_worldspawn, R_RenderScene). Sticky state: set_canvas / set_scissor /
// set_color apply to all subsequent push_quad calls until changed.

#ifndef QS_UI_HOOK_H
#define QS_UI_HOOK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Ortho + viewport are in GL convention (y up from bottom).
void QS_ui_set_canvas(float ortho_l, float ortho_r, float ortho_b, float ortho_t,
                      int viewport_x, int viewport_y, int viewport_w, int viewport_h);

// w < 0 disables the scissor.
void QS_ui_set_scissor(int x, int y, int w, int h);

// RGBA8, byte order R,G,B,A, premultiplied.
void QS_ui_set_color(uint32_t rgba);

// texnum == 0: untextured, solid current color.
void QS_ui_push_quad(int texnum,
                     float x0, float y0, float x1, float y1,
                     float u0, float v0, float u1, float v1);

void QS_ui_frame_ready(void);

#ifdef __cplusplus
}
#endif

#endif
