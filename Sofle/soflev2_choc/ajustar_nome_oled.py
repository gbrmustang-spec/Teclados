#!/usr/bin/env python3
"""SofleV2 - GbrTzT: inverter orientacao dos OLEDs e renomear no QMK/Vial.

Executar na pasta do teclado pelo QMK MSYS. Nao cria backups nem altera
pinagem, RGB, definicoes de camadas, UID, VID ou PID.
"""
from pathlib import Path
import json
import re
import sys

ROOT = Path(__file__).resolve().parent
KBD_FILE = ROOT / "keyboard.json"
VIAL_FILE = ROOT / "keymaps" / "vial" / "vial.json"
KEYMAP_FILE = ROOT / "keymaps" / "vial" / "keymap.c"
NEW_NAME = "SofleV2 - GbrTzT"


def main():
    for file in (KBD_FILE, VIAL_FILE, KEYMAP_FILE):
        if not file.is_file():
            sys.exit(f"ERRO: arquivo nao encontrado: {file}")

    try:
        kbd = json.loads(KBD_FILE.read_text(encoding="utf-8-sig"))
        vial = json.loads(VIAL_FILE.read_text(encoding="utf-8-sig"))
        source = KEYMAP_FILE.read_text(encoding="utf-8-sig")
    except (UnicodeError, ValueError, OSError) as exc:
        sys.exit(f"ERRO ao ler os arquivos: {exc}")

    if "keyboard_name" not in kbd or "name" not in vial:
        sys.exit("ERRO: os arquivos JSON nao possuem os campos de nome esperados.")

    old_rotation = re.compile(
        r"return\s+is_keyboard_left\(\)\s*\?\s*OLED_ROTATION_180\s*:\s*OLED_ROTATION_0\s*;"
    )
    new_rotation = "return is_keyboard_left() ? OLED_ROTATION_0 : OLED_ROTATION_180;"
    if old_rotation.search(source):
        new_source, count = old_rotation.subn(new_rotation, source)
        if count != 1:
            sys.exit(f"ERRO: esperava apenas uma definicao de rotacao, encontrei {count}.")
    elif new_rotation in source:
        new_source = source  # ja aplicado; permite executar novamente
    else:
        sys.exit("ERRO: nao encontrei a funcao de rotacao esperada no keymap.c. Nada foi alterado.")

    old_kbd_name = kbd["keyboard_name"]
    old_vial_name = vial["name"]
    kbd["keyboard_name"] = NEW_NAME
    vial["name"] = NEW_NAME

    # Os tres arquivos foram validados acima; modificar somente o solicitado.
    try:
        if source != new_source:
            KEYMAP_FILE.write_text(new_source, encoding="utf-8", newline="\n")
        if old_kbd_name != NEW_NAME:
            KBD_FILE.write_text(json.dumps(kbd, ensure_ascii=False, indent=4) + "\n", encoding="utf-8", newline="\n")
        if old_vial_name != NEW_NAME:
            VIAL_FILE.write_text(json.dumps(vial, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    except OSError as exc:
        sys.exit(f"ERRO ao salvar alteracoes: {exc}")

    print(f"OK: nome USB/QMK: {old_kbd_name!r} -> {NEW_NAME!r}")
    print(f"OK: nome Vial: {old_vial_name!r} -> {NEW_NAME!r}")
    print("OK: OLED esquerdo = 0 graus; OLED direito = 180 graus")
    print("OK: LED RGB, EE_HANDS, UID, VID/PID e demais recursos mantidos")


if __name__ == "__main__":
    main()
