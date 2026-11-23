#!/usr/bin/env python3
"""Corrige apenas orientacao e presets direito dos OLEDs SofleV2.
Nao cria backups e nao modifica a configuracao USB/RGB/Vial.
"""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parent
KEYMAP = ROOT / "keymaps" / "vial" / "keymap.c"
RIGHT_ASSETS = ROOT / "keymaps" / "vial" / "oled_presets_direito.h"

if not KEYMAP.is_file() or not RIGHT_ASSETS.is_file():
    sys.exit("ERRO: keymap.c ou oled_presets_direito.h nao encontrado.")
source = KEYMAP.read_text(encoding="utf-8")
original = source

# V2 inicial: esquerda 180/direita 0. V2.1: esquerda 0/direita 180.
# Relato fisico: esquerda correta em 0; direita invertida em 180 -> ambos em 0.
pattern = r"return\s+is_keyboard_left\(\)\s*\?\s*OLED_ROTATION_(?:0|180)\s*:\s*OLED_ROTATION_(?:0|180)\s*;"
source, count = re.subn(pattern, "return OLED_ROTATION_0;", source)
if count != 1 and "return OLED_ROTATION_0;" not in source:
    sys.exit("ERRO: padrao de rotacao do OLED nao reconhecido.")

old_include = '#include "oled_presets.h"'
new_include = '#include "oled_presets.h"\n#include "oled_presets_direito.h"'
if '"oled_presets_direito.h"' not in source:
    if source.count(old_include) != 1:
        sys.exit("ERRO: include oled_presets.h esperado nao encontrado exatamente uma vez.")
    source = source.replace(old_include, new_include, 1)

old_call = 'oled_write_raw_P((const char *)sofle_left_preset(sofle_cfg.oled_preset), 512);'
new_call = 'oled_write_raw_P((const char *)(is_keyboard_left() ? sofle_left_preset(sofle_cfg.oled_preset) : sofle_right_preset(sofle_cfg.oled_preset)), 512);'
if new_call not in source:
    if source.count(old_call) != 1:
        sys.exit("ERRO: chamada de bitmap OLED nao encontrada ou duplicada.")
    source=source.replace(old_call,new_call,1)

if source!=original:
    KEYMAP.write_text(source,encoding="utf-8",newline="\n")
print("OK: OLED esquerdo 0 / direito 0; presets separados esquerda/direita.")
print("OK: nenhuma alteracao em RGB, EE_HANDS, Vial e nome USB.")
