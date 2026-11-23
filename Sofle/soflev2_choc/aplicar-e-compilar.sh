#!/usr/bin/env bash
# SofleV2 - GbrTzT - aplica os dois ajustes e compila os dois UF2 na pasta atual.
set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
python3 "$SCRIPT_DIR/ajustar_nome_oled.py"
if [[ ! -f "$SCRIPT_DIR/compilar-uf2.sh" ]]; then
    echo "ERRO: compilar-uf2.sh nao encontrado no projeto." >&2
    exit 1
fi
bash "$SCRIPT_DIR/compilar-uf2.sh"
