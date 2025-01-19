#include "ui/bagl_extension.h"

#ifdef HAVE_UX_FLOW
#define HUD_HEIGHT (RENDER_HEIGHT + (BAGL_HEIGHT - RENDER_HEIGHT) / 2 +3)

// clang-format off
const bagl_element_t ux_layout_ppb_elements[] = {
#if (BAGL_WIDTH==128 && BAGL_HEIGHT==64)
  // erase
  {{BAGL_RECTANGLE                      , 0x00,   0,   0, 128,  64, 0, 0, BAGL_FILL, 0x000000, 0xFFFFFF, 0, 0}, NULL},

   // left/right icons
  {{BAGL_ICON                           , 0x01,   2,  32,   4,   7, 0, 0, 0        , 0xFFFFFF, 0x000000, 0, 0  }, (const char*)&C_icon_left },
  {{BAGL_ICON                           , 0x02, 122,  32,   4,   7, 0, 0, 0        , 0xFFFFFF, 0x000000, 0, 0  }, (const char*)&C_icon_right },

  {{BAGL_ICON                           , 0x10,  28,  9,  64,  64, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_ALIGNMENT_CENTER, 0  }, NULL },
  {{BAGL_ICON                           , 0x11,  64,  9,  64,  64, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_ALIGNMENT_CENTER, 0  }, NULL },
  {{BAGL_LABELINE                       , 0x12,  47, 55, 30,  10, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_OPEN_SANS_EXTRABOLD_11px|BAGL_FONT_ALIGNMENT_CENTER, 0  }, .text=NULL},

#else
  #error "BAGL_WIDTH/BAGL_HEIGHT not defined"
#endif
};
// clang-format on

const bagl_element_t *ux_layout_ppb_prepro(const bagl_element_t *element) {
    // don't display if null
    const ux_layout_ppb_params_t *params =
        (const ux_layout_ppb_params_t *) ux_stack_get_current_step_params();

    // ocpy element before any mod
    memmove(&G_ux.tmp_element, element, sizeof(bagl_element_t));

    // for dashboard, setup the current application's name
    switch (element->component.userid) {
        case 0x01:
            if (ux_flow_is_first()) {
                return NULL;
            }
            break;

        case 0x02:
            if (ux_flow_is_last()) {
                return NULL;
            }
            break;

        case 0x10:
            G_ux.tmp_element.text = (const char *) params->icon1;
            break;

        case 0x11:
            G_ux.tmp_element.text = (const char *) params->icon2;
            break;
        case 0x12:
            G_ux.tmp_element.text = params->line1;
            break;
    }
    return &G_ux.tmp_element;
}

void ux_layout_ppb_init(unsigned int stack_slot) {
    ux_stack_init(stack_slot);
    G_ux.stack[stack_slot].element_arrays[0].element_array = ux_layout_ppb_elements;
    G_ux.stack[stack_slot].element_arrays[0].element_array_count = ARRAYLEN(ux_layout_ppb_elements);
    G_ux.stack[stack_slot].element_arrays_count = 1;
    G_ux.stack[stack_slot].screen_before_element_display_callback = ux_layout_ppb_prepro;
    G_ux.stack[stack_slot].button_push_callback = ux_flow_button_callback;
    ux_stack_display(stack_slot);
}
#endif  // HAVE_UX_FLOW

#ifdef HAVE_UX_FLOW

// clang-format off
const bagl_element_t ux_layout_doom_elements[] = {
#if (BAGL_WIDTH==128 && BAGL_HEIGHT==64)
  {{BAGL_RECTANGLE                      , 0x00,   0,   0, 128,  64, 0, 0, BAGL_FILL, 0x000000, 0xFFFFFF, 0, 0}, NULL},

  {{BAGL_ICON                           , 0x11,  0,                    0,   DOOM_BITMAP_WIDTH,  RENDER_HEIGHT, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_ALIGNMENT_CENTER, 0  }, NULL },
  {{BAGL_ICON                           , 0x12,  DOOM_BITMAP_WIDTH,    0,   DOOM_BITMAP_WIDTH,  RENDER_HEIGHT, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_ALIGNMENT_CENTER, 0  }, NULL },
  {{BAGL_ICON                           , 0x13,  DOOM_BITMAP_WIDTH*2,  0,   DOOM_BITMAP_WIDTH,  RENDER_HEIGHT, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_ALIGNMENT_CENTER, 0  }, NULL },
  {{BAGL_ICON                           , 0x14,  DOOM_BITMAP_WIDTH*3,  0,   DOOM_BITMAP_WIDTH,  RENDER_HEIGHT, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_ALIGNMENT_CENTER, 0  }, NULL },
// HUD
  {{BAGL_LABELINE                       , 0x15,  2, HUD_HEIGHT, 35,  HUD_HEIGHT/2, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_OPEN_SANS_EXTRABOLD_11px, 0  }, .text=NULL},
  {{BAGL_LABELINE                       , 0x16,  40, HUD_HEIGHT, 30,  HUD_HEIGHT/2, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_OPEN_SANS_EXTRABOLD_11px, 0  }, .text=NULL},
  {{BAGL_LABELINE                       , 0x17,  90, HUD_HEIGHT, 30,  HUD_HEIGHT/2, 0, 0, 0        , 0xFFFFFF, 0x000000, BAGL_FONT_OPEN_SANS_EXTRABOLD_11px, 0  }, .text=NULL},
#else
  #error "BAGL_WIDTH/BAGL_HEIGHT not defined"
#endif
};
// clang-format on

const bagl_element_t *ux_layout_doom_prepro(const bagl_element_t *element) {
    // don't display if null
    const ux_layout_doom_params_t *params =
        (const ux_layout_doom_params_t *) ux_stack_get_current_step_params();

    // copy element before any mod
    memmove(&G_ux.tmp_element, element, sizeof(bagl_element_t));

    // for dashboard, setup the current application's name
    switch (element->component.userid) {
        case 0x11:
            G_ux.tmp_element.text = (const char *) params->icon1;
            break;
        case 0x12:
            G_ux.tmp_element.text = (const char *) params->icon2;
            break;
        case 0x13:
            G_ux.tmp_element.text = (const char *) params->icon3;
            break;
        case 0x14:
            G_ux.tmp_element.text = (const char *) params->icon4;
            break;
        case 0x15: {
            G_ux.tmp_element.text = params->health;
            break;
        }
        case 0x16: {
            G_ux.tmp_element.text = params->keys;
            break;
        }
        case 0x17: {
            G_ux.tmp_element.text = params->entities;
            break;
        }
    }

    return &G_ux.tmp_element;
}

void ux_layout_doom_init(unsigned int stack_slot) {
    ux_stack_init(stack_slot);
    G_ux.stack[stack_slot].element_arrays[0].element_array = ux_layout_doom_elements;
    G_ux.stack[stack_slot].element_arrays[0].element_array_count =
        ARRAYLEN(ux_layout_doom_elements);
    G_ux.stack[stack_slot].element_arrays_count = 1;
    G_ux.stack[stack_slot].screen_before_element_display_callback = ux_layout_doom_prepro;
    G_ux.stack[stack_slot].button_push_callback = ux_flow_button_callback;
    ux_stack_display(stack_slot);
}
#endif  // HAVE_UX_FLOW