#!/usr/bin/env bash
# Sofle Choc V2 GbrTzT - gera UF2 esquerdo e direito com EE_HANDS.
set -euo pipefail
shopt -s nullglob
KEYBOARD_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
QMK_ROOT="$(cd "$KEYBOARD_DIR/../../.." && pwd)"
KB='gbrtzt/soflev2_choc'
if [[ ! -f "$QMK_ROOT/builddefs/build_keyboard.mk" ]]; then
    printf 'ERRO: raiz QMK nao encontrada: %s\n' "$QMK_ROOT" >&2
    exit 1
fi
cd "$QMK_ROOT"
for required in keyboard.json config.h rules.mk keymaps/vial/keymap.c keymaps/vial/config.h keymaps/vial/rules.mk keymaps/vial/vial.json keymaps/vial/oled_presets.h; do
    if [[ ! -s "$KEYBOARD_DIR/$required" ]]; then
        printf 'ERRO: arquivo obrigatorio ausente: %s\n' "$KEYBOARD_DIR/$required" >&2
        exit 1
    fi
done
compile_side() {
    local side="$1" name="$2" filename="$3"
    local generated=()
    printf '\n=== Compilando lado %s (%s) ===\n' "$name" "$side"
    rm -f -- "$QMK_ROOT"/gbrtzt_soflev2_choc_vial*.uf2
    qmk compile -c -kb "$KB" -km vial -t "uf2-split-$side" -e 'PROGRAM_CMD=:'
    generated=( "$QMK_ROOT"/gbrtzt_soflev2_choc_vial*.uf2 )
    if [[ ${#generated[@]} -ne 1 || ! -s "${generated[0]:-}" ]]; then
        echo 'ERRO: UF2 nao encontrado apos compilacao.' >&2
        exit 1
    fi
    mv -f -- "${generated[0]}" "$KEYBOARD_DIR/$filename"
    printf 'Gerado: %s\n' "$KEYBOARD_DIR/$filename"
}
compile_side left ESQUERDO soflev2_choc_esquerdo.uf2
compile_side right DIREITO soflev2_choc_direito.uf2
printf '\nOK: dois arquivos UF2 na pasta do teclado.\n'
