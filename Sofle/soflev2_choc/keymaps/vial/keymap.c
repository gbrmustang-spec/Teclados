/*
 * Sofle Choc - GbrTzT QMK/Vial V1
 * Based on original Sofle Choc keymap (c) 2023 Brian Low; GPL-2.0-or-later.
 * 58 switches + 2 encoder buttons in the electrical matrix.
 */
#include QMK_KEYBOARD_H
#include "split_util.h"
#include "via.h"
#include "eeconfig.h"
#include "transactions.h"
#include "timer.h"
#include "action_util.h"
#include <string.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_GRV  ,
        KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
        KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
        KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_MUTE , KC_MPLY , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT ,
        KC_LCTL , KC_LGUI , MO(1)   , KC_LALT , KC_ENT  , KC_SPC  , KC_RALT , MO(2)   , KC_RGUI , KC_RCTL 
    ),
    [1] = LAYOUT(
        KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_MUTE , KC_MPLY , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS 
    ),
    [2] = LAYOUT(
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS 
    ),
    [3] = LAYOUT(
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS 
    ),
    [4] = LAYOUT(
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS 
    ),
    [5] = LAYOUT(
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS 
    )
};

#ifdef ENCODER_MAP_ENABLE
// Encoder 0 (left): volume. Encoder 1 (right): previous / next track.
// Encoder click is handled as an ordinary matrix key (Mute / Play-Pause).
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif


/* ===== GbrTzT Sofle Choc V2: protocolo personalizado XCMKB =====
 * Mantem 0x45/0x46/0x48/0x52/0x53/0x55 do Corvo48 V12, sem trackpad.
 * 0x45: 10 mascaras de LEDs (uint64 little endian, 58 validos).
 * 0x46: 10 cores RGB globais, usadas como fallback em cada funcao.
 * 0x48: 9 cores RGB por pacote, individuais para cada LED da funcao.
 * Funcao 0 = Caps Lock; funcoes 1..9 = camadas 1..9.
 */
#ifdef VIAL_ENABLE
#include "via.h"
#include "eeconfig.h"
#include "transactions.h"
#include "timer.h"
#include "action_util.h"
#include <string.h>

#define SOFLE_CFG_MAGIC           0xD2
#define SOFLE_OLED_NAME_BYTES     8
#define SOFLE_OLED_LAYER_BYTES    6
#define SOFLE_OLED_LONG_SUBCMD    0x53
#define SOFLE_OLED_LONG_MARKER    0xA7
#define SOFLE_OLED_PRESET_SUBCMD   0x55
#define SOFLE_OLED_PRESET_MARKER   0xB8
#define SOFLE_OLED_PRESETS         6
#define SOFLE_OLED_DIRTY_PRESET    (1u << 11)
#define SOFLE_OLED_LAYERS         10
#define SOFLE_OLED_DIRTY_ALL      0x0FFFu
#define SOFLE_RGB_ROLES           10
#define SOFLE_RGB_LED_COUNT       58
#define SOFLE_RGB_DIRTY_ALL       0x03FFu
#define SOFLE_RGB_SYNC_LEDS       7
#define SOFLE_INDICATOR_MASK      0x45
#define SOFLE_INDICATOR_COLOR     0x46
#define SOFLE_INDICATOR_PER_LED   0x48
#define SOFLE_INDICATOR_MAGIC     0x49
#define SOFLE_OLED_SUBCMD         0x52

/* Sem alinhamento implicito; tamanho verificado por static_assert. */
typedef struct {
    uint8_t magic;
    char name[SOFLE_OLED_NAME_BYTES];
    char layers[SOFLE_OLED_LAYERS][SOFLE_OLED_LAYER_BYTES];
    uint8_t masks[SOFLE_RGB_ROLES][8];
    uint8_t role_rgb[SOFLE_RGB_ROLES][3];
    uint8_t led_rgb[SOFLE_RGB_ROLES][SOFLE_RGB_LED_COUNT][3];
    uint8_t oled_mode;   /* 0 = texto; 1 = imagem, aplicado nos dois OLEDs */
    uint8_t oled_preset; /* 0 Oni, 1 Cat, 2 Punisher, 3 Skull, 4 Alchemy1, 5 Alchemy2 */
} sofle_settings_t;

/* Mantem o RPC de OLED da V3, sem mudar a estrutura da mensagem. */
typedef struct {
    uint8_t item;
    char text[SOFLE_OLED_NAME_BYTES];
} sofle_oled_sync_t;

/* RPC <= 32 bytes do split; usa campos explicitos, sem padding. */
typedef struct {
    uint8_t role;
    uint8_t kind; /* 0 mask, 1 rgb padrao, 2 bloco cores/LED */
    uint8_t first;
    uint8_t data[SOFLE_RGB_SYNC_LEDS * 3];
} sofle_rgb_sync_t;


_Static_assert(sizeof(sofle_settings_t) == 1921, "Ajuste EECONFIG_USER_DATA_SIZE");
_Static_assert(sizeof(sofle_rgb_sync_t) == 24, "O RPC excedeu tamanho esperado");

static sofle_settings_t sofle_cfg;
static uint16_t sofle_oled_dirty = SOFLE_OLED_DIRTY_ALL;
static bool sofle_oled_needs_redraw = true;
static uint16_t sofle_rgb_dirty = SOFLE_RGB_DIRTY_ALL;
static uint8_t sofle_rgb_sync_phase = 0;
static uint8_t sofle_rgb_sync_first = 0;
static bool sofle_storage_dirty = false;
static uint32_t sofle_storage_time = 0;

static bool sofle_role_led(uint8_t role, uint8_t led) {
    return (sofle_cfg.masks[role][led / 8] & (1u << (led % 8))) != 0;
}

static void sofle_storage_mark_dirty(void) {
    sofle_storage_dirty = true;
    sofle_storage_time = timer_read32();
}

static void sofle_rgb_mark_dirty(uint8_t role) {
    if (role >= SOFLE_RGB_ROLES) return;
    sofle_rgb_dirty |= ((uint16_t)1u << role);
    sofle_rgb_sync_phase = 0;
    sofle_rgb_sync_first = 0;
    sofle_storage_mark_dirty();
}

static void sofle_defaults(void) {
    memset(&sofle_cfg, 0, sizeof(sofle_cfg));
    sofle_cfg.magic = SOFLE_CFG_MAGIC;
    memcpy(sofle_cfg.name, "GbrTzT", 6);
    static const char names[SOFLE_OLED_LAYERS][SOFLE_OLED_LAYER_BYTES] = {
        "BASE", "FN", "RGB", "L3", "L4", "L5", "L6", "L7", "L8", "L9"
    };
    memcpy(sofle_cfg.layers, names, sizeof(names));
    /* Cores padrao, sem LEDs atribuidos ate configurar na XCMKB. */
    static const uint8_t colors[SOFLE_RGB_ROLES][3] = {
        {128, 0, 0}, {128, 0, 128}, {255, 215, 0}, {0, 128, 128},
        {255, 128, 0}, {0, 0, 128}, {128, 0, 128}, {255, 192, 203},
        {0, 255, 127}, {255, 255, 255}
    };
    memcpy(sofle_cfg.role_rgb, colors, sizeof(colors));
    for (uint8_t role = 0; role < SOFLE_RGB_ROLES; ++role) {
        for (uint8_t led = 0; led < SOFLE_RGB_LED_COUNT; ++led) {
            memcpy(sofle_cfg.led_rgb[role][led], colors[role], 3);
        }
    }
}

void eeconfig_init_user_datablock(void) {
    sofle_defaults();
    eeconfig_update_user_datablock(&sofle_cfg, 0, sizeof(sofle_cfg));
}

static char *sofle_oled_choose(uint8_t item) {
    if (item == 0xFF) return sofle_cfg.name;
    if (item < SOFLE_OLED_LAYERS) return sofle_cfg.layers[item];
    return NULL;
}

/* Nome principal: ate 7 ASCII + NUL. Camadas: ate 5 ASCII + NUL.
 * A interface antiga (0x52) continua aceitando 5 bytes por item.
 */
static void sofle_oled_set(uint8_t item, const char *text, uint8_t input_len, bool mark_dirty) {
    char *target = sofle_oled_choose(item);
    if (target == NULL || text == NULL) return;
    uint8_t width = item == 0xFF ? SOFLE_OLED_NAME_BYTES : SOFLE_OLED_LAYER_BYTES;
    uint8_t limit = width - 1;
    if (input_len < limit) limit = input_len;
    char value[SOFLE_OLED_NAME_BYTES] = {0};
    for (uint8_t i = 0; i < limit; ++i) {
        /* Apenas ASCII imprimivel, sem sequencias UTF-8 em OLED monocromatico. */
        if ((uint8_t)text[i] < 32 || (uint8_t)text[i] > 126) break;
        value[i] = text[i];
    }
    if (memcmp(target, value, width) == 0) return;
    memcpy(target, value, width);
    sofle_storage_mark_dirty();
    sofle_oled_needs_redraw = true;
    if (mark_dirty) {
        sofle_oled_dirty |= (uint16_t)1u << (item == 0xFF ? 10 : item);
    }
}

static void sofle_oled_set_preset(uint8_t mode, uint8_t preset, bool mark_dirty) {
    if (mode > 1 || preset >= SOFLE_OLED_PRESETS) return;
    if (sofle_cfg.oled_mode == mode && sofle_cfg.oled_preset == preset) return;
    sofle_cfg.oled_mode = mode;
    sofle_cfg.oled_preset = preset;
    sofle_oled_needs_redraw = true;
    sofle_storage_mark_dirty();
    if (mark_dirty) sofle_oled_dirty |= SOFLE_OLED_DIRTY_PRESET;
}

static void sofle_oled_slave_sync(uint8_t in_len, const void *in_buf, uint8_t out_len, void *out_buf) {
    (void)out_len;
    (void)out_buf;
    if (in_len != sizeof(sofle_oled_sync_t) || in_buf == NULL) return;
    const sofle_oled_sync_t *msg = (const sofle_oled_sync_t *)in_buf;
    if (msg->item == 0xFE) {
        sofle_oled_set_preset((uint8_t)msg->text[0], (uint8_t)msg->text[1], false);
    } else {
        sofle_oled_set(msg->item, msg->text,
                       msg->item == 0xFF ? 7 : 5, false);
    }
}

static void sofle_rgb_slave_sync(uint8_t in_len, const void *in_buf, uint8_t out_len, void *out_buf) {
    (void)out_len;
    (void)out_buf;
    if (in_len != sizeof(sofle_rgb_sync_t) || in_buf == NULL) return;
    const sofle_rgb_sync_t *msg = (const sofle_rgb_sync_t *)in_buf;
    if (msg->role >= SOFLE_RGB_ROLES) return;
    uint8_t role = msg->role;
    if (msg->kind == 0) {
        if (memcmp(sofle_cfg.masks[role], msg->data, 8) != 0) {
            memcpy(sofle_cfg.masks[role], msg->data, 8);
            sofle_storage_mark_dirty();
        }
    } else if (msg->kind == 1) {
        if (memcmp(sofle_cfg.role_rgb[role], msg->data, 3) != 0) {
            memcpy(sofle_cfg.role_rgb[role], msg->data, 3);
            sofle_storage_mark_dirty();
        }
    } else if (msg->kind == 2 && msg->first < SOFLE_RGB_LED_COUNT) {
        uint8_t count = SOFLE_RGB_LED_COUNT - msg->first;
        if (count > SOFLE_RGB_SYNC_LEDS) count = SOFLE_RGB_SYNC_LEDS;
        uint8_t *dest = &sofle_cfg.led_rgb[role][msg->first][0];
        if (memcmp(dest, msg->data, (size_t)count * 3) != 0) {
            memcpy(dest, msg->data, (size_t)count * 3);
            sofle_storage_mark_dirty();
        }
    }
}

void keyboard_post_init_user(void) {
    eeconfig_read_user_datablock(&sofle_cfg, 0, sizeof(sofle_cfg));
    if (sofle_cfg.magic != SOFLE_CFG_MAGIC ||
        sofle_cfg.oled_mode > 1 || sofle_cfg.oled_preset >= SOFLE_OLED_PRESETS) {
        sofle_defaults();
        eeconfig_update_user_datablock(&sofle_cfg, 0, sizeof(sofle_cfg));
    }
    transaction_register_rpc(OLED_CONFIG_SYNC, sofle_oled_slave_sync);
    transaction_register_rpc(RGB_INDICATOR_SYNC, sofle_rgb_slave_sync);
    sofle_oled_dirty = SOFLE_OLED_DIRTY_ALL;
    sofle_rgb_dirty = SOFLE_RGB_DIRTY_ALL;
}

static void sofle_sync_oled(void) {
    if (sofle_oled_dirty == 0) return;
    for (uint8_t i = 0; i < 12; ++i) {
        uint16_t bit = (uint16_t)1u << i;
        if (!(sofle_oled_dirty & bit)) continue;
        sofle_oled_sync_t msg = {0};
        if (i == 11) {
            msg.item = 0xFE; /* Par modo/preset */
            msg.text[0] = (char)sofle_cfg.oled_mode;
            msg.text[1] = (char)sofle_cfg.oled_preset;
        } else {
            msg.item = i == 10 ? 0xFF : i;
            memcpy(msg.text, sofle_oled_choose(msg.item),
                   msg.item == 0xFF ? SOFLE_OLED_NAME_BYTES : SOFLE_OLED_LAYER_BYTES);
        }
        if (transaction_rpc_send(OLED_CONFIG_SYNC, sizeof(msg), &msg)) {
            sofle_oled_dirty &= ~bit;
        }
        break;
    }
}

static void sofle_sync_rgb(void) {
    if (sofle_rgb_dirty == 0) return;
    uint8_t role = 0;
    while (role < SOFLE_RGB_ROLES && !(sofle_rgb_dirty & ((uint16_t)1u << role))) ++role;
    if (role == SOFLE_RGB_ROLES) return;
    sofle_rgb_sync_t msg = {0};
    msg.role = role;
    msg.kind = sofle_rgb_sync_phase;
    msg.first = sofle_rgb_sync_first;
    if (msg.kind == 0) {
        memcpy(msg.data, sofle_cfg.masks[role], 8);
    } else if (msg.kind == 1) {
        memcpy(msg.data, sofle_cfg.role_rgb[role], 3);
    } else {
        uint8_t count = SOFLE_RGB_LED_COUNT - msg.first;
        if (count > SOFLE_RGB_SYNC_LEDS) count = SOFLE_RGB_SYNC_LEDS;
        memcpy(msg.data, &sofle_cfg.led_rgb[role][msg.first][0], (size_t)count * 3);
    }
    if (!transaction_rpc_send(RGB_INDICATOR_SYNC, sizeof(msg), &msg)) return;
    if (sofle_rgb_sync_phase < 2) {
        ++sofle_rgb_sync_phase;
    } else {
        sofle_rgb_sync_first += SOFLE_RGB_SYNC_LEDS;
        if (sofle_rgb_sync_first >= SOFLE_RGB_LED_COUNT) {
            sofle_rgb_dirty &= ~((uint16_t)1u << role);
            sofle_rgb_sync_first = 0;
            sofle_rgb_sync_phase = 0;
        }
    }
}

void housekeeping_task_user(void) {
    static uint32_t last_sync = 0;
    if (is_keyboard_master() && timer_elapsed32(last_sync) >= 100) {
        last_sync = timer_read32();
        if (sofle_oled_dirty) sofle_sync_oled();
        else sofle_sync_rgb();
    }
    // Grava em lote tanto no master quanto no slave; uma troca de USB preserva as opcoes.
    if (sofle_storage_dirty && timer_elapsed32(sofle_storage_time) >= 2500) {
        eeconfig_update_user_datablock(&sofle_cfg, 0, sizeof(sofle_cfg));
        sofle_storage_dirty = false;
    }
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    if (length < 32) return;
    uint8_t cmd = data[0];
    if (cmd != id_lighting_get_value && cmd != id_lighting_set_value) return;
    uint8_t sub = data[1];
    bool write = (cmd == id_lighting_set_value);

    /* V7: comando adicional 0x53 exclusivo para o nome principal (7 bytes).
     * GET devolve 0xA7 no byte 2, assinatura detectavel pela GUI GbrTzT.
     * O comando 0x52 antigo permanece compativel para as layers e 5 letras.
     */
    if (sub == SOFLE_OLED_LONG_SUBCMD) {
        if (write) sofle_oled_set(0xFF, (const char *)&data[2], 7, true);
        else {
            data[2] = SOFLE_OLED_LONG_MARKER;
            memcpy(&data[3], sofle_cfg.name, 7);
        }
        return;
    }
    /* V12: 0x55 controla modo/preset nos dois displays. */
    if (sub == SOFLE_OLED_PRESET_SUBCMD) {
        if (write) {
            sofle_oled_set_preset(data[2], data[3], true);
        } else {
            data[2] = SOFLE_OLED_PRESET_MARKER;
            data[3] = sofle_cfg.oled_mode;
            data[4] = sofle_cfg.oled_preset;
            data[5] = SOFLE_OLED_PRESETS;
        }
        return;
    }
    if (sub == SOFLE_OLED_SUBCMD) {
        uint8_t item = data[2];
        char *target = sofle_oled_choose(item);
        if (target == NULL) return;
        if (write) sofle_oled_set(item, (const char *)&data[3], 5, true);
        else memcpy(&data[3], target, 5);
        return;
    }
    if (sub == SOFLE_INDICATOR_MASK) {
        uint8_t role = data[2];
        if (role >= SOFLE_RGB_ROLES) return;
        if (write) {
            if (memcmp(sofle_cfg.masks[role], &data[3], 8) != 0) {
                memcpy(sofle_cfg.masks[role], &data[3], 8);
                /* Somente LEDs 0..57 existem; preserva os bits 56 e 57. */
                sofle_cfg.masks[role][7] &= 0x03;
                sofle_rgb_mark_dirty(role);
            }
        } else {
            /* O protocolo devolve mascara desde byte 2, substituindo role. */
            memcpy(&data[2], sofle_cfg.masks[role], 8);
        }
        return;
    }
    if (sub == SOFLE_INDICATOR_COLOR) {
        if (write) {
            for (uint8_t role = 0; role < SOFLE_RGB_ROLES; ++role) {
                const uint8_t *incoming = &data[2 + role * 3];
                if (memcmp(sofle_cfg.role_rgb[role], incoming, 3) == 0) continue;
                memcpy(sofle_cfg.role_rgb[role], incoming, 3);
                /* XCMKB espera que trocar cor da funcao repinte suas teclas. */
                for (uint8_t i = 0; i < SOFLE_RGB_LED_COUNT; ++i) {
                    if (sofle_role_led(role, i)) memcpy(sofle_cfg.led_rgb[role][i], incoming, 3);
                }
                sofle_rgb_mark_dirty(role);
            }
        } else {
            memcpy(&data[2], sofle_cfg.role_rgb, 30);
        }
        return;
    }
    if (sub == SOFLE_INDICATOR_PER_LED) {
        uint8_t role = data[2];
        uint8_t first = data[3];
        if (role >= SOFLE_RGB_ROLES || first >= SOFLE_RGB_LED_COUNT) return;
        if (write) {
            uint8_t count = data[4];
            if (count > 9 || (uint16_t)first + count > SOFLE_RGB_LED_COUNT) return;
            const uint8_t *src = &data[5];
            uint8_t *dest = &sofle_cfg.led_rgb[role][first][0];
            if (memcmp(dest, src, (size_t)count * 3) != 0) {
                memcpy(dest, src, (size_t)count * 3);
                sofle_rgb_mark_dirty(role);
            }
        } else {
            uint8_t count = SOFLE_RGB_LED_COUNT - first;
            if (count > 9) count = 9;
            /* XCMKB usa 0x49 como assinatura de suporte por LED. */
            data[2] = SOFLE_INDICATOR_MAGIC;
            data[3] = count;
            memcpy(&data[4], &sofle_cfg.led_rgb[role][first][0], (size_t)count * 3);
        }
    }
}

#ifdef RGB_MATRIX_ENABLE
/* Duas metades tem cadeias independentes de 29 LEDs. O callback altera
 * apenas os LEDs locais, mantendo cores corretas com USB em qualquer lado.
 * O efeito RGB normal permanece ativo; indicadores sao sobrepostos. */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    uint8_t val = rgb_matrix_get_val();
    bool caps = host_keyboard_led_state().caps_lock;
    for (uint8_t i = led_min; i < led_max && i < SOFLE_RGB_LED_COUNT; ++i) {
        uint8_t role = 0xFF;
        if (layer > 0 && layer < SOFLE_RGB_ROLES && sofle_role_led(layer, i)) role = layer;
        if (caps && sofle_role_led(0, i)) role = 0; /* Caps tem prioridade. */
        if (role == 0xFF) continue;
        const uint8_t *rgb = sofle_cfg.led_rgb[role][i];
        rgb_matrix_set_color(i,
            (uint8_t)(((uint16_t)rgb[0] * val) / 255u),
            (uint8_t)(((uint16_t)rgb[1] * val) / 255u),
            (uint8_t)(((uint16_t)rgb[2] * val) / 255u));
    }
    return false;
}
#endif /* RGB_MATRIX_ENABLE */
#endif /* VIAL_ENABLE */

#ifdef OLED_ENABLE
#ifdef VIAL_ENABLE
#include "oled_presets.h"
#include "oled_presets_direito.h"
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    (void)rotation;
    // Rotacao definida por metade FISICA e nao por qual USB esta conectado.
    return OLED_ROTATION_0;
}

/* ===== GbrTzT V7: Fonte grande OLED 128x32 =====
 * 5x7 pixels ASCII escalados 3x -> 15x21, espaco de 2 pixels.
 * Sete letras ocupam ate 117 de 128 pixels, centralizadas.
 * Nome principal no topo; nome da layer pequeno na ultima linha, x=0.
 */
#ifdef VIAL_ENABLE
typedef struct { char chr; uint8_t columns[5]; } sofle_oled_glyph_t;
static const sofle_oled_glyph_t sofle_oled_glyphs[] = {
    {' ', {0x00, 0x00, 0x00, 0x00, 0x00}},
    {'-', {0x00, 0x08, 0x08, 0x08, 0x00}},
    {'.', {0x00, 0x60, 0x60, 0x00, 0x00}},
    {'0', {0x3E, 0x51, 0x49, 0x45, 0x3E}},
    {'1', {0x00, 0x42, 0x7F, 0x40, 0x00}},
    {'2', {0x42, 0x61, 0x51, 0x49, 0x46}},
    {'3', {0x41, 0x49, 0x49, 0x49, 0x36}},
    {'4', {0x18, 0x14, 0x12, 0x7F, 0x10}},
    {'5', {0x4F, 0x49, 0x49, 0x49, 0x31}},
    {'6', {0x3E, 0x49, 0x49, 0x49, 0x30}},
    {'7', {0x01, 0x71, 0x09, 0x05, 0x03}},
    {'8', {0x36, 0x49, 0x49, 0x49, 0x36}},
    {'9', {0x06, 0x49, 0x49, 0x49, 0x3E}},
    {'?', {0x02, 0x01, 0x59, 0x09, 0x06}},
    {'A', {0x7E, 0x09, 0x09, 0x09, 0x7E}},
    {'B', {0x7F, 0x49, 0x49, 0x49, 0x36}},
    {'C', {0x3E, 0x41, 0x41, 0x41, 0x41}},
    {'D', {0x7F, 0x41, 0x41, 0x41, 0x3E}},
    {'E', {0x7F, 0x49, 0x49, 0x49, 0x41}},
    {'F', {0x7F, 0x09, 0x09, 0x09, 0x01}},
    {'G', {0x3E, 0x41, 0x49, 0x49, 0x39}},
    {'H', {0x7F, 0x08, 0x08, 0x08, 0x7F}},
    {'I', {0x41, 0x41, 0x7F, 0x41, 0x41}},
    {'J', {0x30, 0x40, 0x41, 0x3F, 0x01}},
    {'K', {0x7F, 0x08, 0x14, 0x22, 0x41}},
    {'L', {0x7F, 0x40, 0x40, 0x40, 0x40}},
    {'M', {0x7F, 0x02, 0x0C, 0x02, 0x7F}},
    {'N', {0x7F, 0x06, 0x08, 0x30, 0x7F}},
    {'O', {0x3E, 0x41, 0x41, 0x41, 0x3E}},
    {'P', {0x7F, 0x09, 0x09, 0x09, 0x06}},
    {'Q', {0x3E, 0x41, 0x51, 0x21, 0x5E}},
    {'R', {0x7F, 0x09, 0x19, 0x29, 0x46}},
    {'S', {0x46, 0x49, 0x49, 0x49, 0x31}},
    {'T', {0x01, 0x01, 0x7F, 0x01, 0x01}},
    {'U', {0x3F, 0x40, 0x40, 0x40, 0x3F}},
    {'V', {0x1F, 0x20, 0x40, 0x20, 0x1F}},
    {'W', {0x7F, 0x20, 0x18, 0x20, 0x7F}},
    {'X', {0x63, 0x14, 0x08, 0x14, 0x63}},
    {'Y', {0x03, 0x04, 0x78, 0x04, 0x03}},
    {'Z', {0x61, 0x51, 0x49, 0x45, 0x43}},
    {'_', {0x40, 0x40, 0x40, 0x40, 0x40}},
    {'a', {0x20, 0x54, 0x54, 0x54, 0x78}},
    {'b', {0x7F, 0x48, 0x44, 0x44, 0x38}},
    {'c', {0x38, 0x44, 0x44, 0x44, 0x44}},
    {'d', {0x38, 0x44, 0x44, 0x48, 0x7F}},
    {'e', {0x38, 0x54, 0x54, 0x54, 0x58}},
    {'f', {0x08, 0x7E, 0x09, 0x09, 0x02}},
    {'g', {0x0C, 0x52, 0x52, 0x52, 0x3E}},
    {'h', {0x7F, 0x08, 0x04, 0x04, 0x78}},
    {'i', {0x00, 0x44, 0x7D, 0x40, 0x00}},
    {'j', {0x20, 0x40, 0x44, 0x3D, 0x00}},
    {'k', {0x7F, 0x10, 0x28, 0x44, 0x00}},
    {'l', {0x00, 0x41, 0x7F, 0x40, 0x00}},
    {'m', {0x7C, 0x04, 0x78, 0x04, 0x78}},
    {'n', {0x7C, 0x08, 0x04, 0x04, 0x78}},
    {'o', {0x38, 0x44, 0x44, 0x44, 0x38}},
    {'p', {0x7E, 0x12, 0x12, 0x12, 0x0C}},
    {'q', {0x0C, 0x12, 0x12, 0x12, 0x7E}},
    {'r', {0x7C, 0x08, 0x04, 0x04, 0x08}},
    {'s', {0x48, 0x54, 0x54, 0x54, 0x24}},
    {'t', {0x04, 0x3F, 0x44, 0x44, 0x20}},
    {'u', {0x3C, 0x40, 0x40, 0x20, 0x7C}},
    {'v', {0x1C, 0x20, 0x40, 0x20, 0x1C}},
    {'w', {0x7C, 0x20, 0x10, 0x20, 0x7C}},
    {'x', {0x44, 0x28, 0x10, 0x28, 0x44}},
    {'y', {0x0E, 0x50, 0x50, 0x50, 0x3E}},
    {'z', {0x44, 0x64, 0x54, 0x4C, 0x44}},
};

static const uint8_t *sofle_oled_find_glyph(char c) {
    for (uint8_t i = 0; i < sizeof(sofle_oled_glyphs) / sizeof(sofle_oled_glyphs[0]); ++i) {
        if (sofle_oled_glyphs[i].chr == c) return sofle_oled_glyphs[i].columns;
    }
    return NULL;
}

static void sofle_oled_large_name(const char *name) {
    uint8_t length = 0;
    while (length < 7 && name[length] != '\0') ++length;
    if (length == 0) return;
    uint8_t width = (uint8_t)(length * 17 - 2);
    uint8_t start_x = (uint8_t)((128 - width) / 2);
    for (uint8_t pos = 0; pos < length; ++pos) {
        const uint8_t *columns = sofle_oled_find_glyph(name[pos]);
        if (!columns) continue;
        for (uint8_t col = 0; col < 5; ++col) {
            for (uint8_t row = 0; row < 7; ++row) {
                if (!(columns[col] & (1u << row))) continue;
                for (uint8_t xx = 0; xx < 3; ++xx) {
                    for (uint8_t yy = 0; yy < 3; ++yy) {
                        oled_write_pixel((uint8_t)(start_x + pos * 17 + col * 3 + xx),
                                         (uint8_t)(row * 3 + yy), true);
                    }
                }
            }
        }
    }
}
#endif /* VIAL_ENABLE */

bool oled_task_user(void) {
    static uint8_t previous_layer = 0xFF;
    static bool previous_caps = false;
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    bool caps = host_keyboard_led_state().caps_lock;
    if (sofle_oled_needs_redraw || previous_layer != layer || previous_caps != caps) {
        oled_clear();
        if (sofle_cfg.oled_mode == 1) {
            oled_set_cursor(0, 0);
            // O firmware V12 possui apenas um conjunto de bitmaps: o mesmo preset em cada OLED.
            oled_write_raw_P((const char *)(is_keyboard_left() ? sofle_left_preset(sofle_cfg.oled_preset) : sofle_right_preset(sofle_cfg.oled_preset)), 512);
        } else {
            sofle_oled_large_name(sofle_cfg.name);
            oled_set_cursor(0, 3);
            if (layer < SOFLE_OLED_LAYERS) {
                oled_write(sofle_cfg.layers[layer], false);
            } else {
                oled_write(get_u8_str(layer, ' '), false);
            }
            oled_write(is_keyboard_left() ? PSTR(" E") : PSTR(" D"), false);
        }
        previous_layer = layer;
        previous_caps = caps;
        sofle_oled_needs_redraw = false;
    }
    return false;
}
#endif /* OLED_ENABLE */
